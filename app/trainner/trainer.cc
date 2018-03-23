/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
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
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/public/session_options.h"
#include <tensorflow/core/protobuf/meta_graph.pb.h>

#include <direct.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "dataSampler.h"
#include "glog/logging.h"
#include "misc.h"
#define NUM_THREADS 5


using namespace tensorflow;
using namespace tensorflow::ops;
using namespace cv;
using namespace std;
using namespace dataSampler;

static bool glogInit = false;
int initGlog(string logDirStr,char* argv) {
	// glog init
	google::InitGoogleLogging(argv);
	google::SetLogDestination(google::GLOG_INFO, (logDirStr + "/info").c_str());
	google::SetLogDestination(google::GLOG_WARNING, (logDirStr + "/warn").c_str());
	google::SetLogDestination(google::GLOG_ERROR, (logDirStr + "/error").c_str());
	FLAGS_max_log_size = 10;
#ifdef SAVE_LOG
	FLAGS_logtostderr = false;  // save log to file
#endif
	glogInit = true;

	LOG(INFO) << "Start log!";

	return 0;
}

template <class T> void safe_delete(T*& pointer)
{
	if (pointer) { delete pointer; }
	pointer = nullptr;
}
template <class T> void safe_delete(std::vector<T*>& pointer_v)
{
	for (auto& pointer : pointer_v)
	{
		safe_delete(pointer);
	}
}

int main(int argc, char* argv[]) {
	std::string graph = "model/trainGraph/gpuTrainer.pb";
	std::string config = "tf_train.ini";
	string ok_folder = "./data/train/ok/";
	string ng_folder = "./data/train/ng/";
	int32 input_height = 850;
	int32 input_width = 643;
	int32 window_height = 822;
	int32 window_width = 612;
	int factor = 3;
	int batch = 32;
	int epoches = 1000;
	int step = 1000;
	int method = 1;
	string root_dir = ".";

	std::vector<Flag> flag_list = {
        Flag("method", &method, "load graph method(1:load graph.pb, 2: load checkpoint file)."),
        Flag("config", &config, "load config file for training."),
		Flag("graph", &graph, "graph to be executed."),
		Flag("save_step", &step, "save step interval."),
		Flag("ok", &ok_folder, "good samples folder."),
		Flag("ng", &ng_folder, "not good samples folder."),
		Flag("root_dir", &root_dir, "interpret image and graph file names relative to this directory."),
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
	
	//glog init
	string log_dir = "./log";
	if (!pathExist(log_dir)) {
		_mkdir(log_dir.c_str());
	}
	initGlog(log_dir, argv[0]);

	auto start = std::chrono::system_clock::now();

	//define session and graph
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
		LOG(INFO) << "Starting to restore the checkpoint.";
		fprintf(stdout,"Starting to restore the checkpoint.\n");
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
		LOG(INFO) << "Load the checkpoint finished.";
		fprintf(stdout,"Load the checkpoint finished.\n");
	} else {
		LOG(INFO) << "No method..";
		fprintf(stdout, "No method.\n");
	}


	std::queue<std::pair<Tensor, Tensor>> queueTensor;
	
	dataSampler::DataProducer pTensor(config, ok_folder, ng_folder, queueTensor);
	dataSampler::DataConsumer cTensor(queueTensor,root_dir);
	epoches = epoches / NUM_THREADS;

	std::vector<std::thread*> net_threads(NUM_THREADS);
	for (int i = 0; i < net_threads.size(); i++) {
		net_threads[i] = new std::thread{ &DataProducer::run, &pTensor };
	}

	std::thread consumer_thread(&DataConsumer::run, &cTensor, session, step, method);
	for (int i = 0; i < net_threads.size(); i++) {
		net_threads[i]->join();
	}
	consumer_thread.join();

	safe_delete(net_threads);
	session->Close();
	delete session;

	auto end = std::chrono::system_clock::now();
	std::string time_str = "Total training time:" + to_string(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()) + "s.\n";
	fprintf(stdout, time_str.c_str());
	LOG(INFO) << "Total training time:" << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	// glog close
	if (glogInit == true) {
		LOG(INFO) << "Close the program.";
		google::ShutdownGoogleLogging();
	}
	system("pause");
	return 0;
}



