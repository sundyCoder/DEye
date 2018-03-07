/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Mar 07,2018
************************************************************************/

//train.cpp
#include <opencv2/opencv.hpp>
//#include <opencv2/ml.hpp>

#include <iostream>
#include <string>
//#include "util/imageutils.h"
#include "DataSetManager.h"



using namespace std;
using namespace cv;
using namespace cv::ml;



HOGDescriptor hog(
	Size(128, 128), //winSize
	Size(8, 8), //blocksize
	Size(8, 8), //blockStride,
	Size(8, 8), //cellSize,
	9, //nbins,
	1, //derivAper,
	-1, //winSigma,
	0, //histogramNormType,
	0.2, //L2HysThresh,
	0,//gammal correction,
	128,//nlevels=64
	1);




void getSVMParams(SVM *svm)
{
	cout << "Kernel type     : " << svm->getKernelType() << endl;
	cout << "Type            : " << svm->getType() << endl;
	cout << "C               : " << svm->getC() << endl;
	cout << "Degree          : " << svm->getDegree() << endl;
	cout << "Nu              : " << svm->getNu() << endl;
	cout << "Gamma           : " << svm->getGamma() << endl;
}

void SVMtrain(Mat &trainMat, vector<int> &trainLabels, Mat &testResponse, Mat &testMat) {
	Ptr<SVM> svm = SVM::create();
	svm->setGamma(0.50625);
	svm->setC(100);
	svm->setKernel(SVM::RBF);
	svm->setType(SVM::C_SVC);
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
	svm->train(td);
	//svm->trainAuto(td);
	svm->save("firetrain.yml");
	svm->predict(testMat, testResponse);
	getSVMParams(svm);

	/*
	To acheive 100% rate.
	Descriptor Size : 576
	Kernel type     : 2
	Type            : 100
	C               : 2.5
	Degree          : 0
	Nu              : 0
	Gamma           : 0.03375
	the accuracy is :100

	*/

}

void SVMevaluate(Mat &testResponse, float &count, float &accuracy, vector<int> &testLabels) {

	for (int i = 0; i<testResponse.rows; i++)
	{
		//cout << testResponse.at<float>(i,0) << " " << testLabels[i] << endl;
		if (testResponse.at<float>(i, 0) == testLabels[i]) {
			count = count + 1;
		}
	}
	accuracy = (count / testResponse.rows) * 100;
}
void computeHOG(vector<Mat> &inputCells, vector<vector<float> > &outputHOG) {

	for (int y = 0; y<inputCells.size(); y++) {
		vector<float> descriptors;
		hog.compute(inputCells[y], descriptors);
		outputHOG.push_back(descriptors);
	}
}
void ConvertVectortoMatrix(vector<vector<float> > &ipHOG, Mat & opMat)
{

	int descriptor_size = ipHOG[0].size();
	for (int i = 0; i<ipHOG.size(); i++) {
		for (int j = 0; j<descriptor_size; j++) {
			opMat.at<float>(i, j) = ipHOG[i][j];
		}
	}
}

int main(int argc, char ** argv)
{

	/**************** user code starts *******************/
	cout << " User code starts" << endl;
	DataSetManager dm;
	dm.addData("pos", 1);// positive train data
	dm.addData("neg", -1);// negative train data
							   //dm.addData("./testfolder/test/",1);// test data
							   // can also provide fullpath "/home/pankaj/opencv/programs/udacity/carND/cardetection"
							   //dm.addData("./vehicles/vehicles/",2);
	cout << "Total data length : " << dm.getTotalDataNum() << endl;
	dm.distribute();
	dm.display();
	/***********load all the dataset into vector of Mat*********/
	vector<Mat> trainCells;
	vector<Mat> testCells;
	vector<int> trainLabels;
	vector<int> testLabels;
	for (int i = 0; i<dm.getTotalTrainDataNum(); i++) {
		string imageName = dm.TrainData[i].filename;
		Mat img = imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);
		trainCells.push_back(img);
		trainLabels.push_back(dm.TrainData[i].label);
	}
	for (int i = 0; i<dm.getTotalTestDataNum(); i++) {
		string imageName = dm.TestData[i].filename;
		Mat img = imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);
		testCells.push_back(img);
		testLabels.push_back(dm.TestData[i].label);
	}
	//loadTrainTestLabel(pathName,trainCells,testCells,trainLabels,testLabels);
	/***********Computer HOG descriptor for all the training and testcells *********/
	std::vector<std::vector<float> > trainHOG;
	std::vector<std::vector<float> > testHOG;

	//compute_hog(trainCells, gradient_lst);
	computeHOG(trainCells, trainHOG);
	computeHOG(testCells, testHOG);

	int descriptor_size = trainHOG[0].size();
	cout << "Descriptor Size : " << descriptor_size << endl;
	/******** HOG descriptor ends ****************************/

	/********Prepeare trainData and test data and call SVM ML algorithm*********/
	Mat trainMat(trainHOG.size(), descriptor_size, CV_32FC1);
	Mat testMat(testHOG.size(), descriptor_size, CV_32FC1);
	ConvertVectortoMatrix(trainHOG, trainMat);
	ConvertVectortoMatrix(testHOG, testMat);

	Mat testResponse;
	SVMtrain(trainMat, trainLabels, testResponse, testMat);

	float count = 0;
	float accuracy = 0;
	SVMevaluate(testResponse, count, accuracy, testLabels);

	cout << "the accuracy is :" << accuracy << endl;

	/**************** user code ends *******************/

	system("pause");
	//char ch;
	//cin >> ch;
	return 0;
}