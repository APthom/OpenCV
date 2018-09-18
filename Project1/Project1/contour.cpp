#include <iostream>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#define IMAGE "D:\\Wick\\Univeraity\\4\\computer_vision\\apple.jpg"

int findBiggestContour(vector<vector<cv::Point>> contours)
{
	vector<cv::Moments> mu(contours.size());

	int max_area = 0;
	int max_index = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = cv::moments(contours[i]);
		if (max_area < mu[i].m00)
		{
			max_area = mu[i].m00;
			max_index = i;
		}
	}

	return max_index;

}



int main()
{
	cv::Mat apple;
	apple = cv::imread(IMAGE);
	cv::Mat applehsv;
	cv::cvtColor(apple, applehsv, cv::COLOR_BGR2HSV);
	vector<cv::Mat> channels;
	cv::split(applehsv, channels);
	cv::Mat green;
	cv::inRange(channels[0], 30, 50, green);

	cv::Mat eroded;
	cv::Mat se;
	se = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(5, 5),
		cv::Point(2,2));
	cv::erode(green, eroded, se);

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;

	cv::findContours(eroded, contours, hierarchy,
		CV_RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

	cv::Mat drawing(green.size(), CV_8UC3);

	int i_big = findBiggestContour(contours);

	cv::drawContours(drawing, contours, i_big,
		cv::Scalar(0, 0, 255), -1);

	cv::Moments m_big = cv::moments(contours[i_big]);
	cv::Point centroid_big;
	centroid_big.x = m_big.m10 / m_big.m00;
	centroid_big.y = m_big.m01 / m_big.m00;

	cv::circle(drawing, centroid_big, 2, cv::Scalar(0, 255, 0),
		-1);

	cv::imshow("green", green);
	cv::imshow("erosion", eroded);
	cv::imshow("contour", drawing);
	//cv::imshow("h", channels[0]);
	//cv::imshow("s", channels[1]);
	//cv::imshow("v", channels[2]);
	cv::imshow("apple", apple);
	cv::waitKey(0);

}