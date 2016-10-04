//Standard
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//opencv
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>

int main(){
	/*
	cv::VideoCapture cap(0);
	if (!cap.isOpened()){
		std::cout << "Camera not Found" << std::endl;
		return -1;
	}
	*/

	//--variable--//
	cv::Mat inMat = cv::imread("sample.jpg");	//image input
	cv::Mat hsvMat;
	const int height = inMat.rows;
	const int width = inMat.cols;
	short *dst = new short[width*height]; //labeling
	cv::Mat outMat = cv::Mat(cv::Size(width, height), CV_8UC1); //image ouput
	uchar hue, sat, val;

	cv::imshow("input", inMat);
	cv::waitKey(0);

	cv::cvtColor(inMat, hsvMat, CV_BGR2HSV);
	cv::imshow("hsv", hsvMat);
	cv::waitKey(0);

	//--yellow detection--//
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			//--HSV--//
			hue = hsvMat.at<cv::Vec3b>(y, x)[0];
			sat = hsvMat.at<cv::Vec3b>(y, x)[1];
			val = hsvMat.at<cv::Vec3b>(y, x)[2];
			//--threshold--//
			if (hue < 40 && sat < 80 && val > 230)
				outMat.at<uchar>(y, x) = 0;
			else 
				outMat.at<uchar>(y, x) = 255;
		}
	}

	//--namber detection--//
	cv::Mat bil = cv::Mat(cv::Size(width, height), CV_8UC1);
	cv::bilateralFilter(outMat, bil, 20, 90, 200);
	cv::imwrite("ouMat.jpg", bil);

	//cv::imshow("output", bil);
	cv::waitKey(0);
	return 0;
}