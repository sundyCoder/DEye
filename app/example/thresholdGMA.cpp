
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/types.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
void Threshold_Demo(int, void*);

int main_gma(int, char** argv)
{
	std::string img_name = R"(D:\data\gma\6A0KW_P4003XXXXXXXXXX.jpg)";
	src = imread(img_name, 1);
	vector<cv::Mat> mv;
	mv.push_back(cv::Mat());
	mv.push_back(cv::Mat());
	mv.push_back(cv::Mat());
	cv::split(src, mv);
	mv[1].copyTo(src_gray);
	//cvtColor(src, src_gray, COLOR_RGB2GRAY);
#if 1
	//threshold(src_gray, dst, 78, 255, 1);
	threshold(src_gray, dst, 131, 255, 0);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	RotatedRect rect;
	//Rect roi_rect(207,174,456,861);
	//cv::Rect roi_rect(168, 1221, 212, 106);        // left pad region
	cv::Rect roi_rect(492, 1211, 194, 117);       // right pad region
	cv::Mat roi_dst = dst(roi_rect);
	findContours(roi_dst, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	for (int i = 0; i < contours.size(); i++) {
		rect = minAreaRect(contours[i]);
		Rect brect = rect.boundingRect();
		std::cout<< "size(" << i <<"):"<< brect.area() << std::endl;
		cv::rectangle(roi_dst, brect, cv::Scalar(255), 2);
		//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	imwrite("D:/result.png", roi_dst);
	system("pause");
	return 0;
#endif
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type, Threshold_Demo);
	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value, Threshold_Demo);
	Threshold_Demo(0, 0);
	for (;;)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}
	return 0;
}
void Threshold_Demo(int, void*)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow(window_name, dst);
}