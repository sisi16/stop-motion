#ifndef OPFLOW_H
#define OPFLOW_H

#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <math.h>

#define UNKNOWN_FLOW_THRESH 1e9

#ifndef MAX
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#endif

#define XY_TO_INT(x, y) (((y) << 12) | (x))
#define INT_TO_X(v) ((v)&((1<<12)-1))
#define INT_TO_Y(v) ((v)>>12)

class BITMAP3 {
public:
	int w, h;
	int *data;
	BITMAP3(int w_, int h_) :w(w_), h(h_) { data = new int[w*h]; }
	~BITMAP3() { delete[] data; }
	int *operator[](int y) { return &data[y*w]; }
};

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
	BITMAP3* toBITMAP(const uchar *img, int width, int height, int istep);
	int dist(BITMAP3 *a, BITMAP3 *b, int ax, int ay, int bx, int by, int diagonalDis, int cutoff = INT_MAX);
	void improve_guess(BITMAP3 *a, BITMAP3 *b, int ax, int ay, int &xbest, int &ybest, int &dbest, int bx, int by);
	bool more_area(const std::vector<cv::Point> &c1, const std::vector<cv::Point> &c2)
	{
		return contourArea(c1) > contourArea(c2);
	}
	std::vector<std::vector<cv::Point>> patchMatch(cv::Mat currentframe, cv::Mat nextframe);

private:
    std::vector<cv::Scalar> colorwheel;
};

#endif // OPFLOW_H
