
/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#pragma once

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

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "misc.h"
#include "Config.h"


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;
using namespace tensorflow;
using namespace tensorflow::ops;


namespace dataSampler{

	class DataProducer {
	public:
		DataProducer(std::string& ini, std::string& good_folder, std::string& ngood_folder, std::queue<std::pair<Tensor, Tensor>>& buffer);
		~DataProducer() {
			if (!good_files_.empty()) {
				good_files_.clear();
			}

			if (!ngood_files_.empty()) {
				ngood_files_.clear();
			}

			if (!buffer_.empty()) {
				std::queue<std::pair<Tensor, Tensor>> empty;
				std::swap(buffer_, empty);
			}
		};

		int mats2Tensor(std::vector<std::pair<cv::Mat, float>> mats, Tensor& input_batch, Tensor& label_batch);
		void DataArgumentation(cv::Mat& inMat, int flag, bool isScale);
		int readHyperPara();
		int readDataEnhance();

		void run();

	private:
		std::string good_;
		std::string ngood_;
		vector<std::string> good_files_;
		vector<std::string> ngood_files_;

		std::queue<std::pair<Tensor,Tensor>>& buffer_;

		Config cfg_;

		// hyper parameters
		int hp_batch_ = 32;
		float hp_ratio_ = 0.6;
		int hp_total_epoches_ = 10000;

		// data parameters 
		int input_height_;
		int input_width_;
		int win_height_;
		int win_width_;
		int channels_;
		int only_channel_;
		int factor_;

		// data enhancement
		int dp_data_enhance_;
		std::vector<double> dp_scale_ = {1,-0.05,0.05};
		std::vector<double> dp_contrast_ = {1,-10,10};
		std::vector<double> dp_brightness_ = {1,-0.2,0.2};
		std::vector<double> dp_flip_ = {1,1};
		int dp_smooth_ = 1;
	};

	// 2.consumer for training
	class DataConsumer {
	public:
		DataConsumer(std::queue<std::pair<Tensor, Tensor>>& buffer,std::string& root_dir);
		~DataConsumer() {
			session_->Close();
			if (!buffer_.empty()) {
				std::queue<std::pair<Tensor, Tensor>> empty;
				std::swap(buffer_, empty);
			}
		};

		void run(Session* session,int step, int restore=1);
		bool load_graph(Session* session, std::string path_graph_file);

	private:
		std::queue<std::pair<Tensor, Tensor>>& buffer_;
		std::unique_ptr<tensorflow::Session> session_;
		Tensor phase_train_;
		std::string root_dir;
		std::int32_t iterations_ = 0;
		std::string save_path = "./checkpoint/";
	};
}
