#ifndef HANDDETECTION_H
#define HANDDETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class handdetection
{
public:
    handdetection();
    ~handdetection();
    void isHand(cv::Mat frame, cv::Mat &hand_mask);
	bool isHand(cv::Mat frame, std::vector<cv::Point> blob);

private:
    int hue_min;
    int hue_max;
    int sat_min;
    int sat_max;
    int val_min;
    int val_max;
};

#endif // HANDDETECTION_H
