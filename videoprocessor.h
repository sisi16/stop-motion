#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QProgressBar>
#include <string>
#include "opflow.h"
#include "handdetection.h"

enum clipOperation
{
	NullOperation,
	SelectClip,
	SelectTrack,
	ResumeClip,
	ViewClip,
	MoveClip,
	DeleteClip,
	ReverseClip,
	CastClip,
	GroupClip
};

class videoprocessor
{
public:
    videoprocessor();
    ~videoprocessor();
    void readVideo(const std::string& file);
    std::vector<cv::Mat> getFrames();
    std::vector<int> getStableFrames();
    void calAvgOpFlows();
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
    void writeVideo(std::vector<int> range, clipOperation operation);
    void test();
	void writeBuffers();
	void readBuffers();

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
};

#endif // VIDEOPROCESSOR_H
