//Standard
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//opencv
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>

int main(){
	/*
	cv::VideoCapture cap(0);
	if (!cap.isOpened()){
		std::cout << "Camera not Found" << std::endl;
		return -1;
	}
	*/

	//variable
	cv::Mat inMat = cv::imread("IMGP0518.JPG");	//image input
	cv::Mat hsvMat;
	const int height = inMat.rows;
	const int width = inMat.cols;
	short *dst = new short[width*height]; //labeling
	cv::Mat outMat(height, width, CV_8UC3); //image ouput

	cv::imshow("input", inMat);
	cv::waitKey(0);

	cv::cvtColor(inMat, hsvMat, CV_BGR2HSV);
	cv::imshow("hsv", hsvMat);
	cv::waitKey(0);

	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			int index = hsvMat.step*y + (x * 3);
			if (hsvMat.data[index] >= 50 &&
				hsvMat.data[index] <= 70 &&
				hsvMat.data[index + 1] >= 90 &&
				hsvMat.data[index + 2] >= 90)
			{
				outMat.data[index] = hsvMat.data[index];
				outMat.data[index + 1] = hsvMat.data[index + 1];
				outMat.data[index + 2] = hsvMat.data[index + 2];
			}
		}
	}
	cv::imshow("output", outMat);
	cv::waitKey(0);
	return 0;
}