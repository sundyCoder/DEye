#include <queue>

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"
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
#include "dataSampler.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace cv;
using namespace std;
using namespace dataSampler;

int main(int argc, char* argv[]) {
	std::string graph = "model/trainGraph/gpuTrainer.pb";
	string ok_folder = "./data/train/ok/";
	string ng_folder = "./data/train/ng/";
	int32 input_height = 850;
	int32 input_width = 643;
	int32 window_height = 822;
	int32 window_width = 612;
	int factor = 3;
	int batch = 32;
	int epoches = 1000;
	int step = 100;
	int method = 1;
	string root_dir = ".";

	std::vector<Flag> flag_list = {
		Flag("graph", &graph, "graph to be executed"),
		Flag("ok", &ok_folder, "good samples folder"),
		Flag("ng", &ng_folder, "not good samples folder"),
		Flag("input_height", &input_height, "the height of origin input images."),
		Flag("input_width", &input_width, "the width of origin input images."),
		Flag("window_height", &window_height, "the height of sliding window images."),
		Flag("window_width", &window_width, "the width of sliding window images."),
		Flag("factor", &factor, "the down sampling factor."),
		Flag("batch", &batch, "the training batch size."),
		Flag("epoches", &epoches, "the number of training iterations."),
		Flag("step", &step, "the step to save model"),
        Flag("method", &method, "load graph method(1:load graph.pb, 2: load checkpoint file)."),
		Flag("root_dir", &root_dir, "interpret image and graph file names relative to this directory"),
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

	auto start = std::chrono::system_clock::now();

	//defeine session and graph
	Session* session;
	GraphDef graph_def;
	MetaGraphDef metaGraph_def;
	SessionOptions opts;
	if (method == 1) {
		TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph, &graph_def));

		// Set GPU options
		graph::SetDefaultDevice("/gpu:0", &graph_def);
		//opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
		//opts.config.mutable_gpu_options()->set_allow_growth(true);
		opts.config.set_allow_soft_placement(true);
		//opts.config.set_log_device_placement(true);

		// create a new session
		TF_CHECK_OK(NewSession(opts, &session));

		// Load graph into session
		TF_CHECK_OK(session->Create(graph_def));

		// Initialize our variables
		TF_CHECK_OK(session->Run({}, {}, { "init_global_vars_op" }, nullptr));

	}else if(method == 2) {
		//LOG(INFO) << "Starting to restore the checkpoint.";
		std::cout << "Starting to restore the checkpoint."<<std::endl;
		// set up your input paths
		string pathToGraph;
		string checkpointPath;
		if (graph.empty()) {
			pathToGraph = "model/mckp/model.meta";
			checkpointPath = "model/mckp/model";
		} else {
			checkpointPath = graph;
			pathToGraph = graph + ".meta";
		}

		
		Status status;
		// Read in the protobuf graph we exported
		status = ReadBinaryProto(Env::Default(), pathToGraph, &metaGraph_def);
		if (!status.ok()) {
			throw runtime_error("Error reading graph definition from " + pathToGraph + ": " + status.ToString());
		}

		// Set GPU options
		//opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
		//opts.config.mutable_gpu_options()->set_allow_growth(true);
		opts.config.set_allow_soft_placement(true);
		//opts.config.set_log_device_placement(true);

		// create a new session
		TF_CHECK_OK(NewSession(opts, &session));

		// Add the graph to the session
		status = session->Create(metaGraph_def.graph_def());
		if (!status.ok()) {
			throw runtime_error("Error creating graph: " + status.ToString());
		}

		// Initialize our variables
		TF_CHECK_OK(session->Run({}, {}, { "init_global_vars_op" }, nullptr));

		// Read weights from the saved checkpoint
		Tensor checkpointPathTensor(DT_STRING, TensorShape());
		checkpointPathTensor.scalar<std::string>()() = checkpointPath;
		status = session->Run({ { metaGraph_def.saver_def().filename_tensor_name(), checkpointPathTensor }, },
		{}, { metaGraph_def.saver_def().restore_op_name() }, nullptr);
		if (!status.ok()) {
			throw runtime_error("Error loading checkpoint from " + checkpointPath + ": " + status.ToString());
		}
		//LOG(INFO) << "Load the checkpoint finished.";
		std::cout << "Load the checkpoint finished."<<std::endl;
	} else {
		//LOG(INFO) << "No method..";
		std::cout<< "No method.."<<std::endl;
	}


	struct ImgInfo info = { window_width, window_height,batch,factor };
	std::queue<std::pair<Tensor, Tensor>> queueTensor;
	
	dataSampler::DataProducer pTensor(ok_folder, ng_folder, queueTensor);
	dataSampler::DataConsumer cTensor(queueTensor,root_dir);
	epoches = epoches / 5;

	std::thread producer_thread1(&DataProducer::run, &pTensor, epoches,info);
	std::thread producer_thread2(&DataProducer::run, &pTensor, epoches,info);
	std::thread producer_thread3(&DataProducer::run, &pTensor, epoches,info);
	std::thread producer_thread4(&DataProducer::run, &pTensor, epoches,info);
	std::thread producer_thread5(&DataProducer::run, &pTensor, epoches,info);
	//std::thread producer_thread6(&DataProducer::run, &pTensor, epoches,info);
	//std::thread producer_thread7(&DataProducer::run, &pTensor, epoches,info);
	//std::thread producer_thread8(&DataProducer::run, &pTensor, epoches,info);
	//std::thread producer_thread9(&DataProducer::run, &pTensor, epoches,info);
	//std::thread producer_thread10(&DataProducer::run, &pTensor, epoches,info);

	std::thread consumer_thread(&DataConsumer::run, &cTensor, session, step, method);
	producer_thread1.join();
	producer_thread2.join();
	producer_thread3.join();
	producer_thread4.join();
	producer_thread5.join();
	//producer_thread6.join();
	//producer_thread7.join();
	//producer_thread8.join();
	//producer_thread9.join();
	//producer_thread10.join();
	consumer_thread.join();

	session->Close();
	delete session;

	auto end = std::chrono::system_clock::now();
	std::cout << "Total training time:"
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
