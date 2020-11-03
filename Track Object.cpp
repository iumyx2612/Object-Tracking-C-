// Track Object.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat frame1, frame2;
Mat grayImage1, grayImage2;
Mat thresholdImage;
Mat differenceImage;
Mat blurImage;
Mat finalImage;

int theObject[2] = { 0,0 }; 
Rect objectBoundingRectangle = Rect(0, 0, 0, 0);

String originalWindowName = "Original";
String motionTrackingWindowName = "Motion Tracking";
String differenceImageWindowName = "Difference Image";
String finalThresholdWindowName = "Final Threshold";

int threshHoldValue = 0;
int maxVal = 255;
int blurAmount = 1;
int maxBlurAmount = 25;
int finalThresholdValue = 0;

void ThreshHoldTrackBarCallBack(int, void*)
{
	threshold(differenceImage, thresholdImage, threshHoldValue, maxVal, THRESH_BINARY);
}

void BlurSizeTrackBarCallBack(int, void*)
{
	blur(thresholdImage, blurImage, Size(blurAmount, blurAmount));
}

void FinalThreshHoldTrackBarCallBack(int, void*)
{
	threshold(blurImage, finalImage, finalThresholdValue, maxVal, THRESH_BINARY);
}


int main()
{
	String path = "E:\\Work work\\NNLT\\Btl\\bouncingBall.avi";
	bool isRunning = true;
	while (isRunning)
	{
		VideoCapture video(path);

		if (!video.isOpened())
		{
			cout << "Can't open video" << endl;
			return -1;
		}
		while (video.get(CV_CAP_PROP_POS_FRAMES) < video.get(CV_CAP_PROP_FRAME_COUNT) - 1)
		{
			video.read(frame1);
			namedWindow(originalWindowName, WINDOW_KEEPRATIO);
			namedWindow(motionTrackingWindowName, WINDOW_KEEPRATIO);
			namedWindow(differenceImageWindowName, WINDOW_KEEPRATIO);
			namedWindow(finalThresholdWindowName, WINDOW_KEEPRATIO);
			imshow(originalWindowName, frame1);

			if (waitKey(15) == 27)
			{
				isRunning = false;
				return -1;
			}

			cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
			video.read(frame2);
			cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);

			absdiff(grayImage1, grayImage2, differenceImage);
			imshow(differenceImageWindowName, differenceImage);

			threshold(differenceImage, thresholdImage, threshHoldValue, maxVal, THRESH_BINARY);
			createTrackbar("Threshold", motionTrackingWindowName, &threshHoldValue, maxVal, ThreshHoldTrackBarCallBack);
			imshow(motionTrackingWindowName, thresholdImage);

			blur(thresholdImage, blurImage, Size(blurAmount, blurAmount));
			createTrackbar("Blur", finalThresholdWindowName, &blurAmount, maxBlurAmount, BlurSizeTrackBarCallBack);
			threshold(blurImage, finalImage, finalThresholdValue, maxVal, THRESH_BINARY);
			createTrackbar("Threshold", finalThresholdWindowName, &finalThresholdValue, maxVal, FinalThreshHoldTrackBarCallBack);
			imshow(finalThresholdWindowName, finalImage);
		}
	}
}

		
	
	

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
