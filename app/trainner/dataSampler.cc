/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#define GLOG_NO_ABBREVIATED_SEVERITIES

#include "dataSampler.h"
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
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/public/session_options.h"
#include <tensorflow/core/protobuf/meta_graph.pb.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "glog/logging.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine


using namespace std;
using namespace cv;
using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;
using namespace tensorflow;
using namespace tensorflow::ops;

namespace dataSampler {
	std::mutex mx;
	std::condition_variable conT;
	bool finished = false;
	bool isNAN = false;

	DataProducer::DataProducer(std::string& ini, std::string& good, std::string& ngood, std::queue<std::pair<Tensor, Tensor>>& buffer):buffer_(buffer){
		std::stringstream ss;
		ss << std::this_thread::get_id();
		int id = std::stoi(ss.str());
		srand(id);
		//srand(time(NULL));
		//load ini
		if (ini.empty()) {
			fprintf(stdout, "ini file is not exist!\n");
			LOG(INFO) << "ini file is not exist!";
			return;
		} else {
			fprintf(stdout, "Load the config.ini!\n");
			LOG(INFO) << "Load the config.ini" ;
			cfg_.load(ini.c_str());
			cfg_.print();
			readHyperPara();
			readDataEnhance();
		}
		
		good_ = good;
		ngood_ = ngood;
		if (good.empty() && ngood.empty()) {
			LOG(ERROR) << "The sampler folder is empty!";
		} else {
			std::string ok_str = "OK samples path is (" + good + ")\n";
			std::string ng_str = "NG samples path is (" + ngood + ")\n";
			fprintf(stdout, ok_str.c_str());
			fprintf(stdout, ng_str.c_str());
			LOG(INFO) << "OK samples path is (" << good << ")";
			LOG(INFO) << "NG samples path is (" << ngood << ")";
			GetFileNameFromDir(good, good_files_);
			GetFileNameFromDir(ngood, ngood_files_);
		}
	}
	
	int DataProducer::readHyperPara() {
		hp_batch_ = cfg_.getInt("hp_batch", 32);
		hp_ratio_ = cfg_.getDouble("hp_ratio", 0.6);
		hp_total_epoches_ = cfg_.getInt("hp_total_epoches", 10000);
		return 0;
	}

	int DataProducer::readDataEnhance() {
		input_height_ = cfg_.getInt("input_height", 128);
		input_height_ = cfg_.getInt("input_width", 128);
		win_height_ = cfg_.getInt("window_height", 1000);
		win_width_ = cfg_.getInt("window_width", 1000);
		channels_ = cfg_.getInt("channels", 1);
		only_channel_ = cfg_.getInt("only_channel", 0);
		factor_ = cfg_.getInt("dp_factor",1);

		dp_data_enhance_ = cfg_.getInt("dp_data_enhance", 1);
		dp_scale_ = cfg_.getDoubleVector("dp_scale");
		dp_contrast_ = cfg_.getDoubleVector("dp_contrast");
		dp_brightness_ = cfg_.getDoubleVector("dp_brightness");
		dp_flip_ = cfg_.getDoubleVector("dp_flip");
		dp_smooth_ = cfg_.getInt("dp_smooth", 1);
		return 0;
	}

	int DataProducer::mats2Tensor(vector<pair<Mat, float>> mats, Tensor& input_batch, Tensor& label_batch) {
		auto start = std::chrono::system_clock::now();
		int dims = mats.size();
		//LOG(INFO) << "dims:" << dims;
#pragma omp parallel 
		for (int mt = 0; mt < dims; mt++) {
			cv::Mat mat = mats[mt].first; // NHWC in tensorflow
			float label = mats[mt].second;
			if (channels_ == 1) {
				mat.convertTo(mat, CV_32FC1);
			} else if (channels_ == 3) {
				mat.convertTo(mat, CV_32FC3);
			}
#if 0
			string save_name = "data/"+ std::to_string(label) + "_mat2Tensor_" + std::to_string(mt) + ".png";
			imwrite(save_name, mat);
#endif
			int width = mat.cols;
			int height = mat.rows;
			int depth = mat.channels();
			//std::cout << "[" << height << "," << width << "," << depth <<"]"<< std::endl;
			auto inputImageMapped = input_batch.tensor<float, 4>();
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

			//label batch tensor
			auto batchMapped = label_batch.tensor<float, 2>();	
			//LOG(INFO) << label;
			if (label > 0.5) {
				batchMapped(mt, 0) = 1.0f;
				batchMapped(mt, 1) = 0.0f;
			} else {
				batchMapped(mt, 0) = 0.0f;
				batchMapped(mt, 1) = 1.0f;
			}
		}

		auto end = std::chrono::system_clock::now();
		//LOG(INFO) << "Convert mat to tensors took "
		//	<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0
		//	<< "ms.";
		return 0;
	}


	void DataProducer::DataArgumentation(cv::Mat& inMat, int flag, bool isScale) {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd(
		int data_argu = Rand(2);
		if (flag && data_argu) {
			// 1. scale
			if (isScale && dp_scale_[0] > 0) {
				if (Rand(2)) {
					float min_scale = dp_scale_[1], max_scale = dp_scale_[2]; // [-0.05,0.05]
					std::uniform_real_distribution<> scale(min_scale, max_scale);

					int width = inMat.cols * (1 + scale(gen));
					int height = inMat.rows * (1 + scale(gen));
					cv::resize(inMat, inMat, cv::Size(width, height), cv::INTER_NEAREST);
				}
			}

			//2. Contrast
			if (dp_contrast_[0] > 0 && Rand(2)) {
				float min_alpha = dp_contrast_[1], max_alpha = dp_contrast_[2]; // [-0.2,0.2]
				std::uniform_real_distribution<> alpha((1.0 - min_alpha), (1.0 + max_alpha));
				inMat = inMat*alpha(gen);
			}

			//3. Brightness
			if (dp_contrast_[0] > 0 && Rand(2)) {
				float min_brightness= dp_contrast_[1], max_brightness = dp_contrast_[2]; // [-10,10]
				float beta = (float)(Rand(max_brightness*2)) - min_brightness;
				inMat = inMat + beta;
			}

			//4. flipping around y-axis
			if (dp_flip_[0] > 0 && Rand(2)) {
				int flip = dp_flip_[1];
				cv::flip(inMat, inMat, flip);
			}

			//5. smooth filtering.
			if (dp_smooth_ && Rand(2)) {
				int smooth_param = 3 + 2 * (Rand(2)); //kernel size [3,3] or [5,5]
				GaussianBlur(inMat, inMat, cv::Size(smooth_param, smooth_param), 0, 0);
			}
		}
	}


	void DataProducer::run() {
		random_shuffle(good_files_.begin(), good_files_.end());
		random_shuffle(ngood_files_.begin(), ngood_files_.end());
		int size_good = good_files_.size();
		int size_ngood = ngood_files_.size();
		int epochok = floor(hp_batch_ *(1 - hp_ratio_));
		//LOG(INFO) << "OK num: " << epochok;
		for (int epoch = 0; epoch < hp_total_epoches_ && isNAN != true; epoch++) {
			std::vector<std::pair<cv::Mat, float>> mats;
			for (int i = 0; i < hp_batch_; i++) {
				int random_num; string file_name; cv::Mat image_mat; float label;
				if (i < epochok) {   // OK
					random_num = Rand(size_good);
					file_name = good_files_[random_num];
					//LOG(INFO) << good_ + file_name;
					image_mat = cv::imread(good_ + file_name, CV_LOAD_IMAGE_UNCHANGED);
					if (channels_ == 1) {
						if (image_mat.channels() != 1) {
							std::vector<cv::Mat> vec_mats;
							split(image_mat, vec_mats);
							image_mat = vec_mats[only_channel_];
						}
					} else if (channels_ == 3) {
						if (image_mat.channels() != 3) {
							cv::cvtColor(image_mat, image_mat, CV_GRAY2BGR);
						}
					} else {
						fprintf(stdout, "channel number is error!\n");
					}
					label = 0.0f;
				}
				else if (i >= epochok) { // NG
					random_num = Rand(size_ngood);
					file_name = ngood_files_[random_num];
					//LOG(INFO) << ngood_+ file_name;
					image_mat = cv::imread(ngood_ + file_name, CV_LOAD_IMAGE_UNCHANGED);
					if (channels_ == 1) {
						if (image_mat.channels() != 1) {
							std::vector<cv::Mat> vec_mats;
							split(image_mat, vec_mats);
							image_mat = vec_mats[only_channel_];
						}
					}
					else if (channels_ == 3) {
						if (image_mat.channels() != 3) {
							cv::cvtColor(image_mat, image_mat, CV_GRAY2BGR);
						}
					}
					else {
						fprintf(stdout, "channel number is error!\n");
					}
					label = 1.0f;
				}

				if (image_mat.empty()) {
					std::string err_file = "Could not read " + file_name + "\n";
					fprintf(stdout, err_file.c_str());
					LOG(INFO) << "Could not read " << file_name ;
					continue;
				}

				//data argumentation 
				if (factor_ == 1) {
					DataArgumentation(image_mat, dp_data_enhance_, false);
				} else {
					DataArgumentation(image_mat, dp_data_enhance_, true);
				}

				int oriWidth = image_mat.cols;
				int oriHeight = image_mat.rows;
				int chanel = image_mat.channels();

				if (oriWidth <= win_width_ && oriHeight > win_height_) {
					cv::resize(image_mat, image_mat, cv::Size(win_width_ + 1, win_height_), cv::INTER_NEAREST);
				}
				else if (oriWidth > win_width_ && oriHeight <= win_height_) {
					cv::resize(image_mat, image_mat, cv::Size(oriWidth, win_height_ + 1), cv::INTER_NEAREST);
				}
				else if (oriWidth <= win_width_ && oriHeight <= win_height_) {
					cv::resize(image_mat, image_mat, cv::Size(win_width_ + 1, win_height_ + 1), cv::INTER_NEAREST);
				}

			    oriWidth = image_mat.cols;
				oriHeight = image_mat.rows;

				int h_off = 0, w_off = 0;
				w_off = Rand(oriWidth - win_width_);
				h_off = Rand(oriHeight - win_height_);
				cv::Rect rect = Rect(w_off, h_off, win_width_, win_height_);
				std::pair<cv::Mat, float> temp_mat(cv::Mat(image_mat, rect), label);
				int dsWidth = temp_mat.first.cols / factor_;
				int dsHeight = temp_mat.first.rows / factor_;
				cv::resize(temp_mat.first, temp_mat.first, cv::Size(dsWidth, dsHeight), 0, 0, CV_INTER_LINEAR);
				mats.push_back(temp_mat);
			}
			//LOG(INFO) << "\n";

			int height = win_height_ / factor_;
			int width = win_width_ / factor_;

			//LOG(INFO) << "height:" << height << ",width:" << width;
			//std::cout << "tensor: " << height << "," << width << std::endl;
			Tensor input_batch;
			Tensor label_batch(DT_FLOAT, TensorShape({ hp_batch_, 2 })); //1, height, width, dept
			if (channels_ == 1) {
				input_batch = Tensor(DT_FLOAT, TensorShape({ hp_batch_, height, width, 1 })); //1, height, width, dept
			} else if (channels_ == 3) {
				input_batch = Tensor(DT_FLOAT, TensorShape({ hp_batch_, height, width, 3 })); //1, height, width, dept
			}


			random_shuffle(mats.begin(), mats.end());
			mats2Tensor(mats, input_batch, label_batch);
			//LOG(INFO) << "Debug......................1";
			//LOG(INFO) << label_batch.matrix<float>() << endl;
			std::pair<Tensor, Tensor> tempE(input_batch, label_batch);

			// producer lock
			{
				std::lock_guard<std::mutex> lk(mx);
				buffer_.push(tempE);
				fprintf(stdout,"Training Data Produced. \n");
				//LOG(INFO) << "Training Data Produced. " ;
			}
			conT.notify_all();
		} // end of epoches
		{
			std::lock_guard<std::mutex> lk(mx);
			finished = true;
		}
		conT.notify_all();
	}


	// 2.data consumer
	DataConsumer::DataConsumer(std::queue<std::pair<Tensor, Tensor>>& buffer,std::string& root_dir) :buffer_(buffer),root_dir(root_dir){
		phase_train_ = Tensor(DT_BOOL, TensorShape());
		phase_train_.scalar<bool>()() = true;
	}


	bool DataConsumer::load_graph(Session* session, std::string path_graph_file) {
		GraphDef graph_def;

		// Read in the protobuf graph we exported
		// (The path seems to be relative to the cwd. Keep this in mind
		// when using `bazel run` since the cwd isn't where you call
		// `bazel run` but from inside a temp folder.)
		Status status = ReadBinaryProto(Env::Default(), path_graph_file, &graph_def);
		if (!status.ok()) {
			fprintf(stdout, status.ToString().c_str());
			LOG(ERROR) << status.ToString() ;
			return false;
		}

		// Add the graph to the session
		status = session->Create(graph_def);
		if (!status.ok()) {
			fprintf(stdout, status.ToString().c_str());
			LOG(ERROR) << status.ToString() ;
			return false;
		}

		//Restore graph training status
		std::vector<string> vNames;
		int node_count = graph_def.node_size();
		for (int i = 0; i < node_count; i++) {
			auto n = graph_def.node(i);
			if (n.name().find("nWeights") != std::string::npos) {
				vNames.push_back(n.name());
			}
		}

		std::vector<tensorflow::Tensor> nnOutput;
		status = session->Run({}, vNames, {}, &nnOutput);
		if (!status.ok()) {
			fprintf(stdout, status.ToString().c_str());
			LOG(INFO)<< status.ToString();
			return false;
		}

		//Using graph
		tensorflow::Tensor features(DT_FLOAT, TensorShape({ 4, 8 }));
		auto features_mat = features.flat<float>();
		for (int i = 0; i < 4 * 2; ++i) {
			features_mat(i) = i;
		}

		std::vector<std::pair<string, tensorflow::Tensor>> inputs = { { "input_x", features } };

		// The session will initialize the outputs
		std::vector<tensorflow::Tensor> outputs;

		// Run the session, evaluating our "c" operation from the graph
		status = session->Run(inputs, { "c:0" }, {}, &outputs);
		if (!status.ok()) {
			fprintf(stdout, status.ToString().c_str());
			LOG(INFO)<< status.ToString();
			return false;
		}

		auto output_indices = outputs[0].flat_inner_dims<float>();
		for (int i = 0; i < 3; ++i) {
			std::cout << output_indices(i) << "\n";
		}

		return true;
	}

	void DataConsumer::run(Session* session, int step, int method ){
		
		while (true) {
			std::unique_lock<std::mutex> lk(mx);
			conT.wait(lk, [this] { return finished || !buffer_.empty(); });
			while (!buffer_.empty()) {
				std::pair<Tensor, Tensor> tempE = buffer_.front();
				buffer_.pop();
				iterations_++;
				fprintf(stdout,"Training Data Consumed. \n");
				//LOG(INFO) << "Training Data Consumed ";
				Tensor input_batch = tempE.first;
				Tensor label_batch = tempE.second;

				std::pair<string, Tensor> input1 = { "X",input_batch };
				std::pair<string, Tensor> input2 = { "phase",phase_train_ };
				std::pair<string, Tensor> output = { "Y",label_batch };
				// Actually run the image through the model.
				std::vector<Tensor> outputs;
				std::string iter_str = "Iteration " + to_string(iterations_) + ".\n";
				fprintf(stdout, iter_str.c_str());
				TF_CHECK_OK(session->Run({ input1 , input2 ,output }, { "cost" }, { "train" }, &outputs)); // Train
				float cost = outputs[0].scalar<float>()(0);
				std::string cost_str = "Cost: " + to_string(cost) + ".\n";
				fprintf(stdout, cost_str.c_str());
				if (iterations_ % 10 == 0) {
					LOG(INFO) << "Iteration " << iterations_;
					LOG(INFO) << "Cost: " << cost ;
				}
				if (isnan(cost)) {
					isNAN = true;
					LOG(ERROR) << "Cost: " << cost ;
					return;
				}
			    if (iterations_ % step == 0) {
					Tensor model_string(DT_STRING, TensorShape({ 1, 1 }));
					std::string step_string = "model_step_" + std::to_string(iterations_ / step);
					model_string.matrix< std::string >()(0, 0) = save_path + step_string;
					TF_CHECK_OK(session->Run({ { "save/Const:0", model_string } }, {}, { "save/control_dependency" }, nullptr));
					std::string save_str = "Save checkpoint" + step_string + ".\n";
					fprintf(stdout,save_str.c_str());
					//std::cout << "Save checkpoint" + step_string <<std::endl;
					LOG(INFO)<< "Save checkpoint" + step_string;
				}
			 outputs.clear();
			}
			//if (finished) {
			//	std::cout << "Training finished..." << std::endl;
			//	break;
			//}
		}
	}
}
