
/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#include "misc.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;
#define M_PI       3.14159265358979323846

namespace caffeData {
	enum {
		OKDATA,
		NGDATA,
		GAUDATA,
	};

	// parameters for data generator
	typedef struct paraData {
		int min_count;   // the min pixel count 
		float count_ratio;
		int mask_total;
	}ParaData;

	class CaffeData {
	public:
		CaffeData(string strOK, string strNG);
		~CaffeData() {};

		int genOKData(int width, int height, int nums);
		int genNGData(int width, int height, int nums, ParaData para);

		int gaussianData();

	private:
		string strOKDir_;
		string strNGDir_;
	};

	CaffeData::CaffeData(string strOK, string strNG) :strOKDir_(strOK), strNGDir_(strNG) {
		srand(time(NULL));
	};

	int CaffeData::genOKData(int winWidth, int winHeight, int nums) {
		_mkdir("./OK/");
		auto files = get_files(strOKDir_, "/file.txt");
		std::sort(files.begin(), files.end());
		int dataBlob = 0;
		while (true) {
			for (auto fln : files) {
				std::cout << "##############" << fln << "##############" << std::endl;
				cv::Mat image_mat = cv::imread(strOKDir_ + fln, CV_LOAD_IMAGE_UNCHANGED);
				int oriWidth = image_mat.cols;
				int oriHeight = image_mat.rows;
				int chanel = image_mat.channels();

				if (image_mat.empty() || oriWidth < winWidth || oriHeight < winHeight) {
					std::cout << "Could not read " << fln << std::endl;
					continue;
				}

				int h_off = 0, w_off = 0;
				for (int i = 0; i < 2; i++) {
					w_off = Rand(oriWidth - winWidth);
					h_off = Rand(oriHeight - winHeight);
					cv::Rect rect = Rect(w_off, h_off, winWidth, winHeight);
					cv::Mat temp_mat = cv::Mat(image_mat, rect);
					dataBlob++;
					string blob_name = fln + "@" + to_string(dataBlob) + "_" + to_string(w_off) + "_" + to_string(h_off) + ".png";
					imwrite("./OK/"+blob_name, temp_mat);
					std::cout << "Gen:" << blob_name << std::endl;
					if (dataBlob >= nums) {
						return 1;
					}
				}
			}
		}
	}


	int CaffeData::genNGData(int winWidth, int winHeight, int nums, ParaData para) {
		_mkdir("./NG/");
		_mkdir("./NG/mask/");
		auto files = get_files(strNGDir_, "/file.txt");
		std::sort(files.begin(), files.end());
		int dataBlob = 0;
		while (true) {
			for (auto fln : files) {
				std::cout << "##############" << fln << "##############" << std::endl;
				cv::Mat image_mat = cv::imread(strNGDir_ + fln, CV_LOAD_IMAGE_UNCHANGED);
				int oriWidth = image_mat.cols;
				int oriHeight = image_mat.rows;
				int chanel = image_mat.channels();

				if (image_mat.empty() || oriWidth < winWidth || oriHeight < winHeight) {
					std::cout << "Could not read " << fln << std::endl;
					continue;
				}

				string mask_name = strNGDir_ + "mask/" + fln + "_mask.png";
				cv::Mat mask_mat = cv::imread(mask_name, 0);
				if (mask_mat.empty()) {
					std::cout << "Could not read the mask of" << fln << std::endl;
					continue;
				}

				int h_off = 0, w_off = 0;
				for (int i = 0; i < 2; i++) {
					w_off = Rand(oriWidth - winWidth);
					h_off = Rand(oriHeight - winHeight);
					cv::Rect rect = Rect(w_off, h_off, winWidth, winHeight);
					cv::Mat blob_mat = cv::Mat(image_mat, rect);
					cv::Mat blob_mask_mat = cv::Mat(mask_mat, rect);
					/////////
					int mask_white_count = 0;
					std::vector<std::vector<cv::Point>> contours;
					cv::findContours(mask_mat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
					for (int i_x = 0; i_x < mask_mat.cols; i_x++) {
						for (int i_y = 0; i_y < mask_mat.rows; i_y++) {
							auto point_value = mask_mat.at<uint8_t>(i_y, i_x);
							mask_white_count += point_value / 255.0;
						}
					}

					int count_white = 0;
					for (int i_w = 0; i_w < winWidth; i_w++) {
						for (int i_h = 0; i_h < winHeight; i_h++) {
							if (blob_mask_mat.at<uint8_t>(i_h, i_w) > 200) {
								count_white++;
							}
						}
					}

					//find the max contour
					double max_area = 0;
					std::vector<cv::Point> max_contour;
					for (size_t i = 0; i < contours.size(); i++) {
						double area = cv::contourArea(contours[i]);
						if (area > max_area) {
							max_area = area;
							max_contour = contours[i];
						}
					}

					if (max_area > para.min_count) {
						float radius;
						cv::Point2f center;
						cv::minEnclosingCircle(max_contour, center, radius);
						double distance = sqrt(pow((center.x - winWidth / 2), 2) + pow((center.y - winWidth / 2), 2));
						if (count_white >= (mask_white_count * para.count_ratio)) {
							if ((distance < (winWidth + winHeight) / 2 / 2 * 1.0) && (M_PI * radius * radius >= para.mask_total)) {
								dataBlob++;
								if (dataBlob > nums) {
									return 1;
								}
								string blob_name = fln + "@" + to_string(dataBlob) + "_" + to_string(w_off) + "_" + to_string(h_off) + ".png";
								imwrite("./NG/" + blob_name, blob_mat);
								string blob_mask_name = fln + "@" + to_string(dataBlob) + "_" + to_string(w_off) + "_" + to_string(h_off) + ".png";
								imwrite("./NG/mask/" + blob_mask_name, blob_mask_mat);
								std::cout << "Gen:" << blob_name << std::endl;
							}
						} 
					} 
				}
			}
		}
	}

	int CaffeData::gaussianData() {
		_mkdir("./GAU/");
		auto files = get_files(strOKDir_, "/file.txt");
		std::sort(files.begin(), files.end());
		int dataBlob = 0;
		for (auto fln : files) {
			std::cout << "##############" << fln << "##############" << std::endl;
			cv::Mat image_mat = cv::imread(strOKDir_ + fln, CV_LOAD_IMAGE_UNCHANGED);
			int smooth_param1 = 3 + 2 * (Rand(2));
			cv::GaussianBlur(image_mat, image_mat, cv::Size(smooth_param1, smooth_param1), 0);
			imwrite("./GAU/" + fln, image_mat);
		}
		return 0;
	}
}