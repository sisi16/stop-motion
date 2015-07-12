#include "videoprocessor.h"
#include <iostream>

using namespace std;
using namespace cv;

videoprocessor::videoprocessor()
{
}

videoprocessor::~videoprocessor()
{
    frames.clear();
}

void videoprocessor::readVideo(const string& file)
{
    if (!frames.empty()) frames.clear();

    VideoCapture capture(file);

	if (!capture.isOpened())
		throw "Error when reading the video file";

    for (int i = 0; i < 149; i++)//for (int i = 0; i < capture.get(CV_CAP_PROP_FRAME_COUNT); i++)
    {
        Mat frame;
        capture >> frame;
        frames.push_back(frame);
    }

    num_of_frames = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << num_of_frames << endl;
    frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	frame_rate = capture.get(CV_CAP_PROP_FPS);

    progressBar = new QProgressBar;
    progressBar->setRange(0, frames.size()-1);
    progressBar->setValue(0);
}

vector<Mat> videoprocessor::getFrames()
{
    return frames;
}

vector<int> videoprocessor::getStableFrames()
{
    return stable_frames;
}

int videoprocessor::getVideoSize()
{
    return num_of_frames;
}

void videoprocessor::calAvgOpFlows()
{
    if (!avg_flows.empty()) avg_flows.clear();
    if (!stable_frames.empty()) stable_frames.clear();

    for (int i = 0; i < frames.size()-1; i++)
    {
        Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i+1));
        float current_avg_flow = of.calAvgOpFlow(current_flow);
        cout << current_avg_flow << endl;
        avg_flows.push_back(current_avg_flow);

        if (current_avg_flow < 5e-2)
            stable_frames.push_back(i);
    }
}

void videoprocessor::cut2Scenes()
{
    int scene_count = 0;

    for (int i = 0; i < frames.size()-1; i++)
    {
        progressBar->setValue(i+1);

        Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i+1));
        float current_avg_flow = of.calAvgOpFlow(current_flow);
        bool hand = hd.isHand(frames.at(i));

        if (current_avg_flow < 5e-2)
        {
            if (hand)
                frame_types.push_back(1);
            else
                frame_types.push_back(3);
        }
        else
        {
            if (hand)
                frame_types.push_back(2);
            else
                frame_types.push_back(4);
        }

        if (i == 0)
            scene_cuts.push_back(0);
        else if (i != 0 && frame_types.at(i-1) == frame_types.at(i))
            scene_cuts.at(scene_count)++;
        else if (i != 0 && frame_types.at(i-1) != frame_types.at(i))
        {
            scene_count++;
            scene_cuts.push_back(i);
        }
    }
    for (int j = 0; j < scene_cuts.size(); j++)
    {
        cout << scene_cuts.at(j) << endl;
    }
}

vector<int> videoprocessor::getSceneCuts()
{
    return scene_cuts;
}

vector<int> videoprocessor::getFrameTypes()
{
    return frame_types;
}

QProgressBar *videoprocessor::getProgressBar()
{
    return progressBar;
}

Point3i videoprocessor::getRange(int current, int width)
{
    int current_frame = floor(double(current) / width * num_of_frames);

    for (int i = 0; i < scene_cuts.size(); i++)
    {
        if (current_frame <= scene_cuts.at(i))
        {
            if (i == 0) return Point3i(0, scene_cuts.at(i), i);
            else return Point3i(scene_cuts.at(i-1)+1, scene_cuts.at(i), i);
        }
    }

    return Point3i(-1, -1, -1);
}

int videoprocessor::getNumOfFrames()
{
    return num_of_frames;
}

int videoprocessor::getFrameRate()
{
	return frame_rate;
}

void videoprocessor::writeVideo(Point3i range, clipOperation operation)
{
    if (out.isOpened())
    {
        cout << "Open" << endl;
    }

    Mat frame;
    out.open("D:/CCCC/Stop Motion/2015_05/range.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

    if(!out.isOpened()) {
		throw "Error! Unable to open video file for output.";
    }

	int start = -1;
	int end = -1;

	switch (operation)
	{

	case ViewClip :
		{
			start = range.x;
			end = range.y;
			for (int i = start; i <= end; i++)
			{
				frame = frames.at(i);
				out << frame;
			}
		}
		break;
			
	case DeleteClip :
		{
			start = scene_cuts.at(range.z - 2) + 1;
			end = scene_cuts.at(range.z + 1);
			for (int i = start; i <= end; i++)
			{
				if (i < range.x || i > range.y)
				{
					frame = frames.at(i);
					out << frame;
				}
			}
		}
		break;

	case ReverseClip :
		{
			start = range.y;
			end = range.x;
			for (int i = start; i >= end; i--)
			{
				frame = frames.at(i);
				out << frame;
			}
		}
		break;
	}

    out.release();
}

void videoprocessor::test()
{
    /*Mat color1, color2;
    Mat flow1 = of.calOpFlow(frames.at(80), frames.at(81));
    Mat flow2 = of.calOpFlow(frames.at(90), frames.at(91));
    of.createColorWheel();
    of.motionToColor(flow1, color1);
    of.motionToColor(flow2, color2);
    imshow("Frame 80-81", color1);
    imshow("Frame 90-91", color2);*/

    if (hd.isHand(frames.at(2))) cout << "2: YES" << endl;
    imshow("Frame 2", frames.at(2));

    /*if (hd.isHand(frames.at(81))) cout << "81: YES" << endl;
    imshow("Frame 81", frames.at(81));

    if (hd.isHand(frames.at(90))) cout << "90: YES" << endl;
    imshow("Frame 90", frames.at(90));

    if (hd.isHand(frames.at(91))) cout << "91: YES" << endl;
    imshow("Frame 91", frames.at(91));*/
}
