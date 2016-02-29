#include "handdetection.h"

using namespace std;
using namespace cv;

handdetection::handdetection()
{
    hue_min = 0;
	sat_min = 90; //48
	val_min = 10; //80;

	hue_max = 20; //50;
	sat_max = 255; //150;
    val_max = 255;
}

handdetection::~handdetection()
{
}

void handdetection::isHand(Mat frame, Mat &hand_mask)
{
    int rows = frame.rows;
    int cols = frame.cols;
    //int size = rows * cols;

    hand_mask.create(rows, cols, CV_8UC1);
    Mat hsv_frame(rows, cols, CV_8UC3);

	//Denoise
	medianBlur(frame, frame, 5);
    //first convert the RGB image to HSV
    cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

    //uncomment the following line to see the image in HSV Color Space
    //imshow("HSV Color Space", hsv_frame);

    //filter the image in HSV color space
    inRange(hsv_frame, Scalar(hue_min, sat_min, val_min), Scalar(hue_max, sat_max, val_max), hand_mask);
    //imshow("Hand", hand_mask);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(hand_mask, hand_mask, element);
	morphologyEx(hand_mask, hand_mask, MORPH_OPEN, element);
	dilate(hand_mask, hand_mask, element);
	morphologyEx(hand_mask, hand_mask, MORPH_CLOSE, element);

    /*if (countNonZero(hand_mask) > 100)//if (countNonZero(hand_mask) > 0.01*size)
        return true;
    else
        return false;*/
}

bool handdetection::isHand(Mat frame, vector<Point> blob)
{
	unsigned int handPixelNum = 0;
	unsigned int size = blob.size();
		
	for (unsigned int i = 0; i < size; i++)
	{
		Vec3b hsv = frame.at<Vec3b>(blob[i].y, blob[i].x);
		int H = hsv.val[0]; //hue
		int S = hsv.val[1]; //saturation
		int V = hsv.val[2]; //value
		if (H >= hue_min && H <= hue_max && S >= sat_min && S <= sat_max && V >= val_min && V <= val_max)
			handPixelNum++;
	}
	if (double(handPixelNum) / size >= 0.3)
		return true;
	else
		return false;
}