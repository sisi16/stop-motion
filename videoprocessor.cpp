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

void videoprocessor::readVideo(const string file)
{
    if (!frames.empty()) frames.clear();

    VideoCapture capture(file);

	if (!capture.isOpened())
		throw "Error when reading the video file";

	fileName = file;
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
	for (int i = 0; i < num_of_frames; i++)
    {
		capture >> frame;
		if (i == 0) frames.push_back(frame);
        Mat dst_1, dst_2;
		ss << i << type;
		cv::imwrite("D:/CCCC/Stop Motion/UserTest_MX/1080/" + ss.str(), frame);
		pyrDown(frame, dst_1, Size(frame.cols / 2, frame.rows / 2));
		cv::imwrite("D:/CCCC/Stop Motion/UserTest_MX/540/" + ss.str(), dst_1);
		pyrDown(dst_1, dst_2, Size(dst_1.cols / 2, dst_1.rows / 2));
		cv::imwrite("D:/CCCC/Stop Motion/UserTest_MX/270/" + ss.str(), dst_2);
		ss.str("");
    }*/
	
	Mat temp;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") temp = imread("D:/CCCC/Stop Motion/Test6/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") temp = imread("D:/CCCC/Stop Motion/Test7/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") temp = imread("D:/CCCC/Stop Motion/Test8/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest.avi") temp = imread("D:/CCCC/Stop Motion/UserTest/270/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest_1.avi") temp = imread("D:/CCCC/Stop Motion/UserTest_1/270/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest_2.avi") temp = imread("D:/CCCC/Stop Motion/UserTest_2/270/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest_XT.avi") temp = imread("D:/CCCC/Stop Motion/UserTest_XT/270/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest_LL.avi") temp = imread("D:/CCCC/Stop Motion/UserTest_LL/270/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/UserTest_MX.avi") temp = imread("D:/CCCC/Stop Motion/UserTest_MX/270/0.jpg");
	//cvtColor(frames.at(0), temp, CV_BGR2RGB);
	//capture >> temp;
	cv::imwrite("D:/CCCC/Stop Motion/Videos/preview.png", temp);
	capture.release();

    /*progressBar = new QProgressBar;
	progressBar->setRange(0, num_of_frames - 1);//progressBar->setRange(0, frames.size()-1);
    progressBar->setValue(0);*/

	//test();
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

float videoprocessor::calAvgOpFlow(Mat frame_1, Mat frame_2)
{
	Mat current_flow = of.calOpFlow(frame_1, frame_2);
	return of.calAvgOpFlow(current_flow);
}

void videoprocessor::cut2Scenes()
{
	vector<int> temp;
    int scene_count = 0;

	stringstream ss;
	string type = ".jpg";
	ofstream flowfile("D:/CCCC/Stop Motion/UserTest_XT/flows.txt");
	Mat frame_1, frame_2;
	
	//ifstream flowfile("D:/CCCC/Stop Motion/UserTest_XT/flows.txt");

	//#pragma omp parallel for
	for (int i = 0; i < num_of_frames - 1; i++)
    {
        //progressBar->setValue(i+1);
		
		if (i == 0)
		{
			frame_1 = imread("D:/CCCC/Stop Motion/UserTest_XT/270/0.jpg");
			frame_2 = imread("D:/CCCC/Stop Motion/UserTest_XT/270/1.jpg");
		}
		else
		{
			ss << i+1 << type;
			frame_1 = frame_2;
			frame_2 = imread("D:/CCCC/Stop Motion/UserTest_XT/270/" + ss.str());
		}

		Mat current_flow = of.calOpFlow(frame_1, frame_2);//Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i + 1));
        float current_avg_flow = of.calAvgOpFlow(current_flow);
		ss.str("");
		flowfile << current_avg_flow << endl;

		//float current_avg_flow;
		//flowfile >> current_avg_flow;
		if (current_avg_flow < 0.005) // if (current_avg_flow == 0)
		{
			frame_types.push_back(1);
		}
		else
		{
			frame_types.push_back(2);
		}

		if (i == 0)
		{
			temp.push_back(0);
			//cut_types.push_back(frame_types.at(0));
		}
		else if (i != 0 && frame_types.at(i - 1) == frame_types.at(i))
			temp.at(scene_count)++;
		else if (i != 0 && frame_types.at(i - 1) != frame_types.at(i))
		{
			scene_count++;
			temp.push_back(i);
			//cut_types.push_back(frame_types.at(i));
		}
	}
	
	flowfile.close();


	int cut_counter = -1;
	int sum = 0;
	bool isMessy = false;
	int movingcount = 0;
    for (int j = 0; j < temp.size(); j++)
    {	
		int length;
		
		if (j == 0) length = temp.at(j) + 1;
		else length = temp.at(j) - temp.at(j - 1);

		if (length >= frame_rate)
		{
			if (isMessy)
			{
				if (cut_counter == -1)
				{
					//cout << 1 << endl;
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
						//cout << 2 << endl;
						scene_cuts.at(cut_counter) = temp.at(j);
					}
					else if (cut_types.at(cut_counter) == 1)
					{
						if ((sum-movingcount) * 3 >= sum * 2) scene_cuts.at(cut_counter) += sum;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(2);
						cut_counter++;
					}
					else
					{
						if (movingcount * 3 >= sum * 2) scene_cuts.at(cut_counter) += sum;
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
				//cout << 5 << endl;
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
				if (sum >= frame_rate)
				{
					//cout << 6 << endl;
					scene_cuts.push_back(temp.at(j));
					if (cut_types.at(cut_counter) == 1) cut_types.push_back(2);
					else cut_types.push_back(1);
					cut_counter++;
				}
				else
				{
					//cout << 7 << endl;
					scene_cuts.at(cut_counter) = temp.at(j);
				}
				sum = 0;
				movingcount = 0;
				isMessy = false;
			}
			else if (sum >= frame_rate * 2 && (temp.at(j + 1) - temp.at(j)) >= frame_rate)
			{
				if (cut_counter == -1)
				{
					if (((sum - movingcount) * 2 >= sum && frame_types.at(temp.at(j + 1)) == 2) || (movingcount * 2 >= sum && frame_types.at(temp.at(j + 1)) == 1))
					{
						//cout << 7.5 << endl;
						scene_cuts.push_back(temp.at(j));
						if (frame_types.at(temp.at(j + 1)) == 1) cut_types.push_back(2);
						else cut_types.push_back(1);
						cut_counter++;
					}
				}
				else if (cut_types.at(cut_counter) == frame_types.at(temp.at(j + 1)))
				{
					if (((sum-movingcount) * 3 >= sum * 2 && cut_types.at(cut_counter) == 1) || (movingcount * 3 >= sum * 2 && cut_types.at(cut_counter) == 2))
					{
						//cout << 8 << endl;
						scene_cuts.at(cut_counter) = temp.at(j + 1);
						j++;
					}
					else
					{
						//cout << 9 << endl;
						scene_cuts.push_back(temp.at(j));
						cut_types.push_back(frame_types.at(temp.at(j)));
						cut_counter++;
					}
				}
				else if (((sum - movingcount) * 3 >= sum * 2 && cut_types.at(cut_counter) == 1) || (movingcount * 3 >= sum * 2 && cut_types.at(cut_counter) == 2))
				{
					//cout << 10 << endl;
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
				//cout << 11 << endl;
				scene_cuts.at(cut_counter) = temp.at(j);
				sum = 0;
			}
			else if (cut_counter != -1 && length < 5 && (temp.at(j + 1) - temp.at(j)) > 5 && cut_types.at(cut_counter) == frame_types.at(temp.at(j+1)))
			{
				//cout << 12 << endl;
				scene_cuts.at(cut_counter) = temp.at(j + 1);
				j++;
			}
			else
			{
				//cout << 13 << endl;
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

/*void videoprocessor::writeVideo(vector<int> range, vector<int> moving_range, clipOperation operation)
{
    if (out.isOpened())
    {
        cout << "Open" << endl;
    }

    //Mat frame;
	out.open("D:/CCCC/Stop Motion/Videos/range.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5, Size(960, 540));//out.open("D:/CCCC/Stop Motion/Videos/range.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5, Size(frame_width, frame_height));0

    if(!out.isOpened()) {
		throw "Error! Unable to open video file for output.";
    }

	int start = -1;
	int end = -1;
	int size = range.size();
	Mat frame;

	stringstream ss;
	string type = ".jpg";
	int delay;

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

				if (moving_range.at(i/2) == 2)
				{
					bool isBreak = false;
					delay = 250 / frame_rate;//delay = 1000 / frame_rate;
					for (int j = start; j <= end; j++)
					{
						ss << j << type;
						if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
						imshow("View Clip/Track", frame);
						if (waitKey(delay) == 27)
						{
							isBreak = true;
							break;
						}
						if (waitKey(delay) == 32) waitKey(0);
						ss.str("");
						//frame = frames.at(j);
						//out << frame;
					}
					if (isBreak) break;
				}
				else
				{
					delay = 250;
					ss << (start+end)/2 << type;
					if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
					imshow("View Clip/Track", frame);
					//waitKey(delay);
					if (waitKey(delay) == 27) break;
					if (waitKey(delay) == 32) waitKey(0);
					ss.str("");
					//out << frame;
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
			delay = 250;
			for (int i = start; i <= end; i++)
			{
				if (i < range.at(0) || i > range.at(size-2))
				{
					ss << i << type;
					if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
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

				if (moving_range.at((i-1)/2) == 2)
				{
					delay = 1000 / frame_rate;
					for (int j = start; j >= end; j--)
					{
						ss << j << type;
						if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
						else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
						imshow("Reverse Clip", frame);
						if (waitKey(delay) == 27) break;
						if (waitKey(delay) == 32) waitKey(0);
						ss.str("");
						//frame = frames.at(j);
						//out << frame;
					}
				}
				else
				{
					delay = 250;
					ss << (start + end) / 2 << type;
					if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
					else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
					imshow("Reverse Clip", frame);
					waitKey(delay);
					ss.str("");
				}
			}
		}
		break;

	default:
		break;
	}

    //out.release();
}*/

void videoprocessor::test()
{
	if (out.isOpened())
		cout << "Open." << endl;

	Mat frame;
	out.open("D:/CCCC/Stop Motion/Videos/UserTestOutput_2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(960, 540));
	
	if (!out.isOpened())
		throw "Error! Unable to open video file for output.";
	
	stringstream ss;
	string type = ".jpg";
	
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/30.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 55; i <= 84; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/270.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/470.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/580.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/680.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 707; i <= 718; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/850.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/970.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1120.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1250.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1430.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 1468; i <= 1538; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1680.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 1719; i <= 1804; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1830.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 1880; i <= 1892; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/1980.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	for (int i = 2039; i <= 2164; i++)
	{
		ss << i << type;
		frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/" + ss.str());
		out << frame;
		ss.str("");
	}
	frame = imread("D:/CCCC/Stop Motion/UserTest_2/540/2200.jpg");
	out << frame;
	out << frame;
	out << frame;
	out << frame;
	out << frame;

	out.release();
}

void videoprocessor::writeBuffers()
{
	ofstream cutfile("cuts20.txt");
	if (cutfile.is_open())
	{
		for (int i = 0; i < scene_cuts.size(); i++)
			cutfile << scene_cuts.at(i) << endl;
		cutfile.close();
	}
	else cout << "Unable to open file" << endl;

	ofstream typefile("types20.txt");
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
		ifstream cutfile;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts10.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts11.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts12.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts18.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts16.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cuts17.txt");
		//ifstream cutfile("D:/CCCC/Stop Motion/StopMotion/cuts11.txt");
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
		ifstream typefile;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types10.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types11.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types12.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types18.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types16.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") typefile.open("D:/CCCC/Stop Motion/StopMotion/types17.txt");
		//ifstream typefile("D:/CCCC/Stop Motion/StopMotion/types11.txt");
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

int videoprocessor::matchFeatures(Mat image_1, Mat image_2)
{
	initModule_nonfree();
	vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptor_1, descriptor_2;

	Ptr<FeatureDetector> detector = FeatureDetector::create("HARRIS");
	detector->detect(image_1, keypoints_1);
	detector->detect(image_2, keypoints_2);
	/*Mat display_1, display_2;
	drawKeypoints(image_1, keypoints_1, display_1, Scalar::all(-1), 0);
	drawKeypoints(image_2, keypoints_2, display_2, Scalar::all(-1), 0);
	imshow("1", display_1);
	imshow("2", display_2);*/
	//cout << keypoints_1.size() << endl;
	//cout << keypoints_2.size() << endl;

	int x_1 = 0;
	int y_1 = 0;
	for (int i = 0; i < keypoints_1.size(); i++)
	{
		x_1 += keypoints_1.at(i).pt.x;
		y_1 += keypoints_1.at(i).pt.y;
	}
	int x_2 = 0;
	int y_2 = 0;
	for (int j = 0; j < keypoints_2.size(); j++)
	{
		x_2 += keypoints_2.at(j).pt.x;
		y_2 += keypoints_2.at(j).pt.y;
	}

	cout << keypoints_1.size() << " " << keypoints_2.size() << endl;
	//cout << double(x_1) / keypoints_1.size() << " " << double(y_1) / keypoints_1.size() << " " << double(x_2) / keypoints_2.size() << " " << double(y_2) / keypoints_2.size() << endl;
	//if (abs(double(x_1) / keypoints_1.size() - double(x_2) / keypoints_2.size()) < 2 && abs(double(y_1) / keypoints_1.size() - double(y_2) / keypoints_2.size()) < 2) // 4 for test
	if (abs(double(x_1) / keypoints_1.size() - double(x_2) / keypoints_2.size()) < 2 && abs(double(y_1) / keypoints_1.size() - double(y_2) / keypoints_2.size()) < 2)
		return -1;
	//cout << "Here" << endl;
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SIFT");
	descriptor_extractor->compute(image_1, keypoints_1, descriptor_1);
	descriptor_extractor->compute(image_2, keypoints_2, descriptor_2);

	BFMatcher matcher(NORM_L2);
	vector<vector<DMatch>> allMatches;
	matcher.knnMatch(descriptor_1, descriptor_2, allMatches, 1);
	vector<DMatch> matches;

	float min = 100;
	float max = 0;

	for (int i = 0; i < allMatches.size(); i++)
	{
		for (int j = 0; j < allMatches[i].size(); j++)
		{
			if (allMatches[i][j].distance < min)
				min = allMatches[i][j].distance;
			if (allMatches[i][j].distance > max)
				max = allMatches[i][j].distance;
		}
	}

	min = min < 0.01f ? 0.01f : min;
	//cout << min << " " << max << endl;
	int not_moving_count = 0;
	for (int i = 0; i < allMatches.size(); i++)
	{
		for (int j = 0; j < allMatches[i].size(); j++)
		{
			if (allMatches[i][j].distance < 15 * min) // 7 for test, 6
			{
				Point2f point1 = keypoints_1[allMatches[i][j].queryIdx].pt;
				Point2f point2 = keypoints_2[allMatches[i][j].trainIdx].pt;
				//cout << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << endl;
				if (abs(point1.x - point2.x) < 50 && abs(point1.y - point2.y) < 50) // for test4 could be 40 I think.
				{
					//cout << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << endl;
					matches.push_back(allMatches[i][j]);
				}
				//matches.push_back(allMatches[i][j]);
				if (abs(point1.x - point2.x) <= 5 && abs(point1.y - point2.y) <= 5) not_moving_count++;
			}
		}
	}
	cout << matches.size() << endl;
	//cout << not_moving_count << endl << endl;

	/*Mat image_matches;
	drawMatches(image_1, keypoints_1, image_2, keypoints_2, matches, image_matches, Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("Matches", image_matches);*/
	
	return (matches.size() - not_moving_count);
}