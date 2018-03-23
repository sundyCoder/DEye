/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/

#include <fstream>
#include <utility>
#include <vector>
#include <direct.h>

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/public/session_options.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "misc.h"
#include "libconvert.h"

using namespace cv;
using namespace std;

// These are all common classes it's handy to reference with no namespace.
using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;
using namespace tensorflow;
using namespace tensorflow::ops;

// Takes a file name, and loads a list of labels from it, one per line, and
// returns a vector of the strings. It pads with empty strings so the length
// of the result is a multiple of 16, because our model expects that.
Status ReadLabelsFile(const string& file_name, std::vector<string>* result,
                      size_t* found_label_count) {
  std::ifstream file(file_name);
  if (!file) {
    return tensorflow::errors::NotFound("Labels file ", file_name,
                                        " not found.");
  }
  result->clear();
  string line;
  while (std::getline(file, line)) {
    result->push_back(line);
  }
  *found_label_count = result->size();
  const int padding = 16;
  while (result->size() % padding) {
    result->emplace_back();
  }
  return Status::OK();
}

static Status ReadEntireFile(tensorflow::Env* env, const string& filename,
                             Tensor* output) {
  tensorflow::uint64 file_size = 0;
  TF_RETURN_IF_ERROR(env->GetFileSize(filename, &file_size));

  string contents;
  contents.resize(file_size);

  std::unique_ptr<tensorflow::RandomAccessFile> file;
  TF_RETURN_IF_ERROR(env->NewRandomAccessFile(filename, &file));

  tensorflow::StringPiece data;
  TF_RETURN_IF_ERROR(file->Read(0, file_size, &data, &(contents)[0]));
  if (data.size() != file_size) {
    return tensorflow::errors::DataLoss("Truncated read of '", filename,
                                        "' expected ", file_size, " got ",
                                        data.size());
  }
  output->scalar<string>()() = data.ToString();
  return Status::OK();
}

// Given an image file name, read in the data, try to decode it as an image,
// resize it to the requested size, and then scale the values as desired.
Status ReadTensorFromImageFile(const string& file_name, const int input_height,
                               const int input_width, const float input_mean,
                               const float input_std,
                               std::vector<Tensor>* out_tensors) {
  auto root = tensorflow::Scope::NewRootScope();
  using namespace ::tensorflow::ops;  // NOLINT(build/namespaces)

  string input_name = "file_reader";
  string output_name = "normalized";

  // read file_name into a tensor named input
  Tensor input(tensorflow::DT_STRING, tensorflow::TensorShape());
  TF_RETURN_IF_ERROR(
      ReadEntireFile(tensorflow::Env::Default(), file_name, &input));

  // use a placeholder to read input data
  auto file_reader =
      Placeholder(root.WithOpName("input"), tensorflow::DataType::DT_STRING);

  std::vector<std::pair<string, tensorflow::Tensor>> inputs = {
      {"input", input},
  };

  // Now try to figure out what kind of file it is and decode it.
  const int wanted_channels = 3;
  tensorflow::Output image_reader;
  if (tensorflow::StringPiece(file_name).ends_with(".png")) {
    image_reader = DecodePng(root.WithOpName("png_reader"), file_reader,
                             DecodePng::Channels(wanted_channels));
  } else if (tensorflow::StringPiece(file_name).ends_with(".gif")) {
    // gif decoder returns 4-D tensor, remove the first dim
    image_reader =
        Squeeze(root.WithOpName("squeeze_first_dim"),
                DecodeGif(root.WithOpName("gif_reader"), file_reader));
  } else if (tensorflow::StringPiece(file_name).ends_with(".bmp")) {
    image_reader = DecodeBmp(root.WithOpName("bmp_reader"), file_reader);
  } else {
    // Assume if it's neither a PNG nor a GIF then it must be a JPEG.
    image_reader = DecodeJpeg(root.WithOpName("jpeg_reader"), file_reader,
                              DecodeJpeg::Channels(wanted_channels));
  }
  // Now cast the image data to float so we can do normal math on it.
  auto float_caster =
      Cast(root.WithOpName("float_caster"), image_reader, tensorflow::DT_FLOAT);
  // The convention for image ops in TensorFlow is that all images are expected
  // to be in batches, so that they're four-dimensional arrays with indices of
  // [batch, height, width, channel]. Because we only have a single image, we
  // have to add a batch dimension of 1 to the start with ExpandDims().
  auto dims_expander = ExpandDims(root, float_caster, 0);
  // Bilinearly resize the image to fit the required dimensions.
  auto resized = ResizeBilinear(
      root, dims_expander,
      Const(root.WithOpName("size"), {input_height, input_width}));
  // Subtract the mean and divide by the scale.
  Div(root.WithOpName(output_name), Sub(root, resized, {input_mean}),
      {input_std});

  // This runs the GraphDef network definition that we've just constructed, and
  // returns the results in the output tensor.
  tensorflow::GraphDef graph;
  TF_RETURN_IF_ERROR(root.ToGraphDef(&graph));

  std::unique_ptr<tensorflow::Session> session(
      tensorflow::NewSession(tensorflow::SessionOptions()));
  TF_RETURN_IF_ERROR(session->Create(graph));
  TF_RETURN_IF_ERROR(session->Run({inputs}, {output_name}, {}, out_tensors));
  return Status::OK();
}

// Reads a model graph definition from disk, and creates a session object you
// can use to run it.
Status LoadGraph(const string& graph_file_name,
                 std::unique_ptr<tensorflow::Session>* session) {
  tensorflow::GraphDef graph_def;

  Status load_graph_status =
      ReadBinaryProto(tensorflow::Env::Default(), graph_file_name, &graph_def);
  if (!load_graph_status.ok()) {
    return tensorflow::errors::NotFound("Failed to load compute graph at '",
                                        graph_file_name, "'");
  }
  session->reset(tensorflow::NewSession(tensorflow::SessionOptions()));
  Status session_create_status = (*session)->Create(graph_def);
  if (!session_create_status.ok()) {
    return session_create_status;
  }
  return Status::OK();
}

// Analyzes the output of the Inception graph to retrieve the highest scores and
// their positions in the tensor, which correspond to categories.
Status GetTopLabels(const std::vector<Tensor>& outputs, int how_many_labels,
                    Tensor* indices, Tensor* scores) {
  auto root = tensorflow::Scope::NewRootScope();
  using namespace ::tensorflow::ops;  // NOLINT(build/namespaces)

  string output_name = "top_k";
  TopK(root.WithOpName(output_name), outputs[0], how_many_labels);
  // This runs the GraphDef network definition that we've just constructed, and
  // returns the results in the output tensors.
  tensorflow::GraphDef graph;
  TF_RETURN_IF_ERROR(root.ToGraphDef(&graph));

  std::unique_ptr<tensorflow::Session> session(
      tensorflow::NewSession(tensorflow::SessionOptions()));
  TF_RETURN_IF_ERROR(session->Create(graph));
  // The TopK node returns two outputs, the scores and their original indices,
  // so we have to append :0 and :1 to specify them both.
  std::vector<Tensor> out_tensors;
  TF_RETURN_IF_ERROR(session->Run({}, {output_name + ":0", output_name + ":1"},
                                  {}, &out_tensors));
  *scores = out_tensors[0];
  *indices = out_tensors[1];
  return Status::OK();
}

// Given the output of a model run, and the name of a file containing the labels
// this prints out the top five highest-scoring values.
Status PrintTopLabels(const std::vector<Tensor>& outputs,
                      const string& labels_file_name, int *flag) {
  std::vector<string> labels;
  size_t label_count;
  Status read_labels_status =
      ReadLabelsFile(labels_file_name, &labels, &label_count);
  if (!read_labels_status.ok()) {
    LOG(ERROR) << read_labels_status;
    return read_labels_status;
  }
  const int how_many_labels = std::min(4, static_cast<int>(label_count));
  Tensor indices;
  Tensor scores;
  TF_RETURN_IF_ERROR(GetTopLabels(outputs, how_many_labels, &indices, &scores));
  tensorflow::TTypes<float>::Flat scores_flat = scores.flat<float>();
  tensorflow::TTypes<int32>::Flat indices_flat = indices.flat<int32>();
  std::vector<std::pair<string, float>> vecScore;
  for (int pos = 0; pos < how_many_labels; ++pos) {
    const int label_index = indices_flat(pos);
    const float score = scores_flat(pos);
    LOG(INFO) << labels[label_index] << ": " << score;
	std::pair<string,float> retPair = {labels[label_index],score};
	vecScore.push_back(retPair);
  }
  if (vecScore[0].first == "1") {
	  *flag = 1;
  } else {
	  *flag = 0;
  }
  return Status::OK();
}

// This is a testing function that returns whether the top label index is the
// one that's expected.
Status CheckTopLabel(const std::vector<Tensor>& outputs, int expected,
                     bool* is_expected) {
  *is_expected = false;
  Tensor indices;
  Tensor scores;
  const int how_many_labels = 1;
  TF_RETURN_IF_ERROR(GetTopLabels(outputs, how_many_labels, &indices, &scores));
  tensorflow::TTypes<int32>::Flat indices_flat = indices.flat<int32>();
  if (indices_flat(0) != expected) {
    LOG(ERROR) << "Expected label #" << expected << " but got #"
               << indices_flat(0);
    *is_expected = false;
  } else {
    *is_expected = true;
  }
  return Status::OK();
}

static int Rand(int num) {
	
	int rand_value = rand() % num + 1;
	return rand_value;
}


static int mat2Tensor(std::vector<cv::Mat>& mats, Tensor& inputImg) {
	auto start = std::chrono::system_clock::now();
	int dims = mats.size();
	for (int mt = 0; mt < dims; mt++) {
		cv::Mat mat= mats[mt];
		mat.convertTo(mat, CV_32FC3);
		//string save_name = "data/mat2Tensor_" + std::to_string(mt) + ".png";
		//imwrite(save_name, mat);
		int width = mat.cols;
		int height = mat.rows;
		int depth = 3;

		auto inputImageMapped = inputImg.tensor<float, 4>();
		//Copy all the data over
		for (int y = 0; y < height; ++y) {
			const float* source_row = ((float*)mat.data) + (y * width * depth);
			for (int x = 0; x < width; ++x) {
				const float* source_pixel = source_row + (x * depth);
				inputImageMapped(mt, y, x, 0) = source_pixel[0];
				inputImageMapped(mt, y, x, 1) = source_pixel[1];
				inputImageMapped(mt, y, x, 2) = source_pixel[2];
			}
		}
	}
	
	auto end = std::chrono::system_clock::now();
	LOG(INFO) << "Convert mat to tensors took "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0
		<< "ms.";
	return 0;
}

int main_bigblob(int argc, char* argv[]) {
  // These are the command-line flags the program can understand.
  // input the model expects. If you train your own model, or use something
  // other than inception_v3, then you'll need to update these.
  //string image = "data/NG_7A0LC_A3046XXXXXXXXXX.jpg";

  string graph = "model/saemodel.pb";
  string labels = "model/label.txt";
  string root_dir = ".";
  string file_list = "data";
  string file_path = tensorflow::io::JoinPath(root_dir, "data/");
  
  int32 input_width = 768;
  int32 input_height = 1344;
  int batch = 4;
  float factor = 0.25;
  int height = input_height * factor;
  int width = input_width * factor;

  float input_mean = 0;
  float input_std = 255;
  string input_layer = "X";
  string output_layer = "Y_out";
  int save_image = 0;
  std::vector<Flag> flag_list = {
      Flag("graph", &graph, "graph to be executed"),
      Flag("labels", &labels, "name of file containing labels"),
      Flag("input_width", &input_width, "resize image to this width in pixels"),
      Flag("input_height", &input_height,
           "resize image to this height in pixels"),
      Flag("input_mean", &input_mean, "scale pixel values to this mean"),
      Flag("input_std", &input_std, "scale pixel values to this std deviation"),
      Flag("input_layer", &input_layer, "name of input layer"),
      Flag("output_layer", &output_layer, "name of output layer"),
      Flag("root_dir", &root_dir, "interpret image and graph file names relative to this directory"),
      Flag("file_path", &file_path, "image test folder"),
      Flag("save_image", &save_image, "save the result image?(1:NG,2:OK,3:both OK and NG.)"),
      Flag("batch", &batch, "the number of batchs to test."),
  };
  string usage = tensorflow::Flags::Usage(argv[0], flag_list);
  const bool parse_result = tensorflow::Flags::Parse(&argc, argv, flag_list);
  if (!parse_result) {
    LOG(ERROR) << usage;
    return -1;
  }


  // We need to call this to set up global state for TensorFlow.
  tensorflow::port::InitMain(argv[0], &argc, &argv);
  if (argc > 1) {
    LOG(ERROR) << "Unknown argument " << argv[1] << "\n" << usage;
    return -1;
  }

  SessionOptions options;
  options.config.set_allow_soft_placement(true);
  options.config.set_log_device_placement(true);
  //options.config.set_allocated_gpu_options()
  // First we load and initialize the model.
  std::unique_ptr<tensorflow::Session> session(tensorflow::NewSession(options));
  //std::unique_ptr session(tensorflow::NewSession(options));

  string graph_path = tensorflow::io::JoinPath(root_dir, graph);
  Status load_graph_status = LoadGraph(graph_path, &session);
  if (!load_graph_status.ok()) {
    LOG(ERROR) << load_graph_status;
    return -1;
  }

  auto files = get_files(file_path, "/file.txt");
  std::sort(files.begin(), files.end());
  _mkdir((file_path + "/NG").c_str());
  _mkdir((file_path + "/OK").c_str());
  std::string fileNameOK = file_path + "/OK/" + "OK_file_list.txt";
  std::string fileNameNG = file_path + "/NG/" + "NG_file_list.txt";
  char *okDir = new char[fileNameOK.length() + 1];
  char *ngDir = new char[fileNameNG.length() + 1];
  strcpy(okDir, fileNameOK.c_str());
  strcpy(ngDir, fileNameNG.c_str());
  FILE *fpOK = fopen(okDir, "wb");
  FILE *fpNG = fopen(ngDir, "wb");
  int retNG = 0;
  int retOK = 0;

  srand(time(NULL));
  for (auto  fln: files) {
	  auto start = std::chrono::system_clock::now();
	  //string image_path = tensorflow::io::JoinPath(file_path, fln);
	  LOG(INFO) << "##############" << fln << "##############";
	  cv::Mat image_mat = cv::imread(file_path + fln, CV_LOAD_IMAGE_COLOR);
	  if (image_mat.empty() || image_mat.cols < input_width || image_mat.rows < input_height) {
		  LOG(INFO) << "Could not read " << fln  ;
		  continue;
	  }
	  GaussianBlur(image_mat, image_mat, cv::Size(3, 3), 0, 0);
	  int img_width = image_mat.cols, img_height = image_mat.rows;
	  LOG(INFO) << "Origin size is :" << "[" << img_width << "," << img_height << "]";
	  int h_off = 0, w_off = 0;
	  std::vector<cv::Mat> mats;
	  for (int i = 0; i < batch; i++) {
		  w_off = Rand(img_width - input_width);
		  h_off = Rand(img_height - input_height);
		  LOG(INFO) << "[" << w_off << "," << h_off << "] ";
		  cv::Rect rect = Rect(w_off, h_off, input_width, input_height);
		  cv::Mat temp_mat = cv::Mat(image_mat, rect);
		  cv::resize(temp_mat, temp_mat, cv::Size(), factor, factor);
		  mats.push_back(temp_mat);
	  }
	  
	  Tensor input_batch(DT_FLOAT, TensorShape({ batch,height,width,3 })); //1, height, width, dept
	  mat2Tensor(mats, input_batch);

	  Tensor phase_train(DT_BOOL, TensorShape());
	  phase_train.scalar<bool>()() = false;

	  std::pair<string, Tensor> input1 = { input_layer,input_batch };
	  std::pair<string, Tensor> input2 = { "phase",phase_train };
	  // Actually run the image through the model.
	  std::vector<Tensor> outputs;
	  Status run_status = session->Run({ input1,input2 },
									   { output_layer }, {}, &outputs);
	  if (!run_status.ok()) {
		  LOG(ERROR) << "Running model failed: " << run_status;
		  return -1;
	  }

	  int flag = 0;
	  // Do something interesting with the results we've generated.
	  Tensor outTensor = outputs[0];
	  int numT = outTensor.NumElements();
	  LOG(INFO) << "numT: " << numT;

	  LOG(INFO) << outputs[0].matrix<float>();

	  //Status print_status = PrintTopLabels(outputs, labels, &flag);
	  //if (!print_status.ok()) {
		 // LOG(ERROR) << "Running print failed: " << print_status;
		 // return -1;
	  //}
	 auto retMatrix = outputs[0].matrix<float>();
	 for (int i = 0; i < batch; i++) {
		 if (retMatrix(i, 0) > retMatrix(i,1)) {
			 flag++;
		 }
	 }

	  //copy result files
	  if (flag > 0) {
		  retNG++;
		  convert::writeStringAppendToFile(fln, fpNG);
		  if (save_image == 1 || save_image == 3) {
			imwrite(file_path + "NG/" + fln, image_mat);
		  }
	  } else {
		  retOK++;
		  convert::writeStringAppendToFile(fln, fpOK);
		  if (save_image == 2 || save_image == 3) {
			  imwrite(file_path + "OK/" + fln, image_mat);
		  }
	  }
	  LOG(INFO) << "OK: " << retOK <<",NG: "<<retNG;
	  LOG(INFO) << "Sum of testing " << retNG + retOK << " pcs.";
	  auto end = std::chrono::system_clock::now();
	  LOG(INFO) << "All took "
		  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0
		  << "ms.\n";
  }

  LOG(INFO) << "OK: " << retOK++ <<",NG: "<<retNG;
  fclose(fpOK);
  fclose(fpNG);
  return 0;
}
