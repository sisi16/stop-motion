#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/background_segm.hpp>
#include <QProgressBar>
#include <string>
#include <sstream>
#include "opflow.h"
#include "handdetection.h"
#include "blobtrack.h"

/*enum clipOperation
{
	NullOperation,
	//SelectClip,
	//SelectTrack,
	//ViewClip,
	//ViewTrack,
	MoveClip,
	//DeleteClip,
	//ReverseClip,
	//CastClip
};*/

class videoprocessor
{
public:
    videoprocessor();
    ~videoprocessor();
    void readVideo(const std::string file);
    std::vector<cv::Mat> getFrames();
    std::vector<int> getStableFrames();
    float calAvgOpFlow(cv::Mat frame_1, cv::Mat frame_2);
    void cut2Scenes();
    std::vector<int> getSceneCuts();
	std::vector<int> getCutTypes();
    std::vector<int> getFrameTypes();
    int getVideoSize();
	int getFrameWidth();
	int getFrameHeight();
    QProgressBar *getProgressBar();
    std::vector<int> getRange(int current, int width);
    int getNumOfFrames();
	int getFrameRate();
	//void writeVideo(std::vector<int> range, std::vector<int> moving_range, clipOperation operation);
    std::vector<bool> test();
	void writeBuffers();
	void readBuffers();
	int matchFeatures(cv::Mat image_1, cv::Mat image_2, int &object);
	std::vector<int> checkCuts(std::vector<int> checkRange);

private:
    QProgressBar *progressBar;
    int num_of_frames;
    int frame_width;
    int frame_height;
	int frame_rate;
    std::vector<cv::Mat> frames;
    std::vector<int> stable_frames;
    std::vector<float> avg_flows;
    std::vector<int> frame_types;
	std::vector<int> cut_types;
    std::vector<int> scene_cuts;
    cv::VideoWriter out;
    opflow of;
    handdetection hd;
	std::string fileName;
};

#endif // VIDEOPROCESSOR_H
