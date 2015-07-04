#include "opflow.h"

using namespace std;
using namespace cv;

opflow::opflow()
{
}

opflow::~opflow()
{
}

void opflow::createColorWheel()
{
    int RY = 15;
    int YG = 6;
    int GC = 4;
    int CB = 11;
    int BM = 13;
    int MR = 6;

    int i;

    for (i = 0; i < RY; i++) colorwheel.push_back(Scalar(255, 255*i/RY,	0));
    for (i = 0; i < YG; i++) colorwheel.push_back(Scalar(255-255*i/YG, 255, 0));
    for (i = 0; i < GC; i++) colorwheel.push_back(Scalar(0,	255, 255*i/GC));
    for (i = 0; i < CB; i++) colorwheel.push_back(Scalar(0, 255-255*i/CB, 255));
    for (i = 0; i < BM; i++) colorwheel.push_back(Scalar(255*i/BM, 0, 255));
    for (i = 0; i < MR; i++) colorwheel.push_back(Scalar(255, 0, 255-255*i/MR));
}

void opflow::motionToColor(Mat flow, Mat &coloredflow)
{
    coloredflow.create(flow.rows, flow.cols, CV_8UC3);

    if (colorwheel.empty())
        createColorWheel();

    // determine motion range:
    float maxrad = -1;

    // Find max flow to normalize fx and fy
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);
            float fx = flow_at_pixel[0];
            float fy = flow_at_pixel[1];
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
                continue;
            float rad = sqrt(fx * fx + fy * fy);
            maxrad = maxrad > rad ? maxrad : rad;
        }
    }

    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            uchar *data = coloredflow.data + coloredflow.step[0] * i + coloredflow.step[1] * j;
            Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);

            float fx = flow_at_pixel[0] / maxrad;
            float fy = flow_at_pixel[1] / maxrad;
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
            {
                data[0] = data[1] = data[2] = 0;
                continue;
            }
            float rad = sqrt(fx * fx + fy * fy);

            double angle = atan2(-fy, -fx) / CV_PI;
            double fk = (angle + 1.0) / 2.0 * (colorwheel.size()-1);
            int k0 = (int)fk;
            int k1 = (k0 + 1) % colorwheel.size();
            double f = fk - k0;
            //f = 0; // uncomment to see original color wheel

            for (int b = 0; b < 3; b++)
            {
                double col0 = colorwheel[k0][b] / 255.0;
                double col1 = colorwheel[k1][b] / 255.0;
                double col = (1 - f) * col0 + f * col1;
                if (rad <= 1)
                    col = 1 - rad * (1 - col); // increase saturation with radius
                else
                    col *= .75; // out of range
                data[2 - b] = (int)(255.0 * col);
            }
        }
    }
}

Mat opflow::calOpFlow(Mat currentframe, Mat nextframe)
{
    Mat currentgray, nextgray, flow;

    cvtColor(currentframe, currentgray, CV_BGR2GRAY);
    cvtColor(nextframe, nextgray, CV_BGR2GRAY);

    if (currentgray.data)
        calcOpticalFlowFarneback(currentgray, nextgray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

    return flow;
}

float opflow::calAvgOpFlow(Mat flow)
{
    float accrad = 0;
    int overflow_count = 0;

    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_pixel = flow.at<Vec2f>(i, j);
            float fx = flow_at_pixel[0];
            float fy = flow_at_pixel[1];

            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
            {
                overflow_count++;
                continue;
            }
            accrad += sqrt(fx * fx + fy * fy);
        }
    }

    float avgflow = accrad / (flow.rows * flow.cols - overflow_count);

    return avgflow;
}
