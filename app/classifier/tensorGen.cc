/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#include <fstream>
#include <utility>
#include <vector>
#include <direct.h>
#include <queue>
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
#include "tensorGen.h"

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

namespace tensorGen {
	std::mutex mx;
	std::condition_variable conT;
	bool finished = false;

	int TensorProducer::mat2Tensor(std::vector<cv::Mat>& mats, Tensor& inputImg) {
		auto start = std::chrono::system_clock::now();
		int dims = mats.size();
#pragma omp parallel 
		for (int mt = 0; mt < dims; mt++) {
			cv::Mat mat = mats[mt];       // NHWC in tensorflow
			mat.convertTo(mat, CV_32FC3);
			//string save_name = "data/mat2Tensor_" + std::to_string(mt) + ".png";
			//imwrite(save_name, mat);
			int width = mat.cols;
			int height = mat.rows;
			int depth = mat.channels();;

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
		std::cout << "Convert mat to tensors took "
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0
			<< "ms.\n";
		return 0;
	}


	TensorProducer::TensorProducer(std::queue<std::pair<string, Tensor>>& buffer) :buffer_(buffer) {
			srand(time(NULL));
		}

	void TensorProducer::run(string filePath, vector<string>& files, struct ImgInfo& info) {
		int winWidth = info.winWidth;
		int winHeight = info.winHeight;
		for (auto fln : files) {
				std::cout << "##############" << fln << "##############" << std::endl;
				cv::Mat image_mat = cv::imread(filePath + fln, CV_LOAD_IMAGE_UNCHANGED);
				int oriWidth = image_mat.cols;
				int oriHeight = image_mat.rows;
				int chanel = image_mat.channels();

				if (image_mat.empty()) {
					std::cout << "Could not read " << fln << std::endl;
					continue;
				}

				//GaussianBlur(image_mat, image_mat, cv::Size(3, 3), 0, 0);

				if (oriWidth <= winWidth && oriHeight > winHeight) {
					cv::resize(image_mat, image_mat, cv::Size(winWidth + 1, oriHeight), cv::INTER_NEAREST);
				}
				else if (oriWidth > winWidth && oriHeight <= winHeight) {
					cv::resize(image_mat, image_mat, cv::Size(oriWidth, winHeight + 1), cv::INTER_NEAREST);
				}
				else if (oriWidth <= winWidth && oriHeight <= winHeight) {
					cv::resize(image_mat, image_mat, cv::Size(winWidth + 1, winHeight + 1), cv::INTER_NEAREST);
				}


				oriWidth = image_mat.cols;
				oriHeight = image_mat.rows;

				int h_off = 0, w_off = 0;
				std::vector<cv::Mat> mats;
				for (int i = 0; i < info.batch; i++) {
					w_off = Rand(oriWidth - winWidth);
					h_off = Rand(oriHeight - winHeight);
					std::cout << "[" << w_off << "," << h_off << "] " << std::endl;
					cv::Rect rect = Rect(w_off, h_off, winWidth, winHeight);
					cv::Mat temp_mat = cv::Mat(image_mat, rect);
					int dsWidth = temp_mat.cols / info.factor;
					int dsHeight = temp_mat.rows / info.factor;
					cv::resize(temp_mat, temp_mat, cv::Size(dsWidth, dsHeight), 0, 0, INTER_NEAREST);
					mats.push_back(temp_mat);
				}
				int height = winHeight / info.factor;
				int width = winWidth / info.factor;

				Tensor input_batch(DT_FLOAT, TensorShape({ info.batch, height, width, chanel })); //1, height, width, dept
				mat2Tensor(mats, input_batch);
				std::pair<string, Tensor> tempE(fln, input_batch);

				// producer lock
				{
					std::lock_guard<std::mutex> lk(mx);
					buffer_.push(tempE);
					//LOG(INFO) << "Produced: " << tempE.first;
					std::cout << "Produced: " << tempE.first << std::endl;
				}
				conT.notify_all();

			} // end of for loop

			{
				std::lock_guard<std::mutex> lk(mx);
				finished = true;
			}
			conT.notify_all();
		}

	// 2 consumer
	TensorConsumer::TensorConsumer(std::queue<std::pair<string, Tensor>>& buffer, string graph_path, int method) :buffer_(buffer), graph_path_(graph_path) {
		phase_train_ = Tensor(DT_BOOL, TensorShape());
		phase_train_.scalar<bool>()() = false;
		SessionOptions options;
		options.config.set_allow_soft_placement(true);
		//options.config.set_log_device_placement(true);
		session_.reset(tensorflow::NewSession(options));
		if (session_ == nullptr) {
			throw runtime_error("Could not create Tensorflow session.");
		}

		if (method == 1) {    // load graph.pb 
			Status load_graph_status = LoadGraph(graph_path, &session_);
			if (!load_graph_status.ok()) {
				LOG(ERROR) << load_graph_status;
			}
		}
		else if (method == 2) {   // load checkpoint file 
								  // set up your input paths
			string pathToGraph;
			string checkpointPath;
			if (graph_path.empty()) {
				pathToGraph = "model/mckp/model.meta";
				checkpointPath = "model/mckp/model";
			}
			else {
				checkpointPath = graph_path;
				pathToGraph = graph_path + ".meta";
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
		}
	}

	// Reads a model graph definition from disk, and creates a session object you
	// can use to run it.
	Status TensorConsumer::LoadGraph(const string& graph_file_name,
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

	void TensorConsumer::run(string filePath, int save_image, FILE* fpNG, FILE* fpOK) {
		int retNG = 0, retOK = 0;

		while (true) {
			std::unique_lock<std::mutex> lk(mx);
			conT.wait(lk, [this] { return finished || !buffer_.empty(); });

			while (!buffer_.empty()) {

				std::pair<string, Tensor> tempE = buffer_.front();
				buffer_.pop();
				std::cout << "Consumed: " << tempE.first << std::endl;

				string fln = tempE.first;
				Tensor input_batch = tempE.second;

				std::pair<string, Tensor> input1 = { "X",input_batch };
				std::pair<string, Tensor> input2 = { "phase",phase_train_ };
				// Actually run the image through the model.
				std::vector<Tensor> outputs;
				Status run_status = session_->Run({ input1,input2 },
												  { "Y_out" }, {}, &outputs);
				if (!run_status.ok()) {
					LOG(ERROR) << "Running model failed: " << run_status;
					return;
				}

				int flag = 0;
				// Do something interesting with the results we've generated.
				Tensor outTensor = outputs[0];
				int numT = outTensor.NumElements();
				std::cout << "numT:" << numT << std::endl;

				std::cout << outputs[0].matrix<float>() << std::endl;
				auto retMatrix = outputs[0].matrix<float>();

				for (int i = 0; i < numT / 2; i++) {
					if (retMatrix(i, 0) > retMatrix(i, 1)) {
						flag++;
					}
				}

				//copy result files
				if (flag > 0) {
					retNG++;
					convert::writeStringAppendToFile(fln, fpNG);
				} else {
					retOK++;
					convert::writeStringAppendToFile(fln, fpOK);
				}
			}

			if (finished) {
				float sum = (retNG + retOK)*1.0f;
				std::cout << "OK: " << retOK<<"("<<retOK/sum<<")" << ",NG: " << retNG <<"("<<retNG/sum<<")"<< std::endl;
				std::cout << "Sum of testing " << retNG + retOK << " pcs." << std::endl;
				break;
			}
		}
	}
}