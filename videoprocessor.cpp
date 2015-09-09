#include "videoprocessor.h"
#include <iostream>
#include <fstream>

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

	num_of_frames = capture.get(CV_CAP_PROP_FRAME_COUNT);
	frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	frame_rate = capture.get(CV_CAP_PROP_FPS);
	cout << frame_rate << endl;

	/*for (int i = 0; i < num_of_frames; i++)//for (int i = 0; i < 930; i++)//for (int i = 0; i < 155; i++)
	{
		Mat frame;
		capture >> frame;
	    frames.push_back(frame);
	}*/

	// TEST
	/*stringstream ss;
	string type = ".jpg";
	Mat frame;
	for (int i = 0; i < num_of_frames; i++)//for (int i = 0; i < 930; i++)//for (int i = 0; i < 155; i++)
    {
        Mat dst_1, dst_2;
		ss << i << type;
        capture >> frame;
		cv::imwrite("D:/CCCC/Stop Motion/Test2/480/" + ss.str(), frame);
		pyrDown(frame, dst_1, Size(frame.cols / 2, frame.rows / 2));
		cv::imwrite("D:/CCCC/Stop Motion/Test2/240/" + ss.str(), dst_1);
		//pyrDown(dst_1, dst_2, Size(dst_1.cols / 2, dst_1.rows / 2));
		//cv::imwrite("D:/CCCC/Stop Motion/270/" + ss.str(), dst_2);
		//if (i == 0) frames.push_back(frame);
		ss.str("");
    }*/

	/*Mat temp;
	cvtColor(frames.at(0), temp, CV_BGR2RGB);
	cv::imwrite("D:/CCCC/Stop Motion/2015_05/preview.png", temp);*/

    progressBar = new QProgressBar;
	progressBar->setRange(0, num_of_frames - 1);//progressBar->setRange(0, frames.size()-1);
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

int videoprocessor::getFrameWidth()
{
	return frame_width;
}

int videoprocessor::getFrameHeight()
{
	return frame_height;
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

        //if (current_avg_flow < 5e-2)
            //stable_frames.push_back(i);
    }
}

void videoprocessor::cut2Scenes()
{
	/*for (int i = 469; i < frames.size() - 1; i++)
	{
		Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i + 1));
		float current_avg_flow = of.calAvgOpFlow(current_flow);
		cout << i << ": " << current_avg_flow << endl;
	}*/

	vector<int> temp;
    int scene_count = 0;

	stringstream ss;
	string type = ".jpg";
	ofstream flowfile("D:/CCCC/Stop Motion/Test3/flows.txt");

	Mat frame_1, frame_2;
	for (int i = 0; i < num_of_frames - 1; i++)//for (int i = 0; i < frames.size()-1; i++)
    {
        progressBar->setValue(i+1);
		
		if (i == 0)
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test3/270/0.jpg");
			frame_2 = imread("D:/CCCC/Stop Motion/Test3/270/1.jpg");
		}
		else
		{
			ss << i+1 << type;
			frame_1 = frame_2;
			frame_2 = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
		}
		Mat current_flow = of.calOpFlow(frame_1, frame_2);//Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i + 1));
        float current_avg_flow = of.calAvgOpFlow(current_flow);
		flowfile << current_avg_flow << endl;
		//cout << i << ": " << current_avg_flow << endl;
        //bool hand = hd.isHand(frames.at(i));
		
		if (current_avg_flow == 0)//if (current_avg_flow < 0.4)//if (current_avg_flow < 0.2)//if (current_avg_flow < 5.74e-3)
        {
            //if (hand)
                //frame_types.push_back(1);
            //else
                //frame_types.push_back(3);
			frame_types.push_back(1);
        }
        else
        {
            //if (hand)
                //frame_types.push_back(2);
            //else
                //frame_types.push_back(4);
			frame_types.push_back(2);
        }

		if (i == 0)
		{
			temp.push_back(0);
			//cut_types.push_back(frame_types.at(0));
		}
		else if (i != 0 && frame_types.at(i - 1) == frame_types.at(i))
			temp.at(scene_count)++;
        else if (i != 0 && frame_types.at(i-1) != frame_types.at(i))
        {
            scene_count++;
			temp.push_back(i);
			//cut_types.push_back(frame_types.at(i));
        }
		
		ss.str("");
	}
	
	flowfile.close();
	//for (int j = 0; j < temp.size(); j++)
		//cout << temp.at(j) << endl;

	int cut_counter = -1;
	int sum = 0;
	bool isMessy = false;
	int movingcount = 0;
    for (int j = 0; j < temp.size(); j++)
    {
        //cout << scene_cuts.at(j) << endl;
		cout << endl;
		cout << j << ": " << temp.at(j) << " " << sum << " " << movingcount << endl;
		
		int length;
		
		if (j == 0) length = temp.at(j) + 1;
		else length = temp.at(j) - temp.at(j - 1);

		if (length >= frame_rate)//if (length >= 20)//if (length >= frame_rate)
		{
			if (isMessy)
			{
				if (cut_counter == -1)
				{
					cout << 1 << endl;
					scene_cuts.push_back(temp.at(j));
					cut_types.push_back(frame_types.at(temp.at(j)));
					cut_counter++;
				}
				else 
				{
					int previous_length;
					if (cut_counter == 0) previous_length = scene_cuts.at(0) + 1;
					else previous_length = scene_cuts.at(cut_counter) - scene_cuts.at(cut_counter - 1);
					
					if (cut_types.at(cut_counter) == frame_types.at(temp.at(j)))
					{
						cout << 2 << endl;
						scene_cuts.at(cut_counter) = temp.at(j);
					}
					/*else if (previous_length < length)
					{
						scene_cuts.at(cut_counter) += sum;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(frame_types.at(temp.at(j)));
						cut_counter++;
					}
					else
					{
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(frame_types.at(temp.at(j)));
						cut_counter++;
					}*/
					else if (cut_types.at(cut_counter) == 1)
					{
						cout << 3 << endl;
						if ((sum-movingcount) * 3 >= sum) scene_cuts.at(cut_counter) += sum;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(2);
						cut_counter++;
					}
					else
					{
						cout << 4 << endl;
						if (movingcount * 3 >= sum) scene_cuts.at(cut_counter) += sum;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(1);
						cut_counter++;
					}
				}
				sum = 0;
				movingcount = 0;
				isMessy = false;
			}
			else
			{
				cout << 5 << endl;
				scene_cuts.push_back(temp.at(j));
				cut_types.push_back(frame_types.at(temp.at(j)));
				cut_counter++;
			}
		}
		else if (isMessy)
		{
			sum += length;
			if (frame_types.at(temp.at(j)) == 2) movingcount += length;
			if (j == temp.size() - 1)
			{
				if (sum >= frame_rate)//if (sum >= 20) //if (sum >= frame_rate)
				{
					cout << 6 << endl;
					scene_cuts.push_back(temp.at(j));
					if (cut_types.at(cut_counter) == 1) cut_types.push_back(2);
					else cut_types.push_back(1);
					cut_counter++;
				}
				else
				{
					cout << 7 << endl;
					scene_cuts.at(cut_counter) = temp.at(j);
				}
				sum = 0;
				movingcount = 0;
				isMessy = false;
			}
			else if (sum >= frame_rate && (temp.at(j + 1) - temp.at(j)) >= frame_rate)//else if (sum >= 20 && (temp.at(j + 1) - temp.at(j)) >= 20)//else if (sum >= frame_rate && (temp.at(j+1) - temp.at(j)) >= frame_rate)
			{
				if (cut_counter == -1)
				{
					if (((sum - movingcount) * 3 >= sum && frame_types.at(temp.at(j + 1)) == 2) || (movingcount * 3 >= sum && frame_types.at(temp.at(j + 1)) == 1))
					{
						cout << 7.5 << endl;
						scene_cuts.push_back(temp.at(j));
						if (frame_types.at(temp.at(j + 1)) == 1) cut_types.push_back(2);
						else cut_types.push_back(1);
						cut_counter++;
					}
				}
				else if (cut_types.at(cut_counter) == frame_types.at(temp.at(j + 1)))
				{
					if (((sum-movingcount) * 3 >= sum && cut_types.at(cut_counter) == 1) || (movingcount * 3 >= sum && cut_types.at(cut_counter) == 2))
					{
						cout << 8 << endl;
						scene_cuts.at(cut_counter) = temp.at(j + 1);
						j++;
					}
					else
					{
						cout << 9 << endl;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(frame_types.at(temp.at(j)));
						cut_counter++;
					}
				}
				else if (((sum - movingcount) * 3 >= sum && cut_types.at(cut_counter) == 1) || (movingcount * 3 >= sum && cut_types.at(cut_counter) == 2))
				{
					cout << 10 << endl;
					scene_cuts.at(cut_counter) += sum;
				}
				sum = 0;
				movingcount = 0;
				isMessy = false;
			}
		}
		else if (!isMessy)
		{
			if (j == temp.size() - 1)
			{
				cout << 11 << endl;
				scene_cuts.at(cut_counter) = temp.at(j);
				sum = 0;
			}
			else if (cut_counter != -1 && length < 5 && (temp.at(j + 1) - temp.at(j)) > 5 && cut_types.at(cut_counter) == frame_types.at(temp.at(j+1)))
			{
				cout << 12 << endl;
				scene_cuts.at(cut_counter) = temp.at(j + 1);
				j++;
			}
			else
			{
				cout << 13 << endl;
				sum += length;
				isMessy = true;
				if (frame_types.at(temp.at(j)) == 2) movingcount += length;
			}
		}
    }
}

vector<int> videoprocessor::getSceneCuts()
{
    return scene_cuts;
}

vector<int> videoprocessor::getCutTypes()
{
	return cut_types;
}

vector<int> videoprocessor::getFrameTypes()
{
    return frame_types;
}

QProgressBar *videoprocessor::getProgressBar()
{
    return progressBar;
}

vector<int> videoprocessor::getRange(int current, int width)
{
	vector<int> range;
    int current_frame = floor(double(current) / width * num_of_frames);

    for (int i = 0; i < scene_cuts.size(); i++)
    {
        if (current_frame <= scene_cuts.at(i))
        {
			if (i == 0) 
			{
				range.push_back(i);
				range.push_back(0);
				range.push_back(scene_cuts.at(i));
				return range;
			}
			else
			{
				range.push_back(i);
				range.push_back(scene_cuts.at(i - 1) + 1);
				range.push_back(scene_cuts.at(i));
				return range;
			}
        }
    }

	range.push_back(-1);
	range.push_back(-1);
	range.push_back(-1);
    return range;
}

int videoprocessor::getNumOfFrames()
{
    return num_of_frames;
}

int videoprocessor::getFrameRate()
{
	return frame_rate;
}

void videoprocessor::writeVideo(vector<int> range, vector<bool> moving_range, clipOperation operation)
{
    /*if (out.isOpened())
    {
        cout << "Open" << endl;
    }

    Mat frame;
    out.open("D:/CCCC/Stop Motion/2015_05/range.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5, Size(frame_width, frame_height));

    if(!out.isOpened()) {
		throw "Error! Unable to open video file for output.";
    }*/

	int start = -1;
	int end = -1;
	int size = range.size();
	Mat frame;

	stringstream ss;
	string type = ".jpg";
	int delay = 250;

	switch (operation)
	{

	case ViewClip :
	case ViewTrack :
		{
			namedWindow("View Clip/Track", CV_WINDOW_AUTOSIZE);
			for (int i = 0; i < size; i+=2)
			{
				start = range.at(i);
				end = range.at(i + 1);
				//cout << start << " " << end << endl;

				if (moving_range.at(i / 2))
					for (int j = start; j <= end; j++)
					{
						ss << j << type;
						frame = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
						imshow("View Clip/Track", frame);
						if (waitKey(delay) == 27) break;
						if (waitKey(delay) == 32) waitKey(0);
						ss.str("");
						//frame = frames.at(j);
						//out << frame;
					}
				else
				{
					ss << (start+end)/2 << type;
					frame = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
					imshow("View Clip/Track", frame);
					waitKey(delay);
					ss.str("");
				}
			}
		}
		break;
			
	case DeleteClip :
		{
			namedWindow("Delete Clip", CV_WINDOW_AUTOSIZE);
			int size = range.size();
			if (range.at(size - 1) == 0) start = scene_cuts.at(0) + 1;
			else if (range.at(size - 1) == 1) start = 0;
			else start = scene_cuts.at(range.at(size-1) - 2) + 1;
			end = scene_cuts.at(range.at(size-1) + 1);
			for (int i = start; i <= end; i++)
			{
				if (i < range.at(0) || i > range.at(size-2))
				{
					ss << i << type;
					frame = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
					imshow("Delete Clip", frame);
					if (waitKey(delay) == 27) break;
					if (waitKey(delay) == 32) waitKey(0);
					ss.str("");
					//frame = frames.at(i);
					//out << frame;
				}
			}
		}
		break;

	case ReverseClip :
		{
			namedWindow("Reverse Clip", CV_WINDOW_AUTOSIZE);
			for (int i = size-1; i >= 1; i-=2)
			{
				start = range.at(i);
				end = range.at(i - 1);

				if (moving_range.at((i-1) / 2))
					for (int j = start; j >= end; j--)
					{
						ss << j << type;
						frame = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
						imshow("Reverse Clip", frame);
						if (waitKey(delay) == 27) break;
						if (waitKey(delay) == 32) waitKey(0);
						ss.str("");
						//frame = frames.at(j);
						//out << frame;
					}
				else
				{
					ss << (start + end) / 2 << type;
					frame = imread("D:/CCCC/Stop Motion/Test3/270/" + ss.str());
					imshow("Reverse Clip", frame);
					waitKey(delay);
					ss.str("");
				}
			}
		}
		break;
	}

    //out.release();
}

void videoprocessor::test()
{
	Mat frame_1, frame_2, current_flow;
	float current_avg_flow;
	frame_1 = imread("D:/CCCC/Stop Motion/540/520.jpg");
	frame_2 = imread("D:/CCCC/Stop Motion/540/521.jpg");
	current_flow = of.calOpFlow(frame_1, frame_2);
	current_avg_flow = of.calAvgOpFlow(current_flow);
	cout << "1080p: " << current_avg_flow << endl;

	/*frame_1 = imread("D:/CCCC/Stop Motion/540/497.jpg");
	frame_2 = imread("D:/CCCC/Stop Motion/540/498.jpg");
	current_flow = of.calOpFlow(frame_1, frame_2);
	current_avg_flow = of.calAvgOpFlow(current_flow);
	cout << "540p: " << current_avg_flow << endl;

	frame_1 = imread("D:/CCCC/Stop Motion/270/497.jpg");
	frame_2 = imread("D:/CCCC/Stop Motion/270/498.jpg");
	current_flow = of.calOpFlow(frame_1, frame_2);
	current_avg_flow = of.calAvgOpFlow(current_flow);
	cout << "270p: " << current_avg_flow << endl;*/
}

void videoprocessor::writeBuffers()
{
	ofstream cutfile("cuts10.txt");
	if (cutfile.is_open())
	{
		for (int i = 0; i < scene_cuts.size(); i++)
			cutfile << scene_cuts.at(i) << endl;
		cutfile.close();
	}
	else cout << "Unable to open file" << endl;

	ofstream typefile("types10.txt");
	if (typefile.is_open())
	{
		for (int j = 0; j < cut_types.size(); j++)
			typefile << cut_types.at(j) << endl;
		typefile.close();
	}
	else cout << "Unable to open file" << endl;
}

void videoprocessor::readBuffers()
{ 
	if (scene_cuts.empty())
	{
		ifstream cutfile("cuts9.txt");
		int num;
		if (cutfile.is_open())
		{
			while (cutfile >> num)
				scene_cuts.push_back(num);
			cutfile.close();
		}
		else cout << "Unable to open file" << endl;
	}

	if (cut_types.empty())
	{
		ifstream typefile("types9.txt");
		int num;
		if (typefile.is_open())
		{
			while (typefile >> num)
				cut_types.push_back(num);
			typefile.close();
		}
		else cout << "Unable to open file" << endl;
	}
}