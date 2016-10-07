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
	if (inMat.empty()) return -1;
	cv::Mat hsvMat;
	const int height = inMat.rows;
	const int width = inMat.cols;
	short *dst = new short[width*height]; //labeling
	cv::Mat outMat = cv::Mat(cv::Size(width, height), CV_8UC3); //image ouput
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
			if (hue < 40 && sat < 80 && val > 230){
				outMat.at<cv::Vec3b>(y, x)[0] = 0;
				outMat.at<cv::Vec3b>(y, x)[1] = 255;
				outMat.at<cv::Vec3b>(y, x)[2] = 0;
			}
			else{
				outMat.at<cv::Vec3b>(y, x)[0] = 255;
				outMat.at<cv::Vec3b>(y, x)[1] = 255;
				outMat.at<cv::Vec3b>(y, x)[2] = 255;
			}
		}
	}

	//--namber detection--//
	cv::Mat bil = cv::Mat(cv::Size(width, height), CV_8UC3);
	cv::bilateralFilter(outMat, bil, 20, 90, 200);

	//--HoughLines--//
	cv::Mat cny;
	cv::Canny(bil, cny, 50, 200, 3);
	cv::imshow("canny", cny);
	cv::waitKey(0);
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(cny, lines, 1, CV_PI / 180, 200, 0, 0);

	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it){
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(bil, pt1, pt2, cv::Scalar(0, 0, 255), 3, CV_AA);
	}

	cv::imshow("output", bil);
	cv::waitKey(0);
	return 0;
}