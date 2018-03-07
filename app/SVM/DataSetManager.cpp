/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Mar 07,2018
************************************************************************
//DataSetManager.cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "DataSetManager.h"
#include <algorithm>

using namespace cv;
using std::cout;
using std::endl;
using std::string;

#define EN_DEBUG

//constructor
DataSetManager::DataSetManager() :testDataPercent(20), validationDataPercent(0), totalDataNum(0), totalTrainDataNum(0), totalTestDataNum(0) {
	// default parameter initialization here
}
// setter and getter methods

void DataSetManager::setTestDataPercent(float num) { testDataPercent = num; }
void DataSetManager::setValidationDataPercent(float num) { validationDataPercent = num; }
int DataSetManager::getTotalDataNum() { return totalDataNum; }
int DataSetManager::getTotalTrainDataNum() { return totalTrainDataNum; }
int DataSetManager::getTotalTestDataNum() { return totalTestDataNum; }

//main functions
void DataSetManager::addData(std::string folderName, int classlabel) {
	// notice here that we are using the Opencv's embedded "String" class 
	std::vector<cv::String> filenames;
	cv::String folder = folderName.c_str();// converting from std::string->cv::String
	cv::glob(folder, filenames);
	// for each of these fileNames append them into the DataSet structure with labels
	for (size_t i = 0; i < filenames.size(); i++) {
		DataSet tempDataset;
		tempDataset.filename = static_cast<std::string>(filenames[i]);
		tempDataset.label = classlabel;
		dataList.push_back(tempDataset);
	}
	totalDataNum = totalDataNum + filenames.size();
}

// the distribute functions distributes the whole data into training data and test data.
void DataSetManager::distribute() {
	int n_test_valid = static_cast<int> (
		(validationDataPercent*totalDataNum / 100) + (testDataPercent*totalDataNum / 100));
	//cout<<" n_test_valid == "<< n_test_valid<<endl;
	int counter = 0;
	std::vector<int> rndIndex;
	std::vector<int>::iterator it;
	DataSet tempDataset;
	while (counter < n_test_valid) {
		// random number between [0-totalDataNum-1]
		int num = rand() % totalDataNum;
		it = std::find(rndIndex.begin(), rndIndex.end(), num);
		if (it != rndIndex.end())
			continue;//skip the rest of the loop if this num is already present
					 //we are here only if the 'num' is unique
		rndIndex.push_back(num);
		//cout<<" random number == "<< num<<endl;
		tempDataset.filename = static_cast<std::string>(dataList[num].filename);
		tempDataset.label = dataList[num].label;
		TestData.push_back(tempDataset);
		counter++;
	}
	std::sort(rndIndex.begin(), rndIndex.end());//sort in ascending order
#ifdef EN_DEBUG
	cout << "sortedIndexes: " << endl;
	for (std::vector<int>::iterator it = rndIndex.begin(); it != rndIndex.end(); ++it)
		cout << " " << *it << endl;
	cout << endl;
#endif 

	//cout<<" now fill the TrainData; only exclude the testData"<<endl;

	int curIdx = 0;
	int current = rndIndex[curIdx];
	//cout<<"rndIndex.size()= "<<rndIndex.size()<<endl;
	for (int i = 0; i < dataList.size(); i++) {
		//cout<<" current == "<< current<<" i = "<<i<<" curIndx= "<< curIdx;
		if (i != current) {
			//cout<<" inside Train";
			tempDataset.filename = static_cast<std::string>(dataList[i].filename);
			tempDataset.label = dataList[i].label;
			TrainData.push_back(tempDataset);
		}
		else if ((current == i) && (curIdx < rndIndex.size() - 1)) {
			//cout<<" inside Test";
			current = rndIndex[++curIdx];
		}
	}

	totalTrainDataNum = TrainData.size();
	totalTestDataNum = TestData.size();
}
void DataSetManager::display() {

	// display Data
	cout << "Training data length: " << getTotalTrainDataNum() << endl;
#ifdef EN_DEBUG
	for (int i = 0; i < getTotalTrainDataNum(); i++) {
		cout << " filename: " << TrainData[i].filename;
		cout << "	\tlabels: " << TrainData[i].label << endl;
	}
#endif
	cout << "Test data length: " << getTotalTestDataNum() << endl;
#ifdef EN_DEBUG
	for (int i = 0; i < getTotalTestDataNum(); i++) {
		cout << " filename: " << TestData[i].filename;
		cout << " \tlabels: " << TestData[i].label << endl;
	}
#endif

}