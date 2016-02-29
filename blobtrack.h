#ifndef BLOBTRACK_H
#define BLOBTRACK_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <string>
#include <sstream>
#include "handdetection.h"

/* Blob Structure */
class blob
{
public:
	blob(float bx, float by, float size);
	~blob();

private:
	float x, y;
	float area;
	//int ID;
};

/* Blob List 
class blobList
{

};
*/

/* Blob Detector */
class blobDetector
{
public:
	blobDetector();
	~blobDetector();
	void process(const std::string filename, int numOfFrames);
	static bool more_area(const std::vector<cv::Point> &c1, const std::vector<cv::Point> &c2)
	{
		return contourArea(c1) > contourArea(c2);
	}
	void klt(const std::string filename, int numOfFrames);

private:
	handdetection hd;
};

/* Main API */
class blobtrack
{
public:
	blobtrack(const std::string filename, const int numOfFrames);
    ~blobtrack();
	void process();

private:
	std::string file;
	int num_of_frames;
	blobDetector *bDetector = NULL;
};

#endif // BLOBTRACK_H
