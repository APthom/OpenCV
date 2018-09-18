#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;

int R, G, B;
int bright = 150;
int contrast = 1;
cv::Mat img;

static void on_trackbar(int, void*)
{
	//cv::Mat mypic = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);
	//cv::rectangle(mypic, cv::Rect(0, 0, mypic.cols, mypic.rows),
		//cv::Scalar( B, G, R), -1);
	cv::Mat image;
	int ib = bright;
	int con = 1;
	image.convertTo(image, -1, con, ib);


	cv::imshow("adjust", img);

}

void on_bright(int n, void*)
{
	cv::Mat img_tmp;
	img.convertTo(img_tmp, -1, contrast, bright - 150);
	cv::imshow("adjust", img_tmp);
}

void brightnessandcontrast()
{
	cv::createTrackbar("brightness", "adjust", &bright, 300, on_bright);
	cv::createTrackbar("contrat", "adjust", &contrast, 4, on_bright);
}


bool checkred(cv::Mat input) {

	int red = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[2];
	int green = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[1];
	int blue = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[0];

	if (red > 150 && green > 150 && blue > 150) {
		return true;
	}
	else
		return false;

}

bool checkred_hsv(cv::Mat input) {
	int H = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[0];
	int S = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[1];
	int V = input.at<cv::Vec3b>(input.cols / 2, input.rows / 2)[2];

	cout << "H = " << H << "S = " << S << "V = " << V << endl;

	if ((H > 165 || H < 15) && (V > 20 && V < 230) && (S > 50)) {
		return true;
	}
	else
		return false;
}

int main()
{
	cv::Mat image;
	cv::Mat gray;
	//int pixel;

	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		return -1;

	}

	while (true)
	{
		cv::Mat frame;
		cv::Mat gray;
		cap >> frame;

		cv::Mat rgb = frame.clone();
		cv::Mat hsv;
		vector<cv::Mat> rgb_channels, hsv_channels;
		cv::split(rgb, rgb_channels);

		cv::cvtColor(rgb, hsv, cv::COLOR_BGR2HSV);
		cv::split(hsv, hsv_channels);
		
		//cv::imshow("RGB", rgb);
		//cv::imshow("H", hsv_channels[0]);
		//cv::imshow("S", hsv_channels[1]);
		//cv::imshow("V", hsv_channels[2]);


		//hsv_channels[1] = hsv_channels[1] - cv::Scalar(100);
		//cv::merge(hsv_channels, hsv);
		//cv::cvtColor(hsv, hsv, cv::COLOR_HSV2BGR);

		//cv::imshow("RGB", rgb);
		//cv::imshow("RGB+sat", hsv);

		//cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		//img = frame.at<cv::Vec3b>(frame.cols / 2, frame.rows / 2);
		cv::circle(frame,cv::Point(frame.cols/2,frame.rows/2),1,
			cv::Scalar(0, 0, 255), -1);
		int redd = frame.at<cv::Vec3b>(frame.cols / 2, frame.rows / 2)[2];
		if (checkred(frame)) {
			//cv::putText(frame, "red", cv::Point(10, 20),
				//cv::FONT_HERSHEY_SIMPLEX, 0.5,
				//cv::Scalar(0,0,255));
			cout << redd << endl;
		}

		checkred_hsv(hsv);
		
		cv::imshow("output", frame);
		cv::waitKey(10);
	}

	//image = cv::imread("D:\\Wick\\Univeraity\\4\\computer_vision\\apple.jpg");
	//cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

	img = cv::imread("D:\\Wick\\Univeraity\\4\\computer_vision\\apple.jpg");

	// วาดรูปต่าง ๆ
	//cv::Mat mypic = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);
	//cv::rectangle(mypic, cv::Rect(0, 0, mypic.cols, mypic.rows), 
		//cv::Scalar(200, 150, 250), -1);

	/*on_trackbar(R, 0);
	string TrackR;
	string TrackG;
	string TrackB;
	TrackR = "R = %d" + R;
	TrackG = "G = %d" + G;
	TrackB = "B = %d" + B;
	cv::namedWindow("adjust", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar(TrackR, "adjust", &R, 255, on_trackbar);
	cv::createTrackbar(TrackG, "adjust", &G, 255, on_trackbar);
	cv::createTrackbar(TrackB, "adjust", &B, 255, on_trackbar);*/

	
	cv::namedWindow("adjust", cv::WINDOW_AUTOSIZE);
	//cv::createTrackbar("brightness", "adjust", &bright, 255, on_trackbar);
	on_trackbar(bright, 0);
	brightnessandcontrast();

	/*cv::circle(mypic, cv::Point(mypic.cols / 2, mypic.rows / 2), 20,
		cv::Scalar(0, 255, 255), 3);

	cv::line(mypic, cv::Point(0, mypic.rows), cv::Point(mypic.cols / 2, mypic.rows / 2),
		cv::Scalar(0, 127, 0), 3);*/


	//cv::line(mypic, cv::Point(mypic.cols / 2, mypic.rows / 2), cv::Point(mypic.cols, mypic.rows),
		//cv::Scalar(0, 127, 0), 3);

	//------------

	cv::Mat output = gray.clone();
	cv::Mat color = image.clone();


	for (int x = 0; x < output.cols; x++)
	{
		for (int y = output.rows/2; y < output.rows; y++)
		{
			int pixel = output.at<uchar>(y, x);
			output.at<uchar>(y, x) = -pixel;

		}
	}

	for (int x = 0; x < color.cols; x++)
	{
		for (int y = 0; y < color.rows; y++)
		{
			cv::Vec3b pixel = color.at<cv::Vec3b>(y, x);
			pixel.val[0] = 255 - pixel.val[0];
			pixel.val[2] = 255 - pixel.val[2];
			pixel.val[1] = 255 - pixel.val[1];
			color.at<cv::Vec3b>(y, x) = pixel;

		}
	}

	//gray.at<uchar>(10, 20) = 0;
	//pixel = gray.at<uchar>(10, 10);

	//cv::imshow("apple", image);
	//cv::imshow("output", output);
	//cv::imshow("gray", gray);
	//cv::imshow("color", color);
	//cv::imshow("pic", mypic);
	//cv::imshow("adjust", img);

	cv::waitKey(0);

}