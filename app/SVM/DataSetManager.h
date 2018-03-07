/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Mar 07,2018
************************************************************************

#ifndef _DATASETMANAGER_H
#define _DATASETMANAGER_H

#include <iostream>

struct DataSet {
	std::string filename;
	float label;
};

class DataSetManager
{
private:
	// user defined data member
	float testDataPercent;
	float validationDataPercent;

	// derrived or internally calculated
	int totalDataNum;
	int totalTrainDataNum;
	int totalTestDataNum;
	int totalValidationDataNum;

public:
	//constructor
	DataSetManager();

	// setter and getter methods
	void setTestDataPercent(float num);
	void setValidationDataPercent(float num);

	int getTotalDataNum();
	int getTotalTrainDataNum();
	int getTotalTestDataNum();
	int getTotalValidationDataNum();

	// primary functions of the class
	void addData(std::string folderName, int classlabel);
	void read();
	void display();// displays the read file names for debugging
	void distribute();
	// ideally these are private; need to update
	std::vector<DataSet> dataList;
	std::vector<DataSet> TrainData;
	std::vector<DataSet> TestData;
	std::vector<DataSet> ValidationData;
};

#endif