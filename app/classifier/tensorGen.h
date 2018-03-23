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
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/public/session_options.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "misc.h"

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


namespace tensorGen{

	struct ImgInfo {
		int winWidth;
		int winHeight;
		int batch;
		float factor;
	};

	class TensorProducer {
	private:
		std::queue<std::pair<string, Tensor>>& buffer_;
		const unsigned int size_ = 32;

	public:
		TensorProducer(std::queue<std::pair<string, Tensor>>& buffer);
		~TensorProducer() {
			if (!buffer_.empty()) {
				std::queue<std::pair<string, Tensor>> empty;
				std::swap(buffer_, empty);
			}
		};

		void run(string filePath, vector<string>& files, struct ImgInfo& info);
		int mat2Tensor(std::vector<cv::Mat>& mats, Tensor& inputImg);
	};

	class TensorConsumer {
	private:
		std::queue<std::pair<string, Tensor>>& buffer_;
		std::unique_ptr<tensorflow::Session> session_;
		std::string graph_path_;
		Tensor phase_train_;

	public:
		TensorConsumer(std::queue<std::pair<string, Tensor>>& buffer, string graph_path, int method);
		~TensorConsumer() {
			session_->Close();
			if (!buffer_.empty()) {
				std::queue<std::pair<string, Tensor>> empty;
				std::swap(buffer_, empty);
			}
		}

		Status LoadGraph(const string& graph_file_name, std::unique_ptr<tensorflow::Session>* session);
		void run(string filePath, int save_image, FILE* fpNG, FILE* fpOK);
	};
};
