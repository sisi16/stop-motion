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
}

void videoprocessor::readVideo(const string file)
{
	//start = clock();
	if (file == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 315;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/XTTRA1/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 26;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/XTTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 325;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 736;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 417;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 457;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 1394;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 631;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/Videos/Real.avi")
	{
		fileName = file;
		num_of_frames = 1411;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else if (file == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg")
	{
		fileName = file;
		num_of_frames = 312;
		frame_width = 1920;
		frame_height = 1080;
		frame_rate = 15;
		cout << frame_rate << endl;
	}
	else
	{
		VideoCapture capture(file);
		if (!capture.isOpened())
			throw "Error when reading the video file";
		fileName = file;
		num_of_frames = capture.get(CV_CAP_PROP_FRAME_COUNT);
		frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
		frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		frame_rate = capture.get(CV_CAP_PROP_FPS);
		cout << frame_rate << endl;
		capture.release();
	}

	// TEST
	stringstream ss;
	string type = ".jpg";
	Mat frame, dst_1, dst_2;
	VideoCapture capture(file);
	double time;
	start = clock();
	time = (double)start / CLOCKS_PER_SEC;
	logger.push_back(QString::number(time).toStdString() + "  start loading frames...");
	cout << time << endl;
	//#pragma omp parallel for
	for (int i = 0; i < num_of_frames; i++) // i+...
    {
		capture >> frame;
		ss << i << type;
		//cv::imwrite("D:/CCCC/Stop Motion/US_XT2/1080/" + ss.str(), frame);
		pyrDown(frame, dst_1, Size(960, 540)); // frame.cols / 2, frame.rows / 2
		cv::imwrite("D:/CCCC/Stop Motion/XTTRA2/nn540/" + ss.str(), dst_1);
		pyrDown(dst_1, dst_2, Size(480, 270)); // dst_1.cols / 2, dst_1.rows / 2
		cv::imwrite("D:/CCCC/Stop Motion/XTTRA2/n270/" + ss.str(), dst_2);
		ss.str("");
    }
	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	cout << time << endl;
	logger.push_back(QString::number(time).toStdString() + "  finish loading frames");
	capture.release();

	Mat temp;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") temp = imread("D:/CCCC/Stop Motion/Test6/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") temp = imread("D:/CCCC/Stop Motion/Test7/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") temp = imread("D:/CCCC/Stop Motion/Test8/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/UserTest_Tra1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/UserTest_Tra2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") temp = imread("D:/CCCC/Stop Motion/US_SS1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") temp = imread("D:/CCCC/Stop Motion/US_SS2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") temp = imread("D:/CCCC/Stop Motion/XT1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") temp = imread("D:/CCCC/Stop Motion/XT2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_SSTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/XTTRA1/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/XTTRA1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/XTTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/XTTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") temp = imread("D:/CCCC/Stop Motion/US_ZL1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") temp = imread("D:/CCCC/Stop Motion/US_ZL2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_ZLTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") temp = imread("D:/CCCC/Stop Motion/US_JJ1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") temp = imread("D:/CCCC/Stop Motion/US_JJ2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") temp = imread("D:/CCCC/Stop Motion/US_LL1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") temp = imread("D:/CCCC/Stop Motion/US_LL2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") temp = imread("D:/CCCC/Stop Motion/US_XR1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") temp = imread("D:/CCCC/Stop Motion/US_XR2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") temp = imread("D:/CCCC/Stop Motion/US_QK1/540/0.jpg"); // i+...
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") temp = imread("D:/CCCC/Stop Motion/US_QK2/540/0.jpg"); // i+...
	else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_LLTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_XRTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_JJTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/US_ZXTRA2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") temp = imread("D:/CCCC/Stop Motion/Basic1/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") temp = imread("D:/CCCC/Stop Motion/Basic2/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") temp = imread("D:/CCCC/Stop Motion/Basic3/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") temp = imread("D:/CCCC/Stop Motion/Real/540/0.jpg");
	else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") temp = imread("D:/CCCC/Stop Motion/RealTra/540/0.jpg");
	//cvtColor(frames.at(0), temp, CV_BGR2RGB);
	//capture >> temp;
	cv::imwrite("D:/CCCC/Stop Motion/Videos/preview.png", temp);

    /*progressBar = new QProgressBar;
	progressBar->setRange(0, num_of_frames - 1);//progressBar->setRange(0, frames.size()-1);
    progressBar->setValue(0);*/

	//test();
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
	double time;
	vector<int> temp;
    int scene_count = 0;

	stringstream ss;
	string type = ".jpg";
	ofstream flowfile("D:/CCCC/Stop Motion/XT1/flows.txt"); // i+...
	Mat frame_1, frame_2;

	//#pragma omp parallel for
	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	cout << time << endl;
	logger.push_back(QString::number(time).toStdString() + "  start calculating optical flows...");

	for (int i = 0; i < num_of_frames - 1; i++) // i+...
    {
        //progressBar->setValue(i+1);

		if (i == 0) // i+...
		{
			frame_1 = imread("D:/CCCC/Stop Motion/XT1/270/0.jpg"); // i+...
			frame_2 = imread("D:/CCCC/Stop Motion/XT1/270/1.jpg");
		}
		else
		{
			ss << i + 1 << type;
			frame_1 = frame_2;
			frame_2 = imread("D:/CCCC/Stop Motion/XT1/270/" + ss.str());
			ss.str("");
		}

		//cout << 1 << endl;
		Mat current_flow = of.calOpFlow(frame_1, frame_2);//Mat current_flow = of.calOpFlow(frames.at(i), frames.at(i + 1));
		//cout << 2 << endl;
        float current_avg_flow = of.calAvgOpFlow(current_flow);
		//cout << 3 << endl;
		flowfile << current_avg_flow << endl;

		//float current_avg_flow;
		//flowfile >> current_avg_flow;
		if (current_avg_flow < 1200)//if (current_avg_flow < 0.005) // if (current_avg_flow == 0)
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

	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	cout << time << endl;
	logger.push_back(QString::number(time).toStdString() + "  finish calculating optical flows");
	flowfile.close();

	int cut_counter = -1;
	int sum = 0;
	bool isMessy = false;
	int movingcount = 0;

	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	logger.push_back(QString::number(time).toStdString() + "  start segment clips...");
    for (int j = 0; j < temp.size(); j++)
    {	
		int length;
		int cut_type;

		if (j == 0) length = temp.at(j) + 1;
		else length = temp.at(j) - temp.at(j - 1);
		cut_type = frame_types.at(temp.at(j));

		if (length >= frame_rate)
		{
			if (isMessy)
			{
				if (cut_counter == -1)
				{
					//cout << 1 << endl;
					scene_cuts.push_back(temp.at(j));
					cut_types.push_back(cut_type);
					cut_counter++;
				}
				else 
				{
					int previous_length;
					if (cut_counter == 0) previous_length = scene_cuts.at(0) + 1;
					else previous_length = scene_cuts.at(cut_counter) - scene_cuts.at(cut_counter - 1);
					
					if (cut_types.at(cut_counter) == cut_type)
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
				cut_types.push_back(cut_type);
				cut_counter++;
			}
		}
		else if (isMessy)
		{
			sum += length;
			if (cut_type == 2) movingcount += length;
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
			// sum >= frame_rate * 2
			else if (sum >= frame_rate && (temp.at(j + 1) - temp.at(j)) >= frame_rate) //else if (sum >= frame_rate * 2 && (temp.at(j + 1) - temp.at(j)) >= frame_rate)
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
						cut_types.push_back(cut_type);
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
				if (cut_type == 2) movingcount += length;
			}
		}
    }
	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	logger.push_back(QString::number(time).toStdString() + "  finish segment clips...");
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

vector<bool> videoprocessor::test()
{	
	double logtime;
	
	/*stringstream ss;
	string type = ".jpg";
	Mat frame, prevframe;
	int index, num_small_move, num_move_object;

	ofstream matchfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") matchfile.open("D:/CCCC/Stop Motion/Test6/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") matchfile.open("D:/CCCC/Stop Motion/Test7/matches_2.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") matchfile.open("D:/CCCC/Stop Motion/Test8/matches_3.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") matchfile.open("D:/CCCC/Stop Motion/US_SS1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") matchfile.open("D:/CCCC/Stop Motion/US_SS2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") matchfile.open("D:/CCCC/Stop Motion/XT1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") matchfile.open("D:/CCCC/Stop Motion/XT2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") matchfile.open("D:/CCCC/Stop Motion/US_ZL1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") matchfile.open("D:/CCCC/Stop Motion/US_ZL2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") matchfile.open("D:/CCCC/Stop Motion/US_JJ1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") matchfile.open("D:/CCCC/Stop Motion/US_JJ2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") matchfile.open("D:/CCCC/Stop Motion/US_LL1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") matchfile.open("D:/CCCC/Stop Motion/US_LL2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") matchfile.open("D:/CCCC/Stop Motion/US_XR1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") matchfile.open("D:/CCCC/Stop Motion/US_XR2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") matchfile.open("D:/CCCC/Stop Motion/US_QK1/matches.txt"); // i+...
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") matchfile.open("D:/CCCC/Stop Motion/US_QK2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") matchfile.open("D:/CCCC/Stop Motion/Basic1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") matchfile.open("D:/CCCC/Stop Motion/Basic2/matches.txt"); 
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") matchfile.open("D:/CCCC/Stop Motion/Basic3/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") matchfile.open("D:/CCCC/Stop Motion/Real/matches.txt");
	//start = clock();
	logtime = (double)(clock()-start) / CLOCKS_PER_SEC;
	logger.push_back(QString::number(logtime).toStdString() + "  start PatchMatch & match features...");
	
	for (int i = 0; i < scene_cuts.size(); i += 2)
	{
		if (i == 0) index = scene_cuts[0] / 2; //i+...
		else index = (scene_cuts[i] + scene_cuts[i - 1] + 1) / 2;
		ss << index << type;
	
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") frame = imread("D:/CCCC/Stop Motion/US_SS1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") frame = imread("D:/CCCC/Stop Motion/US_SS2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") frame = imread("D:/CCCC/Stop Motion/XT1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") frame = imread("D:/CCCC/Stop Motion/XT2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") frame = imread("D:/CCCC/Stop Motion/US_LL1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") frame = imread("D:/CCCC/Stop Motion/US_LL2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") frame = imread("D:/CCCC/Stop Motion/US_XR1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") frame = imread("D:/CCCC/Stop Motion/US_XR2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") frame = imread("D:/CCCC/Stop Motion/US_QK1/270/" + ss.str()); // i+...
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") frame = imread("D:/CCCC/Stop Motion/US_QK2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") frame = imread("D:/CCCC/Stop Motion/Basic1/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") frame = imread("D:/CCCC/Stop Motion/Basic2/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") frame = imread("D:/CCCC/Stop Motion/Basic3/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") frame = imread("D:/CCCC/Stop Motion/Real/270/" + ss.str());
		ss.str("");

		if (i != 0)
		{
			vector<vector<Point>> contours = of.patchMatch(prevframe, frame);
			int size = contours.size();
			int area_sum = 0;
			for (int i = 0; i < size; i++)
				area_sum += contourArea(contours[i]);
			num_small_move = matchFeatures(prevframe, frame); //matchfile << matchFeatures(prevframe, frame) << endl;
			matchfile << num_small_move << " " <<  size << " " << area_sum << endl;
		}
		prevframe = frame;
	}

	logtime = (double)(clock() - start) / CLOCKS_PER_SEC;
	logger.push_back(QString::number(logtime).toStdString() + "  finish PatchMatch & match features...");
	
	matchfile.close();*/

	ifstream imatchfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") imatchfile.open("D:/CCCC/Stop Motion/Test7/matches_2.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") imatchfile.open("D:/CCCC/Stop Motion/Test8/matches_2.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_SS1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_SS2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") imatchfile.open("D:/CCCC/Stop Motion/XT1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") imatchfile.open("D:/CCCC/Stop Motion/XT2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_ZL1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_ZL2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_JJ1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_JJ2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_LL1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_LL2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_XR1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_XR2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") imatchfile.open("D:/CCCC/Stop Motion/US_QK1/matches.txt"); //i+...a
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") imatchfile.open("D:/CCCC/Stop Motion/US_QK2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") imatchfile.open("D:/CCCC/Stop Motion/Basic1/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") imatchfile.open("D:/CCCC/Stop Motion/Basic2/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") imatchfile.open("D:/CCCC/Stop Motion/Basic3/matches.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") imatchfile.open("D:/CCCC/Stop Motion/Real/matches.txt");
	vector<bool> checkMovingClips;

	if (imatchfile.is_open())
	{
		int num, contour_size, contour_area; //, index;
		int idx = 1;

		/*index = scene_cuts[0] / 2;
		ss << index << type;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") prevframe = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") prevframe = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
		ss.str("");*/

		logtime = (double)(clock() - start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(logtime).toStdString() + " start decide which clips to drop...");

		while (imatchfile >> num >> contour_size >> contour_area)
		{
			/*index = (scene_cuts[idx+1] + scene_cuts[idx] + 1) / 2;
			ss << index << type;
			if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi")	frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
			
			vector<vector<Point>> contours = of.patchMatch(prevframe, frame);
			int size = contours.size();
			int area_sum = 0;
			cout << size << " ";
			if (size != 0)
			{
				for (int i = 0; i < size; i++)
					area_sum += contourArea(contours[i]);
			}
			else size = 1;
			ss.str("");*/
			//int num_small_move = matchFeatures(prevframe, frame);
			
			if (contour_size == 0) contour_size = 1;
			int time = scene_cuts[idx] - scene_cuts[idx - 1];
			//cout << area_sum << " " << num << endl;
			
			if (contour_area > 116640 || time > 150 * contour_size || num == 0) // 0.9*480*270
				checkMovingClips.push_back(false);
			else
				checkMovingClips.push_back(true);
			
			//prevframe = frame;
			idx += 2;
		}
		imatchfile.close();


		for (int i = 0; i < checkMovingClips.size(); i++)
		{
			if (i < (checkMovingClips.size()-1) && checkMovingClips[i] && checkMovingClips[i+1]) //&& checkMovingClips[i+2])
			{
				i += 2;
				while (i < checkMovingClips.size() && checkMovingClips[i])
					i++;
			}
			else
				checkMovingClips[i] = false;
		}

		logtime = (double)(clock() - start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(logtime).toStdString() + "  finish decide which clips to drop...");

		//for (int j = 0; j < checkMovingClips.size(); j++)
			//cout << checkMovingClips[j] << endl;

		/*ofstream logfile("D:/CCCC/Stop Motion/XT1/algo_logs_1.txt"); // i+...
		if (logfile.is_open())
		{
			for (int i = 0; i < logger.size(); i++)
				logfile << logger[i] << endl;
			logfile.close();
		}
		else cout << "Unable to open file" << endl;*/
	}
	else cout << "Unable to open file" << endl;

	return checkMovingClips;
}

void videoprocessor::writeBuffers()
{
	ofstream cutfile("D:/CCCC/Stop Motion/XT1/cuts.txt"); //i+...
	if (cutfile.is_open())
	{
		for (int i = 0; i < scene_cuts.size(); i++)
			cutfile << scene_cuts.at(i) << endl;
		cutfile.close();
	}
	else cout << "Unable to open file" << endl;

	ofstream typefile("D:/CCCC/Stop Motion/XT1/types.txt"); //i+...
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
		else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cutsTra1.txt");
		else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/StopMotion/cutsTra2.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") cutfile.open("D:/CCCC/Stop Motion/US_SS1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") cutfile.open("D:/CCCC/Stop Motion/US_SS2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") cutfile.open("D:/CCCC/Stop Motion/XT1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") cutfile.open("D:/CCCC/Stop Motion/XT2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_SSTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/XTTRA1/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/XTTRA1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/XTTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/XTTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_ZLTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") cutfile.open("D:/CCCC/Stop Motion/US_ZL1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") cutfile.open("D:/CCCC/Stop Motion/US_ZL2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") cutfile.open("D:/CCCC/Stop Motion/US_JJ1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") cutfile.open("D:/CCCC/Stop Motion/US_JJ2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") cutfile.open("D:/CCCC/Stop Motion/US_LL1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") cutfile.open("D:/CCCC/Stop Motion/US_LL2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") cutfile.open("D:/CCCC/Stop Motion/US_XR1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") cutfile.open("D:/CCCC/Stop Motion/US_XR2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") cutfile.open("D:/CCCC/Stop Motion/US_QK1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") cutfile.open("D:/CCCC/Stop Motion/US_QK2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_LLTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_XRTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_JJTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/US_ZXTRA2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") cutfile.open("D:/CCCC/Stop Motion/Basic1/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") cutfile.open("D:/CCCC/Stop Motion/Basic2/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") cutfile.open("D:/CCCC/Stop Motion/Basic3/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") cutfile.open("D:/CCCC/Stop Motion/Real/cuts.txt");
		else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") cutfile.open("D:/CCCC/Stop Motion/RealTra/cuts.txt");
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
		else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/StopMotion/typesTra1.txt");
		else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/StopMotion/typesTra2.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") typefile.open("D:/CCCC/Stop Motion/US_SS1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") typefile.open("D:/CCCC/Stop Motion/US_SS2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") typefile.open("D:/CCCC/Stop Motion/XT1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") typefile.open("D:/CCCC/Stop Motion/XT2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_SSTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/XTTRA1/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/XTTRA1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/XTTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/XTTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_ZLTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") typefile.open("D:/CCCC/Stop Motion/US_ZL1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") typefile.open("D:/CCCC/Stop Motion/US_ZL2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") typefile.open("D:/CCCC/Stop Motion/US_JJ1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") typefile.open("D:/CCCC/Stop Motion/US_JJ2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") typefile.open("D:/CCCC/Stop Motion/US_LL1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") typefile.open("D:/CCCC/Stop Motion/US_LL2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") typefile.open("D:/CCCC/Stop Motion/US_XR1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") typefile.open("D:/CCCC/Stop Motion/US_XR2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") typefile.open("D:/CCCC/Stop Motion/US_QK1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") typefile.open("D:/CCCC/Stop Motion/US_QK2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_LLTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_XRTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_JJTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/US_ZXTRA2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") typefile.open("D:/CCCC/Stop Motion/Basic1/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") typefile.open("D:/CCCC/Stop Motion/Basic2/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") typefile.open("D:/CCCC/Stop Motion/Basic3/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") typefile.open("D:/CCCC/Stop Motion/Real/types.txt");
		else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") typefile.open("D:/CCCC/Stop Motion/RealTra/types.txt");
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
	//TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	//Size subPixWinSize(10, 10), winSize(31, 31);

	initModule_nonfree();
	vector<KeyPoint> keypoints_1, keypoints_2;
	//vector<Point2f> points_1, points_2;
	Mat descriptor_1, descriptor_2;

	cv::GoodFeaturesToTrackDetector detector(
		500,    // maximum number of corners to be returned  
		0.01,   // quality level  
		10);    // minimum allowed distance between points
	//Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
	detector.detect(image_1, keypoints_1);
	detector.detect(image_2, keypoints_2);
	/*KeyPoint::convert(keypoints_1, points_1);
	KeyPoint::convert(keypoints_2, points_2);
	cornerSubPix(image_1, points_1, subPixWinSize, Size(-1, -1), termcrit);
	cornerSubPix(image_2, points_2, subPixWinSize, Size(-1, -1), termcrit);*/

	/*Mat display_1, display_2;
	drawKeypoints(image_1, keypoints_1, display_1, Scalar::all(-1), 0);
	drawKeypoints(image_2, keypoints_2, display_2, Scalar::all(-1), 0);
	imshow("1", display_1);
	imshow("2", display_2);*/
	//cout << keypoints_1.size() << endl;
	//cout << keypoints_2.size() << endl;

	/*int x_1 = 0;
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
	}*/

	//cout << keypoints_1.size() << " " << keypoints_2.size() << endl;
	//cout << double(x_1) / keypoints_1.size() << " " << double(y_1) / keypoints_1.size() << " " << double(x_2) / keypoints_2.size() << " " << double(y_2) / keypoints_2.size() << endl;
	//if (abs(double(x_1) / keypoints_1.size() - double(x_2) / keypoints_2.size()) < 2 && abs(double(y_1) / keypoints_1.size() - double(y_2) / keypoints_2.size()) < 2) // 4 for test
	//if (abs(double(x_1) / keypoints_1.size() - double(x_2) / keypoints_2.size()) < 2 && abs(double(y_1) / keypoints_1.size() - double(y_2) / keypoints_2.size()) < 2)
		//return -1;
	//cout << "Here" << endl;
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SIFT");
	descriptor_extractor->compute(image_1, keypoints_1, descriptor_1);
	descriptor_extractor->compute(image_2, keypoints_2, descriptor_2);

	FlannBasedMatcher matcher; // BFMatcher matcher(NORM_L2);
	vector<vector<DMatch>> allMatches;
	matcher.knnMatch(descriptor_1, descriptor_2, allMatches, 2);
	vector<DMatch> matches;

	//float min = 100;
	float max = 0;

	for (int i = 0; i < allMatches.size(); i++)
	{
		//if (allMatches[i][0].distance < min)
			//min = allMatches[i][0].distance;
		if (allMatches[i][0].distance > max)
			max = allMatches[i][0].distance;
	}

	//min = min < 0.01f ? 0.01f : min;
	//cout << min << " " << max << endl;
	int total = 0;
	int small_or_no_move = 0;
	float min_distance = 1000;
	float max_distance = -1;
	
	/*vector<vector<Point>> filterContours;
	vector<Point2f>center(size);
	vector<float>radius(size);
	for (int i = 0; i < size; i++)
		minEnclosingCircle((Mat)contours[i], center[i], radius[i]);*/
	
	for (int i = 0; i < allMatches.size(); i++)
	{
		//for (int j = 0; j < allMatches[i].size(); j++)
		//{
			if (allMatches[i][0].distance < 0.8 * allMatches[i][1].distance && allMatches[i][0].distance * 3 <= max * 2) // 2/3
			{
				total++;
				Point2f point1 = keypoints_1[allMatches[i][0].queryIdx].pt;
				Point2f point2 = keypoints_2[allMatches[i][0].trainIdx].pt;
				float flowx = abs(point1.x - point2.x);
				float flowy = abs(point1.y - point2.y);
				//cout << flowx << " " << flowy << endl;
				
				/*for (int i = 0; i < contours.size(); i++)
				{
					float dx1 = point1.x - center[i].x; float dy1 = point1.y - center[i].y;
					float dx2 = point2.x - center[i].x; float dy2 = point2.y - center[i].y;
					if (sqrt(dx1*dx1 + dy1*dy1) <= radius[i] + 15
						|| sqrt(dx2*dx2 + dy2*dy2) <= radius[i] + 15)
					{
						object++;
						//filterContours.push_back(contours[i]);
						contours.erase(contours.begin() + i);
						break;
					}
				}*/
				
				if (flowx <= 96 && flowy <= 54) // 40.5, 72
				{
					small_or_no_move++;
					if (flowx >= 4.8 || flowy >= 2.7)
					{
						matches.push_back(allMatches[i][0]);
					}
					//else if ((flowx >= 2.7 && flowx <= 40.5 && flowy < 4.8) || (flowy >= 4.8 && flowy <= 72 && flowx < 2.7)) 
				}
				//matches.push_back(allMatches[i][j]);
			}
		//}
	}

	/*Mat image_matches;
	drawMatches(image_1, keypoints_1, image_2, keypoints_2, matches, image_matches, Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("Matches", image_matches);
	Mat temp = image_1;
	drawContours(temp, filterContours, -1, Scalar(0, 0, 0), 1);
	imshow("Flow", temp);*/
	
	int small_move = matches.size();
	int size_1 = keypoints_1.size() - total;
	int size_2 = keypoints_2.size() - total;
	//cout << small_move << " " << total - small_or_no_move << endl;
	//cout << size_1 << " " << size_2 << endl;
	//cout << nearest.x << " " << nearest.y << " " << farthest.x << " " << farthest.y << endl;
		
	if (small_move > 0 && small_move < total - small_or_no_move)
		return 0;
	else if (small_move == 0 && size_2 > 2 * size_1 && size_2 - size_1 > 5)
		return size_2;
	else
		return small_move;
}

vector<int> videoprocessor::checkCuts(vector<int> checkRange)
{
	ifstream flowfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") flowfile.open("D:/CCCC/Stop Motion/Test7/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") flowfile.open("D:/CCCC/Stop Motion/Test8/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") flowfile.open("D:/CCCC/Stop Motion/US_SS1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") flowfile.open("D:/CCCC/Stop Motion/US_SS2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT1.avi") flowfile.open("D:/CCCC/Stop Motion/XT1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/XT2.avi") flowfile.open("D:/CCCC/Stop Motion/XT2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") flowfile.open("D:/CCCC/Stop Motion/US_ZL1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") flowfile.open("D:/CCCC/Stop Motion/US_ZL2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") flowfile.open("D:/CCCC/Stop Motion/US_JJ1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") flowfile.open("D:/CCCC/Stop Motion/US_JJ2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") flowfile.open("D:/CCCC/Stop Motion/US_LL1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") flowfile.open("D:/CCCC/Stop Motion/US_LL2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") flowfile.open("D:/CCCC/Stop Motion/US_XR1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") flowfile.open("D:/CCCC/Stop Motion/US_XR2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") flowfile.open("D:/CCCC/Stop Motion/US_QK1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") flowfile.open("D:/CCCC/Stop Motion/US_QK2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") flowfile.open("D:/CCCC/Stop Motion/Basic1/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") flowfile.open("D:/CCCC/Stop Motion/Basic2/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") flowfile.open("D:/CCCC/Stop Motion/Basic3/flows.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") flowfile.open("D:/CCCC/Stop Motion/Real/flows.txt");
	if (flowfile.is_open())
	{  
		float num;
		int count = 0;
		int begin = checkRange[0];
		int end = checkRange[1];
		bool processing = false;
		vector<int> cutRanges;
		while (flowfile >> num)
		{
			if (count >= begin && count <= end)
			{
				int size = cutRanges.size();
				if (num <= 2000)//if (num <= 0.1)
				{	
					if (!processing)
					{
						cutRanges.push_back(count);
						cutRanges.push_back(count + 1);
						processing = true;
					}
					else
						cutRanges[size-1]++;
					
					size = cutRanges.size();
					if (count == end && cutRanges[size-1] - cutRanges[size-2] < 4)
					{
						cutRanges.pop_back();
						cutRanges.pop_back();
					}
				}
				else if (processing)
				{
					if (cutRanges[size-1] - cutRanges[size-2] < 4)
					{
						cutRanges.pop_back();
						cutRanges.pop_back();
					}
					processing = false;
				}
			}
			count++;
		}
		flowfile.close();
		for (size_t i = 0; i < cutRanges.size(); i++)
			cout << cutRanges[i] << endl;
		return cutRanges;
	}
	else cout << "Unable to open file" << endl;
}