#include<iostream>
#include<string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#define image "D:\\Wick\\Univeraity\\4\\computer_vision\\coin.jpg"

#define image2 "D:\\Wick\\Univeraity\\4\\computer_vision\\not2.jpg"

int main()
{
	cv::Mat coin;
	coin = cv::imread(image2);
	cv::Mat nutandbolt = cv::imread(image2);

	cv::Mat input = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);

	cv::circle(input, cv::Point(200, 200), 20, CV_RGB(255, 0, 0), -1);
	cv::circle(input, cv::Point(100, 100), 30, CV_RGB(0, 255, 0), -1);
	cv::rectangle(input, cv::Rect(400, 100, 50, 50), CV_RGB(255, 0, 255), -1);
	cv::rectangle(input, cv::Rect(350, 300, 40, 80), CV_RGB(0, 255, 255), -1);

	cv::Mat gray, binary;

	cv::cvtColor(nutandbolt, gray, CV_BGR2GRAY);
	cv::threshold(gray, binary, 100, 255, CV_THRESH_BINARY_INV);

	vector<vector<cv::Point>> contours;       // ให้ set ของเส้นขอบของรูป
	vector<cv::Vec4i> hierarchy;

	cv::findContours(binary, contours, hierarchy, 
		CV_RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	//cv::Mat drawing(cv::Size(binary.size()), CV_8UC3);

	for (int i = 0; i < contours.size(); i++) {
		cv::Moments mo = cv::moments(contours[i]);
		double area = mo.m00;
		double peri = cv::arcLength(contours[i], true);
		cv::Rect bound = cv::boundingRect(contours[i]);
		cv::RotatedRect minRect = cv::minAreaRect(contours[i]);

		//minRect.angle
		//bound.height;
		cout << "area = " << mo.m00 << endl;
		cout << "perimeter = " << cv::arcLength(contours[i], true) << endl;
		cout << "circularity = " << (4.0*CV_PI*area) / (peri*peri) << endl;
		cout << "angle = " << minRect.angle << endl;
		cout << "aspect ratio = " << minRect.size.width / minRect.size.height << endl << endl;
	}

	cv::imshow("coin", nutandbolt);
	//cv::imshow("coin", input);
	cv::imshow("segment", binary);


	cv::waitKey(0);
}