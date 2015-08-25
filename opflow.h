#ifndef OPFLOW_H
#define OPFLOW_H

#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <math.h>

#define UNKNOWN_FLOW_THRESH 1e9

class opflow
{
public:
    opflow();
    ~opflow();
    void createColorWheel();
    void motionToColor(cv::Mat flow, cv::Mat &coloredflow);
    cv::Mat calOpFlow(cv::Mat currentframe, cv::Mat nextframe);
	bool isFlowCorrect(float u);
    float calAvgOpFlow(cv::Mat flow);

private:
    std::vector<cv::Scalar> colorwheel;
};

#endif // OPFLOW_H
