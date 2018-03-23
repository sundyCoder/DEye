/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/

#include <fstream>
#include <utility>
#include <vector>
#include <direct.h>
#include <numeric>
#include <iomanip>


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
#include <tensorflow/core/protobuf/meta_graph.pb.h>

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

struct defectBlob {
	int type;
	float confidence;
	cv::Rect defectRect;
	std::vector<cv::Point> vpts;
};

struct DefectInfo {
	float confidence;
	std::vector<defectBlob> vDefects;
	std::shared_ptr<cv::Mat> pDefectImage_;
};

static void formatFprintf(std::string& str, const char* format, ...)
{
	char s[1000];
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(s, format, arg_ptr);
	va_end(arg_ptr);
	str += s;
}

static std::string formatTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);
	return buf;
}

static void writeStringAppendFile(const std::string& str, FILE *fp) {
	int length = str.length();
	fwrite(str.c_str(), length, 1, fp);
	fputc('\n', fp);
}

int mat2Tensor(std::vector<cv::Mat>& mats, Tensor& inputImg) {
	auto start = std::chrono::system_clock::now();
	int dims = mats.size();
#pragma omp parallel 
	for (int mt = 0; mt < dims; mt++) {
		cv::Mat mat = mats[mt];       // NHWC in tensorflow
		int width = mat.cols;
		int height = mat.rows;
		int depth = mat.channels();;
		if (depth == 1) {
			mat.convertTo(mat, CV_32FC1);
		} else if (depth == 3) {
			mat.convertTo(mat, CV_32FC3);
		}
		//string save_name = "data/mat2Tensor_" + std::to_string(mt) + ".png";
		//imwrite(save_name, mat);

		auto inputImageMapped = inputImg.tensor<float, 4>(); // 4 tensors
															 //Copy all the data over
		for (int y = 0; y < height; ++y) {
			const float* source_row = ((float*)mat.data) + (y * width * depth);
			for (int x = 0; x < width; ++x) {
				const float* source_pixel = source_row + (x * depth);
				for (int c = 0; c < depth; ++c) {
					const float* source_value = source_pixel + c;
					inputImageMapped(mt, y, x, c) = *source_value;
				}
			}
		}
	}

	auto end = std::chrono::system_clock::now();
	//LOG(INFO) << "Convert mat to tensors took "
	//std::cout << "Convert mat to tensors took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0 << "ms.\n";
	return 0;
}



int main(int argc, char* argv[]) {
	string graph = "model/mpb/gpuver.pb";
	string labels = "model/mpb/label.txt";

	int32 input_height = 1344;
	int32 input_width = 768;
	int32 window_height = 822;
	int32 window_width = 612;
	int batch = 4;
	float factor = 0.25;
	string root_dir = ".";
	string file_list = "data";
	string file_path = tensorflow::io::JoinPath(root_dir, "data/");
	//int load_color = 0;
	int load_channel = 1;
	int only_channel = 0;
	int smooth = 0;

	float input_mean = 0;
	float input_std = 255;
	string input_layer = "X";
	string output_layer = "Y_out";
	int save_image = 0;
	int method = 1;
	std::vector<Flag> flag_list = {
		Flag("graph", &graph, "graph to be executed"),
		Flag("labels", &labels, "name of file containing labels"),
		Flag("input_height", &input_height, "resize image to this height in pixels"),
		Flag("input_width", &input_width, "resize image to this width in pixels"),
		Flag("window_height", &window_height, "the height of sliding window images."),
		Flag("window_width", &window_width, "the width of sliding window images."),
		Flag("factor", &factor, "the down sample factor."),
		//Flag("load_color", &load_color, "load color image or not."),
		Flag("load_channel", &load_channel, "number of channel."),
		Flag("smooth", &smooth, "number of channel."),
		Flag("root_dir", &root_dir, "interpret image and graph file names relative to this directory"),
		Flag("file_path", &file_path, "image test folder"),
		Flag("save_image", &save_image, "save the result image?(1:NG,2:OK,3:both OK and NG.)"),
		Flag("batch", &batch, "the number of batchs to test."),
		Flag("method", &method, "load graph method(1:load graph.pb, 2: load checkpoint file).")
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
/////////////////////////////////////////////////////////////////////

  SessionOptions options;
  std::unique_ptr < tensorflow::Session> session_;
  options.config.set_allow_soft_placement(true);
 //options.config.set_inter_op_parallelism_threads(1);
 //options.config.set_intra_op_parallelism_threads(1);
  //options.config.set_log_device_placement(true);
  session_.reset(tensorflow::NewSession(options));
  if (session_ == nullptr) {
	  throw runtime_error("Could not create Tensorflow session.");
  }

  string pathToGraph;
  string checkpointPath;
  if (graph.empty()) {
	  pathToGraph = "model/mckp/model.meta";
	  checkpointPath = "model/mckp/model";
  }
  else {
	  checkpointPath = graph;
	  pathToGraph = graph + ".meta";
  }
  Status status;

  // Read in the protobuf graph we exported
  MetaGraphDef graph_def;
  status = ReadBinaryProto(Env::Default(), pathToGraph, &graph_def);
  if (!status.ok()) {
	  throw runtime_error("Error reading graph definition from " + pathToGraph + ": " + status.ToString());
  }

  // Add the graph to the session
  status = session_->Create(graph_def.graph_def());
  if (!status.ok()) {
	  throw runtime_error("Error creating graph: " + status.ToString());
  }

  // Read weights from the saved checkpoint
  Tensor checkpointPathTensor(DT_STRING, TensorShape());
  checkpointPathTensor.scalar<std::string>()() = checkpointPath;
  status = session_->Run({ { graph_def.saver_def().filename_tensor_name(), checkpointPathTensor }, },
						{}, { graph_def.saver_def().restore_op_name() }, nullptr);
  if (!status.ok()) {
	  throw runtime_error("Error loading checkpoint from " + checkpointPath + ": " + status.ToString());
  }

  Tensor phase_train_ = Tensor(DT_BOOL, TensorShape());
  phase_train_.scalar<bool>()() = false;
  ////////////////////////////////////////////////////////////////////

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
  //split images
  int x_start = 0;
  int y_start = 0;


  for (auto  fln: files) {
	  auto start = std::chrono::system_clock::now();
	  std::cout<< "##############" << fln << "##############"<<std::endl;
	  if (fln.substr(fln.length() - 3) == "txt") {
		  continue;
	  }
	  cv::Mat image_mat = cv::imread(file_path + fln, CV_LOAD_IMAGE_UNCHANGED);
	  if (image_mat.empty()) {
		  LOG(INFO) << "Could not read " << fln  ;
		  continue;
	  }

	  int c_ = image_mat.channels();
	  if (load_channel == 1) {
		  if (c_ != 1) {
			  std::vector<cv::Mat> vec_mats;
			  split(image_mat, vec_mats);
			  image_mat = vec_mats[only_channel];
		  }
	  } else if (load_channel == 3) {
		  if (c_ != 3) {
			  cv::cvtColor(image_mat, image_mat, CV_GRAY2BGR);
		  }
	  } else {
		  fprintf(stdout,"error channel number!");
		  break;
	  }

	  int overlap_ = 0.5;
	  int gray_threshold_ = 100;

	  if (smooth == 1) {
		  GaussianBlur(image_mat, image_mat, cv::Size(3, 3), 0, 0);
	  }
	  int x_end = image_mat.cols - window_width;
	  int y_end = image_mat.rows - window_height;

	  DefectInfo defectInfoN;
	  defectInfoN.confidence = 0;
	  defectInfoN.pDefectImage_ = std::make_shared<cv::Mat>(image_mat.rows, image_mat.cols, CV_8U);
	  defectInfoN.vDefects.clear();
	  (*defectInfoN.pDefectImage_) = 0;
	  //fprintf(stdout, "Splitting image...\n");
	  std::vector<cv::Mat> vec_mat;
	  std::vector<cv::Rect> split_rects_;
	  int sum_mat = 0;
	  for (int x = x_start; x < x_end; x += window_width/2) {
		  for (int y = y_start; y < y_end; y += window_height/2) {
			  cv::Rect rect(x, y, window_width , window_height);
			  cv::Mat sub_mat = image_mat(rect);
			  split_rects_.push_back(rect);
			  vec_mat.push_back(sub_mat);
			  sum_mat++;
		  }
	  }
	  std::cout << "Sum of blocks:" << sum_mat << std::endl;
	  double max_value = 0;
	  double min_value = 0;
	  int countC1 = 0;
	  int countC2 = 0;
	  for (size_t i = 0; i < sum_mat; i++) {
		  std::vector<cv::Mat> mats;
		  mats.reserve(1);
		  cv::Mat preMat = vec_mat.at(i);
		  mats.push_back(preMat);
		  //cv::minMaxIdx(preMat, &min_value, &max_value);
		  //if (max_value < 100 ) {
			 // continue;
		  //}

		  Tensor input_batch;
		  if (load_channel == 1) {
			  input_batch = Tensor(DT_FLOAT, TensorShape({ batch,window_height,window_width,1 })); //1, height, width, dept
		  } else if (load_channel == 3) {
			  input_batch = Tensor(DT_FLOAT, TensorShape({ batch,window_height,window_width,3 })); //3, height, width, dept
		  }
		  mat2Tensor(mats, input_batch);
		  std::pair<string, Tensor> input1 = { "X",input_batch };
		  std::pair<string, Tensor> input2 = { "phase",phase_train_ };
		  // Actually run the image through the model.
		  std::vector<Tensor> outputs;
		  Status run_status = session_->Run({ input1,input2 }, { "Y_out" }, {}, &outputs);
		  if (!run_status.ok()) {
			  LOG(ERROR) << "Running model failed: " << run_status;
			  return -1;
		  }

		  // Do something interesting with the results we've generated.
		  Tensor outTensor = outputs[0];
		  int numT = outTensor.NumElements();

		  auto retMatrix = outputs[0].matrix<float>();
		  //std::cout << retMatrix<< std::endl;
		  
		  // get the average score of from output tensor
		  float conf_threshold = 0.5;
		  std::vector<float> results;
		  int flag = 0;
		  for (int j = 0; j < numT / 2; j++) {
			  float pos_score = retMatrix(j, 0);
			  if ((pos_score > retMatrix(j, 1)) && (pos_score >= 0.5)) {
				  results.push_back(pos_score);
				  flag++;
			  }
		  }

		  
		  if (flag) {
			  float avg_conf = std::accumulate(results.begin(), results.end(), 0) / results.size() * 1.0f;
			  if (avg_conf >= conf_threshold) {
				  defectBlob dInfo;
				  dInfo.type = 1;
				  dInfo.confidence = avg_conf;
				  dInfo.defectRect = split_rects_[i];
				  defectInfoN.vDefects.push_back(dInfo);
			  }
		  }
	  }
	  int sum_defects = defectInfoN.vDefects.size();
	  std::cout << "Sum of defects:" << sum_defects << std::endl;
	  for (size_t i = 0; i < sum_defects; i++) {
		  auto& di = defectInfoN.vDefects[i];
		  uint8_t v = std::max(0.0, di.confidence - 0.5) * 2 * 192 + 63;
		  cv::circle(*defectInfoN.pDefectImage_, cv::Point(di.defectRect.x + window_width / 2, di.defectRect.y + window_height / 2), window_height / 2, cv::Scalar(v, v, v), -1);

		  cv::Rect drect = di.defectRect;
		  if (save_image == 100) {
			  string save_name = fln + "@" + to_string(drect.x) + "_" + to_string(drect.y) + ".png";
			  _mkdir("./NG");
			  imwrite("./NG/" + save_name, image_mat(drect));
		  }
	  }


	  cv::Mat output_img = *(defectInfoN.pDefectImage_.get());

	  if (c_ == 1) {
		  cv::cvtColor(image_mat, image_mat, CV_GRAY2BGR);
		  image_mat = image_mat*0.5;
	  }
	  cv::Mat chs[3];
	  if (image_mat.channels() == 1) {
		  chs[0] = image_mat;
		  chs[1] = image_mat;
		  chs[2] = image_mat.clone();
		  output_img.copyTo(chs[2]);
	  }
	  else if (image_mat.channels() == 3) {
		  split(image_mat, chs);
		  output_img.copyTo(chs[2], output_img);
	  }

	  //marking defect on defect image
	  for (auto &di : defectInfoN.vDefects) {
		  string str_info;
		  std::stringstream stream;
		  cv::Rect drect = di.defectRect;
		  formatFprintf(str_info, "%d, %d, %d, %d, %f\n", drect.x, drect.y, drect.width, drect.height, di.confidence);
		  writeStringAppendFile(str_info, fpNG);
		  stream << di.confidence * 100;
		  string str_confidence = stream.str();
		  auto color = cv::Scalar(255, 255, 255);
		  putText(chs[1], str_confidence, cv::Point(drect.x + int(0.5 * drect.width) - 10, drect.y + int(0.5 * drect.height) + 5),
			  CV_FONT_HERSHEY_SIMPLEX, 0.5, color);
	  }

	  if (sum_defects > 0) {
		  cv::Mat output_defect_img;
		  cv::merge(chs, 3, output_defect_img);
		  if (save_image == 0) {
			convert::writeStringAppendToFile(fln, fpNG);
		  } else if(save_image == 1 || save_image == 3) {
			cv::imwrite(file_path + "/NG/" + fln + "_" + std::to_string(sum_defects) + ".png", output_defect_img);
			convert::writeStringAppendToFile(fln, fpNG);
		  }
		  retNG++;
	  } else {
		  if (save_image == 0) {
			  convert::writeStringAppendToFile(fln, fpOK);
		  } else if (save_image == 2 || save_image == 3) {
			  cv::imwrite(file_path + "/OK/" + fln, image_mat);
			  convert::writeStringAppendToFile(fln, fpOK);
		  }
		  retOK++;
	  }


	  auto end = std::chrono::system_clock::now();
	  std::cout << "All took "
		  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0
		  << "ms.\n";
  }

  float sum = (retNG + retOK)*1.0f;
  std::cout << "OK: " << retOK << "(" << retOK / sum << ")" << ",NG: " << retNG << "(" << retNG / sum << ")" << std::endl;
  std::cout << "Sum of testing " << retNG + retOK << " pcs." << std::endl;

  fclose(fpOK);
  fclose(fpNG);
  return 0;
}
