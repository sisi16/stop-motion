#include "handdetection.h"

using namespace std;
using namespace cv;

handdetection::handdetection()
{
    hue_min = 0;
    sat_min = 90;
    val_min = 10;

    hue_max = 20;
    sat_max = 255;
    val_max = 255;
}

handdetection::~handdetection()
{
}

bool handdetection::isHand(Mat frame)
{
    int rows = frame.rows;
    int cols = frame.cols;
    //int size = rows * cols;

    Mat hand_mask(rows, cols, CV_8UC1);
    Mat hsv_frame(rows, cols, CV_8UC3);

    //first convert the RGB image to HSV
    cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

    //uncomment the following line to see the image in HSV Color Space
    //imshow("HSV Color Space", hsv_frame);

    //filter the image in HSV color space
    inRange(hsv_frame, Scalar(hue_min, sat_min, val_min), Scalar(hue_max, sat_max, val_max), hand_mask);
    //imshow("Hand", hand_mask);


    if (countNonZero(hand_mask) > 100)//if (countNonZero(hand_mask) > 0.01*size)
        return true;
    else
        return false;
}
