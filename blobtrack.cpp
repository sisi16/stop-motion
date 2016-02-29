#include "blobtrack.h"

using namespace std;
using namespace cv;

///////////////// blob ///////////////////

blob::blob(float bx, float by, float size)
{
	x = bx;
	y = by;
	area = size;
}

blob::~blob()
{
}


/////// blobDetector ///////

blobDetector::blobDetector()
{
}

blobDetector::~blobDetector()
{
}

void blobDetector::process(const string filename, int numOfFrames)
{
	stringstream ss;
	string type = ".jpg";
	Mat frame, mask, temp;
	BackgroundSubtractorMOG bgSubtractor(50, 5, 0.7);
	int delay = 100;

	for (int i = 0; i < numOfFrames; i++)//for (int i = 70; i < 120; i++)//for (int i = 1020; i < 1055; i++)//
	{
		ss << i << type;
		if (filename == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
		ss.str("");

		vector<vector<Point>> contours;
		vector<vector<Point>> filterContours;
		vector<Vec4i> hierarchy;
		contours.clear();
		filterContours.clear();
		hierarchy.clear();

		//bgSubtractor(frame, mask, 0.002); //0.001
		//imshow("Mask", mask);
		temp = frame;
		hd.isHand(temp, mask);
		imshow("Mask", mask);
		findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		
		//comment
		/*if (contours.size() > 2)
		{
			sort(contours.begin(), contours.end(), blobDetector::more_area);
			if (contourArea(contours[0])>1000) filterContours.push_back(contours[0]);
			if (contourArea(contours[0])>1000) filterContours.push_back(contours[1]);
			//drawContours(frame, filterContours, -1, Scalar(0, 0, 255), 2);
		}
		else if (!contours.empty())
		{
			for (int j = 0; j < contours.size(); j++)
				if (contourArea(contours[j])>1000) filterContours.push_back(contours[j]);
		}*/

		/*int rows = frame.rows;
		int cols = frame.cols;
		Mat hsv_frame(rows, cols, CV_8UC3);
		cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
		for (unsigned int contourIdx = 0; contourIdx < contours.size(); contourIdx++)
		{
			//Moments moms = moments(contours[contourIdx]);
			//Point2f center = Point2f(moms.m10 / moms.m00, moms.m01 / moms.m00);
			if (contourArea(contours[contourIdx])>650) //&& hd.isHand(hsv_frame, contours[contourIdx]))
				filterContours.push_back(contours[contourIdx]);
		}*/

		for (unsigned int contourIdx = 0; contourIdx < contours.size(); contourIdx++)
		{
			//Moments moms = moments(contours[contourIdx]);
			//Point2f center = Point2f(moms.m10 / moms.m00, moms.m01 / moms.m00);
			if (contourArea(contours[contourIdx]) > 650)
				filterContours.push_back(contours[contourIdx]);
		}

		/// Find the convex hull object for each contour  
		vector<vector<Point> >hull(filterContours.size());
		// Int type hull  
		vector<vector<int>> hullsI(filterContours.size());
		// Convexity defects  
		vector<vector<Vec4i>> defects(filterContours.size());

		for (size_t i = 0; i < filterContours.size(); i++)
		{
			convexHull(Mat(filterContours[i]), hull[i], false);
			// find int type hull  
			convexHull(Mat(filterContours[i]), hullsI[i], false);
			// get convexity defects  
			convexityDefects(Mat(filterContours[i]), hullsI[i], defects[i]);
			drawContours(frame, hull, i, Scalar(0, 0, 255), 2);
			
			for (const Vec4i& v : defects[i])
			{
				float depth = v[3] / 256;
				if (depth > 15) //  filter defects by depth, e.g more than 10
				{
					int startidx = v[0]; Point ptStart(filterContours[i][startidx]);
					int endidx = v[1]; Point ptEnd(filterContours[i][endidx]);
					int faridx = v[2]; Point ptFar(filterContours[i][faridx]);
					double x = double(ptStart.x + ptEnd.x) / 2;
					double y = double(ptStart.y + ptEnd.y) / 2;
					if (y < ptFar.y && abs((y - ptFar.y) / (x - ptFar.x)) > 0.58)
					{
						line(frame, ptStart, ptEnd, Scalar(0, 255, 0), 1);
						line(frame, ptStart, ptFar, Scalar(0, 255, 0), 1);
						line(frame, ptEnd, ptFar, Scalar(0, 255, 0), 1);
						circle(frame, ptFar, 4, Scalar(0, 255, 0), 2);
					}
				}
			}
		}

		//if (!filterContours.empty()) drawContours(frame, filterContours, -1, Scalar(0, 0, 255), 2);
		imshow("Blobs", frame);
		if (waitKey(delay) == 27) break;
		if (waitKey(delay) == 32) waitKey(0);
		//waitKey(100);
	}
}

void blobDetector::klt(const string filename, int numOfFrames)
{
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);
	const int MAX_COUNT = 500;
	bool needToInit = true;
	int delay = 100;

	Mat gray, prevGray, image;
	//vector<KeyPoint> keypoints;
	vector<Point2f> points[2];
	stringstream ss;
	string type = ".jpg";

	//cv::initModule_nonfree();//if use SIFT or SURF
	//Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");

	for (int i = 0; i < numOfFrames; i++)//for (int i = 70; i < 120; i++)//for (int i = 1020; i < 1055; i++)//
	{
		Mat frame;
		ss << i << type;
		if (filename == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
		else if (filename == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
		ss.str("");

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		if (needToInit)
		{
			// automatic initialization
			goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 1, 0.04);//detector->detect(image, keypoints);
			//KeyPoint::convert(keypoints, points[1]);
			cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);
			for (size_t i = 0; i < points[1].size(); i++)
				circle(image, points[1][i], 3, Scalar(0, 255, 255), -1, 8);
		}
		else if (!points[0].empty())
		{
			vector<uchar> status;
			vector<float> err;
			if (prevGray.empty())
				gray.copyTo(prevGray);
			calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
				3, termcrit, 0, 0.001);
			size_t i, k;
			for (i = k = 0; i < points[1].size(); i++)
			{
				if (!status[i])
					continue;

				points[1][k++] = points[1][i];
				circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
			}
			points[1].resize(k);
		}

		if ((i+1) % 5 == 0) needToInit = true;
		else needToInit = false;
		imshow("LK", image);
		if (waitKey(delay) == 27) break;
		if (waitKey(delay) == 32) waitKey(0);
		std::swap(points[1], points[0]);
		cv::swap(prevGray, gray);
	}
}

//////////////// blobtrack ////////////////

blobtrack::blobtrack(const string filename, const int numOfFrames)
{
	file = filename;
	num_of_frames = numOfFrames;
}

blobtrack::~blobtrack()
{
	if (bDetector != NULL)
	{
		delete bDetector;
		bDetector = NULL;
	}
}

void blobtrack::process()
{
	bDetector = new blobDetector();
	//bDetector->process(file, num_of_frames);
	bDetector->klt(file, num_of_frames);
}

