/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#include "CaffeDataGen.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>     // std::string, std::stof

using namespace cv;
using namespace caffeData;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please input the data type." << std::endl;
		system("pause");
		return 0;
	}
	int data_type = stoi(argv[1]);
	if (data_type == OKDATA) {
		if (argc < 6) {
			std::cout << "Please input the data paras(w,h,nums)." << std::endl;
			system("pause");
			return 0;
		}
		else {
			int width = stoi(argv[2]);
			int height = stoi(argv[3]);
			int nums = stoi(argv[4]);
			string dataOKDir = argv[5];
			CaffeData gendata(dataOKDir, dataOKDir);
			gendata.genOKData(width, height, nums);
		}
	}
	else if (data_type == NGDATA) {
		if (argc < 8) {
			std::cout << "Please input the data paras(w,h,nums,min,ratio,total)." << std::endl;
			system("pause");
			return 0;
		}
		else {
			int width = stoi(argv[2]);
			int height = stoi(argv[3]);
			int nums = stoi(argv[4]);
			struct paraData para = { stoi(argv[5]),stof(argv[6]), stoi(argv[7]) };
			string dataNGDir = argv[8];
			CaffeData gendata(dataNGDir, dataNGDir);
			gendata.genNGData(width, height, nums, para);
		}
	} else if (data_type == GAUDATA) {
		string strDir = argv[2];
		CaffeData gendata(strDir, strDir);
		gendata.gaussianData();
	}

	std::cout << "Gen data finished!" << std::endl;
	return 0;
}