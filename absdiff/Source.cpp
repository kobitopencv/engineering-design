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

//--MatResize--//
cv::Mat MatResize(cv::Mat src, int height, int width){
	const int src_height = src.rows;
	const int src_width = src.cols;
	double mag_height, mag_width;
	mag_height = height / (double)src_height;
	mag_width = width / (double)src_width;
	cv::Mat dst;
	cv::resize(src, dst, cv::Size(), mag_width, mag_height);
	return dst;
}

int main(){

	//--variable--//
	cv::Mat bgMat = cv::imread("bgMat.JPG");	//input background image
	cv::Mat srcMat = cv::imread("srcMat.JPG");	//input source image
	if (srcMat.empty() || bgMat.empty()) return -1;
	cv::Mat result;

	cv::Mat RebgMat = MatResize(bgMat, 480, 640);
	cv::Mat ResrcMat = MatResize(srcMat, 480, 640);

	cv::imshow("source", ResrcMat);
	cv::imshow("background", RebgMat);
	cv::waitKey(0);

	cv::absdiff(ResrcMat, RebgMat, result);

	cv::imshow("result", result);
	//--WriteImage--//
	cv::imwrite("result.jpg", result);
	cv::waitKey(0);
	return 0;
}