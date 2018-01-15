#include<opencv2/opencv.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include "libconvert.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace cv;
using namespace std;

int sampleSize_= 256;

int main2() {
	std::ifstream infile("H:/dbot/png/file.txt");
	string root_folder = "H:/dbot/NG/";
	string file;
	while (std::getline(infile, file)) {
		std::cout << "Processing " << file << std::endl;
		size_t pos = file.find_last_of('\/');
		string ori_name = file.substr(pos + 1);
		pos = ori_name.find_last_of('.');
		ori_name = ori_name.substr(0,pos) + ".tiff";
		cv::Mat ori_img = imread(root_folder + ori_name,1);
		if (!ori_img.data) {
			std::cout << "Could not read or found " << ori_name << std::endl;
			system("pause");
			return 1;
		}

		cv::Mat mask_img = imread(file, 0);
		if (!mask_img.data) {
			std::cout << "Could not read or find " << file << std::endl;
			system("pause");
			return 1;
		}
		vector<vector<Point>> contours;
		cv::findContours(mask_img, contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		Mat dst_contour = Mat::zeros(mask_img.size(), CV_8UC1); //最小外接矩形画布  
		drawContours(dst_contour, contours, -1, Scalar(255), CV_FILLED);

		FILE *fpLabel = fopen((root_folder + "label/"+ ori_name + "_.txt").c_str(), "wb");
		for (int i = 0; i<contours.size(); i++){
			cv::Rect bRect = boundingRect(contours[i]);
			if (bRect.width<sampleSize_)
			{
				int diffx = sampleSize_ - bRect.width;
				if ((bRect.x + sampleSize_) > mask_img.cols)
				{
					bRect.x = bRect.x - diffx;
					bRect.width = sampleSize_;
				}
				else {
					bRect.x = bRect.x - diffx / 2;
					if (bRect.x < 0) {
						bRect.x = 0;
					}
					bRect.width = sampleSize_;
				}
			}

			if (bRect.height<sampleSize_)
			{
				int diffy = sampleSize_ - bRect.height;
				if ((bRect.y + sampleSize_) > mask_img.rows)
				{
					bRect.y = bRect.y - diffy;
					bRect.height = sampleSize_;
				}
				else {
					bRect.y = bRect.y - diffy / 2;
					if (bRect.y < 0) {
						bRect.y = 0;
					}
					bRect.height = sampleSize_;
				}
			}

			// save label txt
			string str;
			convert::formatAppendString(str, "%d, %d, %d, %d", bRect.x, bRect.y, bRect.width, bRect.height);
			convert::writeStringAppendToFile(str, fpLabel);

			//save cancer
			string cancer_name = root_folder + "cancer/" + ori_name + to_string(i) + "@_" + to_string(bRect.x) + "_" + to_string(bRect.y) + ".png";
			cv::Mat sub_img = ori_img(bRect);
			imwrite(cancer_name,sub_img);

			// save mask
			string mask_name = cancer_name + "_mask.png";
			cv::Mat mask_mat = dst_contour(bRect);
			imwrite(mask_name,mask_mat);
		}

		fclose(fpLabel);
	}

    system("pause");
	return 0;
}