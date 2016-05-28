#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //resize_count = -1;
    //window_current_width = this->width();
    //window_current_height = this->height() - ui->menuBar->height() - ui->mainToolBar->height();
	isCut = false;
	entered = false;
	isCounting = false;
	ui->frameLabel->setScaledContents(true);
	//ui->scrollArea->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_1->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_2->setBackgroundRole(QPalette::Midlight);
	frame_slider = new myslider(Qt::Horizontal);
	ui->verticalLayout->addWidget(frame_slider);
	//addedTrackCount = 0;
}

MainWindow::~MainWindow()
{
	delete myPlayer;
    delete ui;
}

void MainWindow::refresh(int index)
{
	stringstream ss;
	string type = ".jpg";
	Mat frame;
	ss << index << type;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/UserTest_Tra1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/UserTest_Tra2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") frame = imread("D:/CCCC/Stop Motion/US_SS1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") frame = imread("D:/CCCC/Stop Motion/US_SS2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT1.avi") frame = imread("D:/CCCC/Stop Motion/US_XT1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT2.avi") frame = imread("D:/CCCC/Stop Motion/US_XT2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_SSTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_XTTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_XTTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_ZLTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") frame = imread("D:/CCCC/Stop Motion/US_LL1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") frame = imread("D:/CCCC/Stop Motion/US_LL2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") frame = imread("D:/CCCC/Stop Motion/US_XR1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") frame = imread("D:/CCCC/Stop Motion/US_XR2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") frame = imread("D:/CCCC/Stop Motion/US_QK1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") frame = imread("D:/CCCC/Stop Motion/US_QK2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_LLTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_XRTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_JJTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_ZXTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") frame = imread("D:/CCCC/Stop Motion/Basic1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") frame = imread("D:/CCCC/Stop Motion/Basic2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") frame = imread("D:/CCCC/Stop Motion/Basic3/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") frame = imread("D:/CCCC/Stop Motion/Real/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/RealTra/540/" + ss.str());
	ss.str("");

	cv::Mat temp;
	cvtColor(frame, temp, CV_BGR2RGB);
	QImage current_image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	current_image.bits();

	QPixmap pix(ui->frameLabel->width(), ui->frameLabel->height());
	pix.fill(Qt::black);
	QPainter *paint = new QPainter(&pix);
	int w = pix.width();
	int h = pix.height();
	if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg")
		paint->drawPixmap((w-h*4/3)/2, 0, h*4/3, h, QPixmap::fromImage(current_image));
	else
		paint->drawPixmap((w-h*16/9)/2, 0, h*16/9, h, QPixmap::fromImage(current_image));
	if (ui->editRadioButton->isChecked() && index == current_clip->getRange().at(0))
	{
		stringstream ss_1, ss_2;
		string type = ".jpg";
		Mat frame_1, frame_2;
		int start = current_clip->getRange().at(0);
		int end = current_clip->getRange().at(1);
		ss_1 << (start + end) / 2 << type;
		ss_2 << end << type;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test6/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test6/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test7/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test7/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test8/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test8/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/UserTest_Tra2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/UserTest_Tra2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_SS1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_SS1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_SS2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_SS2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XT1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XT1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XT2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XT2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_SSTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_SSTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_XTTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XTTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XTTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_ZLTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_ZLTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_ZL1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_ZL1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_ZL2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_ZL2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_JJ1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_JJ1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_JJ2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_JJ2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_LL1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_LL1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_LL2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_LL2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XR1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XR1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XR2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XR2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_QK1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_QK1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_QK2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_QK2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_LLTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_LLTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_XRTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_XRTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_JJTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_JJTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/US_ZXTRA2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/US_ZXTRA2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Basic1/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Basic1/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Basic2/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Basic2/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Basic3/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Basic3/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Real/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Real/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/RealTra/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/RealTra/540/" + ss_2.str());
		}
		ss_1.str("");
		ss_2.str("");

		cvtColor(frame_1, temp, CV_BGR2RGB);
		QImage image_1((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image_1.bits();
		cvtColor(frame_2, temp, CV_BGR2RGB);
		QImage image_2((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image_2.bits();

		QPixmap pix_1((w-h*16/9)/3, h*3/5);
		QPixmap pix_2((w-h*16/9)/6, h/3);
		QPainter *paint_1 = new QPainter(&pix_1);
		QPainter *paint_2 = new QPainter(&pix_2);
		pix_1.fill(Qt::darkGray);
		pix_2.fill(Qt::darkGray);
		paint_1->drawPixmap(0, (pix_1.height()-pix_1.width()*9/16)/2, pix_1.width(), pix_1.width()*9/16, QPixmap::fromImage(image_1));
		paint_1->end();
		paint_2->drawPixmap(0, (pix_2.height()-pix_2.width()*9/16)/2, pix_2.width(), pix_2.width()*9/16, QPixmap::fromImage(image_2));
		paint_2->end();
		paint->drawPixmap((w+h*16/9)/2, h/5, pix_1.width(), pix_1.height(), pix_1);
		paint->drawPixmap((w*5+h*16/9)/6, h/3, pix_2.width(), pix_2.height(), pix_2);
	}
	paint->end();
	ui->frameLabel->setStyleSheet("");
	ui->frameLabel->setPixmap(pix);
	ui->frameLabel->repaint();
}

void MainWindow::visualizeClips()
{
	vector<bool> isDropped;
	vector<int> scene_cuts = vproc.getSceneCuts();
	vector<int> cut_types = vproc.getCutTypes();
	//vector<Mat> frames = vproc.getFrames();
	int frameRate = vproc.getFrameRate();
	int height = floor(0.8 * ui->scrollArea_1->height());
	int base_width = ceil(height * vproc.getFrameWidth() / double(vproc.getFrameHeight()));
	int base, end, width, cut_size, length;

	/*myscrollarea *scroll = new myscrollarea();
	ui->verticalLayout->addWidget(scroll);
	scroll->getCentralWidget()->installEventFilter(this);
	addedTrackCount++;
	addedTrack.push_back(scroll);*/

	stringstream ss;
	string type = ".jpg";

	if (fileName != "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_XTTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg"
		&& fileName != "D:/CCCC/Stop Motion/Videos/Real.avi"
		&& fileName != "D:/CCCC/Stop Motion/RealTra/1080/0.jpg")
		isDropped = vproc.test();
	/*ifstream flowfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") flowfile.open("D:/CCCC/Stop Motion/Test6/suggestion_threshold.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") flowfile.open("D:/CCCC/Stop Motion/Test7/suggestion_threshold.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") flowfile.open("D:/CCCC/Stop Motion/Test8/suggestion_threshold.txt");*/

	for (int i = 0; i < scene_cuts.size(); i++)
	{
		vector<Mat> srcImages;
		if (i == 0) // i+...
			base = 0;
		else
			base = scene_cuts.at(i - 1) + 1;
		end = scene_cuts[i];
		cut_size = scene_cuts.at(i) - base + 1;

		if (cut_size % (2 * frameRate) == 0)
			length = cut_size / (2 * frameRate);
		else
			length = cut_size / (2 * frameRate) + 1;

		if (cut_size > 1 && cut_types.at(i) == 1)
			width = base_width + base_width / 10 * (length - 1);
		else
			width = base_width * length;

		for (int j = 0; j < length; j++)
		{
			if (cut_types[i] == 1)
				ss << (base + end) / 2 << type;
			else if (cut_types[i] == 2)
				ss << base + 2 * j*frameRate << type;
			if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test/480/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/UserTest_Tra1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/UserTest_Tra2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_SS1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_SS2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XT1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XT2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_SSTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_XTTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XTTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_ZLTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_ZL1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_ZL2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_JJ1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_JJ2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_LL1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_LL2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XR1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XR2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_QK1/270/" + ss.str())); // i+...
			else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_QK2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_LLTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_XRTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_JJTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/US_ZXTRA2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Basic1/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Basic2/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Basic3/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Real/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") srcImages.push_back(imread("D:/CCCC/Stop Motion/RealTra/270/" + ss.str()));
			ss.str("");

			if (cut_types.at(i) == 1) break;
			//srcImages.push_back(frames.at(base + j*frameRate));
		}

		cliplabel *clip = new cliplabel(srcImages, base_width, width, height, i, cut_types.at(i), length);
		vector<int> range;
		range.push_back(base);
		range.push_back(scene_cuts.at(i));
		clip->setRange(range);
		clips.push_back(clip);
		
		cliplabel *empty_clip = new cliplabel();
		empty_clip->setFixedSize(width, height);
		empty_clip->setSizeThreshold(width, height);
		if (cut_types[i] == 1 || isDropped.empty() || !isDropped[i/2])
		{
			ui->gridLayout_2->addWidget(clip, 0, i, Qt::AlignLeft);
			ui->gridLayout_3->addWidget(empty_clip, 0, i, Qt::AlignLeft);
			if (cut_types[i] == 2 && !isDropped.empty() && !isDropped[i / 2])
			{
				clip->setAutoCuts(vproc.checkCuts(range));
				cout << i / 2 << endl << endl;;
			}
		}
		else
		{
			clip->setEditedMode(isDeleted);
			ui->gridLayout_3->addWidget(clip, 0, i, Qt::AlignLeft);
			ui->gridLayout_2->addWidget(empty_clip, 0, i, Qt::AlignLeft);
		}

		//connect(clip, SIGNAL(signalEntered(bool)), this, SLOT(slotEntered(bool)));
	}

	//flowfile.close();

	connect(ui->scrollArea_1->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_2->horizontalScrollBar(), SLOT(setValue(int)));
	connect(ui->scrollArea_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_1->horizontalScrollBar(), SLOT(setValue(int)));
	ui->scrollArea_1->setBackgroundRole(QPalette::Dark);
	ui->scrollArea_2->setBackgroundRole(QPalette::Dark);
}

void MainWindow::setCurrentClip(cliplabel *clip)
{
	if (ui->editRadioButton->isChecked())
	{
		current_clip->updatePixmap(fileName);
		QPoint pos = current_clip->pos();
		cliplabel *empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
		int width = current_clip ->getWidth();
		int height = current_clip->getHeight();
		empty_clip->setFixedSize(width, height);
		empty_clip->setSizeThreshold(width, height);
		initFrameSlider();
		ui->editRadioButton->setChecked(false);
	}

	if (current_clip->getEditedMode() == isSelected || current_clip->getEditedMode() == isViewed)
		current_clip->setEditedMode(NotEdited);
	else if (current_clip->getEditedMode() == isSelectedDeleted)
		current_clip->setEditedMode(isDeleted);

	current_clip = clip;
	current_clip_index = clip->getCutIndex();

	if (current_clip->getSize() == 1)
		ui->editRadioButton->setCheckable(false);
	else
		ui->editRadioButton->setCheckable(true);

	if (current_clip->getEditedMode() == NotEdited || current_clip->getEditedMode() == isViewed)
	{
		current_clip->setEditedMode(isSelected);
		//ui->keepRadioButton->setChecked(true);
	}
	else if (current_clip->getEditedMode() == isDeleted)
	{
		current_clip->setEditedMode(isSelectedDeleted);
		//ui->keepRadioButton->setChecked(false);
	}

	/*if (current_clip->getCutType() == 2)
	{
		vector<Point2f> centers = klt();
		drawScatterPlot(centers);
		
	}*/
	int index = (current_clip->getRange()[0] + current_clip->getRange()[1]) / 2;
	refresh(index);
	if (current_clip->pos().x() + current_clip->width() > ui->scrollArea_1->horizontalScrollBar()->sliderPosition() + ui->scrollArea_1->width())
		ui->scrollArea_1->horizontalScrollBar()->setSliderPosition(current_clip->pos().x());
	frame_slider->setValue(current_clip_index);
}

void MainWindow::cutVideo()
{
	/*progressBar = vproc.getProgressBar();
	ui->verticalLayout_2->addWidget(progressBar);
	progressBar->show();*/

	vproc.readBuffers();
	/*if (vproc.getSceneCuts().empty() || vproc.getCutTypes().empty())
	{
		vproc.cut2Scenes();
		vproc.writeBuffers();
	}*/
	//frame_slider->updateParams(vproc.getSceneCuts(), vproc.getCutTypes());
	isCut = true;
	statusBar()->clearMessage();

	/*progressBar->hide();
	ui->verticalLayout_2->removeWidget(progressBar);
	delete progressBar;*/

	visualizeClips();
	current_clip = clips.at(0);
	current_clip_index = 0;
	if (current_clip->getSize() == 1)
		ui->editRadioButton->setCheckable(false);
	else
		ui->editRadioButton->setCheckable(true);
	if (current_clip->getEditedMode() == NotEdited)
	{
		current_clip->setEditedMode(isSelected);
		//ui->keepRadioButton->setChecked(true);
	}
	else
	{
		current_clip->setEditedMode(isSelectedDeleted);
		//ui->keepRadioButton->setChecked(false);
	}

	ui->scrollAreaWidgetContents_1->installEventFilter(this);
	//ui->scrollAreaWidgetContents_1->setAcceptDrops(true);
	ui->scrollAreaWidgetContents_2->installEventFilter(this);
	//ui->scrollAreaWidgetContents_2->setAcceptDrops(true);
}

void MainWindow::initFrameSlider()
{
	frame_slider->clearLabels();
	frame_slider->clearCuts();
	frame_slider->setRange(0, clips.size() - 1);
	frame_slider->setValue(current_clip->getCutIndex());
	frame_slider->setTickPosition(QSlider::TicksAbove);
	frame_slider->setTickInterval(1);
	frame_slider->setEditMode(false);
	connect(frame_slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

	vector<int> *labeledValues = frame_slider->getLabeledIndices();
	bool empty = current_clip->getCuts().empty();
	if (labeledValues->empty() && !empty)
		labeledValues->push_back(current_clip_index);
	else if (!labeledValues->empty())
	{
		for (int i = 0; i < labeledValues->size(); i++)
		{
			if (labeledValues->at(i) == current_clip_index && empty)
			{
				labeledValues->at(i) = -1;
				return;
			}
			else if (labeledValues->at(i) == current_clip_index && !empty)
				return;
		}
		if (!empty)
			labeledValues->push_back(current_clip_index);
	}
}

void MainWindow::drawScatterPlot()
{
	
	ifstream centerfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") centerfile.open("D:/CCCC/Stop Motion/Test7/points1.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") centerfile.open("D:/CCCC/Stop Motion/Test8/points1.txt");

	if (centerfile.is_open())
	{
		vector<int> range = current_clip->getRange();
		cout << range[0] << " " << range[1] << endl;

		float x, y;
		float xmin = 500;
		//float ymin = 300;
		float xmax = -1;
		//float ymax = -1;
		int i = 0;
		vector<Point2f> points;
		
		while (centerfile >> x >> y)
		{
			if (i >= range[0] && i <= range[1])
			{
				if (x != 0 || y != 0)
				{
					if (x < xmin) xmin = x;
					if (x > xmax) xmax = x;
					//if (y < ymin) ymin = y;
					//if (y > ymax) ymax = y;
					points.push_back(Point2f(x, y));
				}
			}
			i++;
		}

		Mat plot(270, (xmax - xmin) * 15 / 2, CV_8UC3, Scalar(255, 255, 255));
		//Mat plot((ymax-ymin)*15/2, (xmax-xmin)*15/2, CV_8UC3, Scalar(255, 255, 255));
		for (size_t i = 0; i < points.size(); i++)
		{
			circle(plot, Point2f((points[i].x - xmin + (xmax - xmin) / 4) * 5, points[i].y), 1, Scalar(0, 0, 255), -1, 8);
				//(points[i].y-ymin+(ymax-ymin)/4)*5), 1, Scalar(0, 0, 255), -1, 8);
		}

		centerfile.close();
		imshow("Plot", plot);
	}
	else cout << "Unable to open file" << endl;
}

void MainWindow::drawScatterPlot(vector<Point2f> points)
{
	float x, y;
	float xmin = 500;
	//float ymin = 300;
	float xmax = -1;
	//float ymax = -1;
	for (size_t i = 0; i < points.size(); i++)
	{
		x = points[i].x;
		y = points[i].y;
		if (x != 0 || y != 0)
		{
			if (x < xmin) xmin = x;
			if (x > xmax) xmax = x;
			//if (y < ymin) ymin = y;
			//if (y > ymax) ymax = y;
		}
	}

	Mat plot(270, (xmax - xmin) * 15 / 2, CV_8UC3, Scalar(255, 255, 255));
	//Mat plot((ymax-ymin)*15/2, (xmax-xmin)*15/2, CV_8UC3, Scalar(255, 255, 255));
	for (size_t i = 0; i < points.size(); i++)
	{
		circle(plot, Point2f((points[i].x - xmin + (xmax - xmin) / 4) * 5, points[i].y), 1, Scalar(0, 0, 255), -1, 8);
		//(points[i].y-ymin+(ymax-ymin)/4)*5), 1, Scalar(0, 0, 255), -1, 8);
	}
	imshow("Plot", plot);
}

vector<Point2f> MainWindow::klt()
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
	vector<Point2f> centers;
	//cv::initModule_nonfree();//if use SIFT or SURF
	//Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");

	int start = current_clip->getRange().at(0);
	int end = current_clip->getRange().at(1);
	bool drifted = false;
	for (int i = start; i <= end; i++)
	{
		Mat frame;
		ss << i << type;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
		ss.str("");

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		if (needToInit && !drifted)
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
			drifted = false;//int num_drift_pts = 0;

			if (prevGray.empty())
				gray.copyTo(prevGray);
			calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);

			size_t i, k;
			for (i = k = 0; i < points[1].size(); i++)
			{
				if (!status[i])
					continue;

				drifted = false;
				points[1][k++] = points[1][i];
				float flowx = abs(points[0][i].x - points[1][i].x);
				float flowy = abs(points[0][i].y - points[1][i].y);
				if (flowx > 20 || flowy > 20)
				{
					drifted = true;//circle(image, points[1][i], 3, Scalar(255, 255, 0), -1, 8);
					break;//num_drift_pts++;
				}
				else if ((flowx < 5 && flowx > 1) || (flowy < 9 && flowy > 5))
				{
					line(image, points[0][i], points[1][i], Scalar(255, 255, 255));
					circle(image, points[1][i], 3, Scalar(255, 0, 255), -1, 8);
				}
				else
					circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
			}
			points[1].resize(k);
			if (drifted)//if (num_drift_pts >= 5)
			{
				goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 1, 0.04);//detector->detect(image, keypoints);
				cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);
				for (size_t i = 0; i < points[1].size(); i++)
					circle(image, points[1][i], 3, Scalar(0, 255, 255), -1, 8);
			}
		}

		Scalar mean = cv::mean(points[1]);
		centers.push_back(Point2f(mean[0], mean[1]));
		circle(image, Point2f(mean[0], mean[1]), 3, Scalar(0, 0, 255), -1, 8);

		if ((i + 1) % 5 == 0)
			needToInit = true;
		else needToInit = false;

		imshow("LK", image);
		if (waitKey(delay) == 27) break;
		if (waitKey(delay) == 32) waitKey(0);

		std::swap(points[1], points[0]);
		cv::swap(prevGray, gray);
	}
	return centers;
}

int MainWindow::round(double r)
{
	return (r > 0.0) ? int(floor(r + 0.5)) : int(ceil(r - 0.5));
}

void MainWindow::writeLogFile()
{
	ofstream logfile("D:/CCCC/Stop Motion/US_QK1/logs.txt");

	if (logfile.is_open())
	{
		for (int i = 0; i < logger.size(); i++)
			logfile << logger[i] << endl;
		logfile.close();
	}
	else cout << "Unable to open file" << endl;
}

/*void MainWindow::resizeEvent(QResizeEvent* ev)
{
    resize_count++;
	int current_width, current_height;
    if (resize_count > 0)
	{
		if (current_frame != NULL) //if (current_frame->parent() != 0)
		{
			current_width = current_frame->width();
			current_height = current_frame->height();
		}
    }

	QMainWindow::resizeEvent(ev);

    if (resize_count > 0)
    {
		if (current_frame != NULL) //if (current_frame->parent() != 0)
		{
			int new_width = floor(this->width()*current_width / double(window_current_width));
			int new_height = floor(this->height()*current_height / double(window_current_height));
			current_frame->setFixedSize(new_width, new_height);			
		}
    }

    window_current_width = this->width();
    window_current_height = this->height() - ui->menuBar->height() - ui->mainToolBar->height();
}*/

/*void MainWindow::setClickRange(vector<int> indices)
{
	if (!clickRange.empty()) clickRange.clear();
	if (!movingRange.empty()) movingRange.clear();
		
	int index;
	vector<int> scene_cuts = vproc.getSceneCuts();
	for (int i = 0; i < indices.size(); i++)
	{
		index = indices.at(i);
		if (index == 0) clickRange.push_back(0);
		else clickRange.push_back(scene_cuts.at(index-1) + 1);
		clickRange.push_back(scene_cuts.at(index));
	}
}*/

void MainWindow::on_playClipButton_clicked()
{
	double time;
	if (isCounting)
		time = (double)(clock() - start) / CLOCKS_PER_SEC;
	
	if (myPlayer->isStopped())
	{
		myPlayer->playVideo(current_clip_index);
		ui->playClipButton->setIcon(QIcon(":/Images/icons/pause_24.png"));
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  playClipButton");
	}
	else
	{
		myPlayer->stopVideo();
		ui->playClipButton->setIcon(QIcon(":/Images/icons/play_24.png"));
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  pauseClipButton");
	}
	/*vector<int> cutRanges = current_clip->getCuts();
	if (cutRanges.empty())
	{
		int start = current_clip->getRange().at(0);
		int end = current_clip->getRange().at(1);

		if (current_clip->getCutType() == 2)
		{
			int delay = 500 / vproc.getFrameRate();//delay = 1000 / frame_rate;
			for (int j = start; j <= end; j++)
			{
				refresh(j);
				Sleep(delay);
			}
		}
		else
			refresh((start + end) / 2);
	}
	else
	{
		int start, end;
		int size = cutRanges.size();
		int delay = 500 / vproc.getFrameRate();

		for (int i = 0; i < size; i += 2)
		{
			start = cutRanges.at(i);
			end = cutRanges.at(i + 1);
			for (int j = start; j <= end; j++)
			{
				refresh(j);
				Sleep(delay);
			}
		}
	}*/

	/*if (frame_slider->parent() == 0)
    {
		child = ui->verticalLayout_2->takeAt(0);
		child->widget()->setVisible(0);
		ui->verticalLayout_2->removeWidget(child->widget());
		delete child;

		if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame_slider->setRange(0, 6283); //frame_slider->setRange(0, mediaplayer_1->duration());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame_slider->setRange(0, 4716);
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame_slider->setRange(0, 2348);
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame_slider->setRange(0, 9321);
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame_slider->setRange(0, 8449);
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame_slider->setRange(0, 5457);
		frame_slider->setValue(0);
		frame_slider->setTickPosition(QSlider::TicksAbove);
		frame_slider->setTickInterval(30);//frame_slider->setTickInterval(500);
		connect(frame_slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
		ui->verticalLayout_2->addWidget(frame_slider);
    }*/
}

void MainWindow::on_preButton_clicked()
{
	if (isCounting)
	{
		double time = (double)(clock() - start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(time).toStdString() + "  preButton");
	}
	if (current_clip_index > 0)
	{
		int i = current_clip_index - 1;
		while (i >= 0 && clips[i]->getEditedMode() == isDeleted)
			i--;
		if (i != -1)
			setCurrentClip(clips.at(i));
	}
}

void MainWindow::on_nextButton_clicked()
{
	if (isCounting)
	{
		double time = (double)(clock()-start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(time).toStdString() + "  nextButton");
	}
	int size = clips.size();
	if (current_clip_index < size - 1)
	{
		int i = current_clip_index + 1;
		while (i < size && clips[i]->getEditedMode() == isDeleted)
			i++;
		if (i != size)
			setCurrentClip(clips.at(i));
	}
}

/*void MainWindow::on_pauseButton_clicked()
{
    //mediaplayer_1->pause();
	if (!myPlayer->isStopped())
		myPlayer->stopVideo();
}*/

void MainWindow::on_playTrackButton_clicked()
{
	double time;
	if (isCounting)
		time = (double)(clock() - start) / CLOCKS_PER_SEC;
	if (myPlayer->isStopped())
	{
		myPlayer->playVideo(current_clip_index, false);
		ui->playTrackButton->setIcon(QIcon(QPixmap(":/Images/icons/pause_24.png")));
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  playTrackButton");
	}
	else
	{
		myPlayer->stopVideo();
		ui->playTrackButton->setIcon(QIcon(QPixmap(":/Images/icons/view-track.png")));
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  pauseTrackButton");
	}

	/*int start = -1;
	int end = -1;
	int delay = -1;
	int frameRate = vproc.getFrameRate();
	int size = clips.size();
	cliplabel *item;

	for (int i = frame_slider->value() % (size - 1); i < size; i++)
	{
		item = clips.at(i);
		isEdited orginMode = item->getEditedMode();
		if (item->getCutType() != -1 && orginMode != isDeleted && orginMode != isSelectedDeleted)
		{
			item->setEditedMode(isViewed);
			//ui->scrollArea_1->horizontalScrollBar()->setSliderPosition(item->pos().x());
			//frame_slider->setValue(i);
			start = item->getRange().at(0);
			end = item->getRange().at(1);
			vector<int> cutRanges = item->getCuts();
			setCurrentClip(item);

			if (!cutRanges.empty())
			{
				int size = cutRanges.size();
				delay = 500 / vproc.getFrameRate();
				for (int j = 0; j < size; j += 2)
				{
					start = cutRanges.at(j);
					end = cutRanges.at(j + 1);
					for (int k = start; k <= end; k++)
					{
						refresh(k);
						Sleep(delay);
					}
				}
			}
			else if (item->getCutType() == 2)
			{
				delay = 500 / frameRate;
				int current_position = ui->scrollArea_1->horizontalScrollBar()->sliderPosition();
				int base_width = current_clip->getBaseWidth();
				int clip_width = current_clip->width();
				int scroll_width = ui->scrollArea_1->width();
				for (int j = start; j <= end; j++)
				{
					if (clip_width > scroll_width && current_position + scroll_width <= ui->scrollAreaWidgetContents_1->width()
						&& j > 0 && j % (2 * frameRate) == 0)
					{
						cout << j << endl;
						ui->scrollArea_1->horizontalScrollBar()->setSliderPosition(current_position + base_width);
						current_position += base_width;
					}
					refresh(j);
					if (GetAsyncKeyState(0x53))
					{
						setCurrentClip(item);
						return;
					}
					Sleep(delay);
				}
			}
			else
			{
				delay = 500;
				refresh((start + end) / 2);
				if (GetAsyncKeyState(0x53))
				{
					setCurrentClip(item);
					return;
				}
				Sleep(delay);
			}
			item->setEditedMode(orginMode);
		}
	}*/
}

void MainWindow::seek(int index)
{
	if (ui->editRadioButton->isChecked())
		refresh(index);
	else
		setCurrentClip(clips.at(index));

	//mediaplayer_1->setPosition(seconds);//mediaplayer_1->setPosition(seconds * 1000);
}

void MainWindow::slotEntered(bool isEntered)
{
	entered = isEntered;
}

void MainWindow::on_actionLoad_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Video Files(*.mp4 *.avi *.mov *.jpg);;All files (*.*)" ));
    if (fileName.isEmpty())
        return;
	
	string stdFileName = fileName.toStdString();
	vproc.readVideo(stdFileName);
	cutVideo();
	ui->frameLabel->setStyleSheet("background-color: rgb(0, 0, 0); image: url(D:/CCCC/Stop Motion/Videos/preview.png);");
	initFrameSlider();
	myPlayer = new player();
	myPlayer->loadVideo(stdFileName, vproc.getFrameRate(), clips);
	QObject::connect(myPlayer, SIGNAL(display(int)), this, SLOT(updatePlayer(int)));
	QObject::connect(myPlayer, SIGNAL(setCurrentClipIndex(int)), this, SLOT(updateCurrentClip(int)));
	QObject::connect(myPlayer, SIGNAL(setPlayButtonIcon(bool)), this, SLOT(updatePlayButtonIcon(bool)));
}

/*void MainWindow::on_actionSelect_triggered()
{
	if (!ui->actionSelect->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionSelect->isChecked())
	{
		selectedClips.clear();
		seletedPos.clear();
		action = SelectClip;
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionView_triggered()
{
	if (!ui->actionView->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionView->isChecked() && !selectedClips.empty() && !seletedPos.empty())
	{
		//ui->actionSelect->setChecked(false);
		if (selectedClips.size() == 1)
		{
			cliplabel *item = selectedClips.at(0);
			//setClickRange(item->getGroupIndices());
			if (!clickRange.empty()) clickRange.clear();
			if (!movingRange.empty()) movingRange.clear();
			clickRange = item->getRange();
			movingRange.push_back(item->getCutType());
			action = ViewClip;
			playRange();
			item->setEditedMode(NotEdited);
		}
		else
		{
			QString tip = "Please select one and only one clip.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedClips.size(); i++)
			{
				cliplabel *item = selectedClips.at(i);
				item->setEditedMode(NotEdited);
			}
		}
		ui->actionView->setChecked(false);
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionSwap_triggered()
{
	if (!ui->actionSwap->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionSwap->isChecked())
		action = MoveClip;
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionReverse_triggered()
{
	if (!ui->actionReverse->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionReverse->isChecked() && !selectedClips.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		if (selectedClips.size() == 1)
		{
			cliplabel *item = selectedClips.at(0);
			if (!clickRange.empty()) clickRange.clear();
			if (!movingRange.empty()) movingRange.clear();
			clickRange = item->getRange();
			movingRange.push_back(item->getCutType());
			action = ReverseClip;
			playRange();
		}
		else
		{
			QString tip = "Please select one and only one clip.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedClips.size(); i++)
			{
				cliplabel *item = selectedClips.at(i);
				item->setEditedMode(NotEdited);
			}
		}
		ui->actionReverse->setChecked(false);
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionCast_triggered()
{
	if (!ui->actionCast->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionCast->isChecked() && !selectedClips.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		for (int i = 0; i < selectedClips.size(); i++)
		{
			cliplabel *item = selectedClips.at(i);
			QPoint pos = seletedPos.at(i);
			cliplabel *cast2item;
			if (item->getCutType() == 1)
				cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
			else
				cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(pos));
			cast2item->cast(item);
			item->setEditedMode(isCasted);
		}
		action = CastClip;
		ui->actionCast->setChecked(false);
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionZoomIn_triggered()
{
	//int currentSliderWidth = frame_slider->width();
	//frame_slider->setFixedWidth(2*currentSliderWidth);

	QLayoutItem *child_1;
	QLayoutItem *child_2;
	int count = 0;
	while ((child_1 = ui->gridLayout_2->itemAt(count)) != 0 && (child_2 = ui->gridLayout_3->itemAt(count)) != 0)
	{
		cliplabel* item_1 = static_cast<cliplabel*>(child_1->widget());
		cliplabel* item_2 = static_cast<cliplabel*>(child_2->widget());
		item_1->zoomIn();
		item_2->zoomIn();
		count++;
	}
	for(int i = 0; i < addedTrackCount && !addedTrack.at(i)->getIsDeleted(); i++)
	{
		count = 0;
		QGridLayout *layout = addedTrack.at(i)->getLayout();
		while ((child_1 = layout->itemAt(count)) != 0)
		{
			cliplabel* item = static_cast<cliplabel*>(child_1->widget());
			item->zoomIn();
			count++;
		}
	}
}*/

/*void MainWindow::on_actionZoomOut_triggered()
{
	//int current_width = frame_slider->width();
	//frame_slider->setFixedWidth(floor(0.5 * current_width));

	QLayoutItem *child_1;
	QLayoutItem *child_2;
	int count = 0;
	while ((child_1 = ui->gridLayout_2->itemAt(count)) != 0 && (child_2 = ui->gridLayout_3->itemAt(count)) != 0)
	{
		cliplabel* item_1 = static_cast<cliplabel*>(child_1->widget());
		cliplabel* item_2 = static_cast<cliplabel*>(child_2->widget());
		item_1->zoomOut();
		item_2->zoomOut();
		count++;
	}
	for (int i = 0; i < addedTrackCount && !addedTrack.at(i)->getIsDeleted(); i++)
	{
		count = 0;
		QGridLayout *layout = addedTrack.at(i)->getLayout();
		while ((child_1 = layout->itemAt(count)) != 0)
		{
			cliplabel* item = static_cast<cliplabel*>(child_1->widget());
			item->zoomOut();
			count++;
		}
	}
}*/

/*void MainWindow::on_actionSelectTrack_triggered()
{
	if (!ui->actionSelectTrack->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionSelectTrack->isChecked())
	{
		selectedTrack.clear();
		action = SelectTrack;
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionAddTrack_triggered()
{
	if (!ui->actionAddTrack->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionAddTrack->isChecked())
	{
		myscrollarea *scroll = new myscrollarea();
		ui->verticalLayout->addWidget(scroll);
		scroll->getCentralWidget()->installEventFilter(this);
		addedTrackCount++;
		addedTrack.push_back(scroll);
		ui->actionAddTrack->setChecked(false);
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionDeleteTrack_triggered()
{
	if (!ui->actionDeleteTrack->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionDeleteTrack->isChecked() && !selectedTrack.empty())
	{
		ui->actionSelectTrack->setChecked(false);
		for (int i = 0; i < selectedTrack.size(); i++)
		{
			selectedTrack.at(i)->setFrameStyle(QFrame::NoFrame);
			if (selectedTrack.at(i) == ui->scrollArea_1 || selectedTrack.at(i) == ui->scrollArea_2)
			{
				statusBar()->showMessage("This track is not deletable.");
				continue;
			}
			myscrollarea *scroll = static_cast<myscrollarea*>(selectedTrack.at(i));
			scroll->getCentralWidget()->removeEventFilter(this);
			scroll->setIsDeleted(true);
			scroll->hide();
		}
		ui->actionDeleteTrack->setChecked(false);
	}
	else
		action = NullOperation;
}*/

/*void MainWindow::on_actionViewTrack_triggered()
{
	if (!ui->actionViewTrack->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionViewTrack->isChecked() && !selectedTrack.empty())
	{
		ui->actionSelectTrack->setChecked(false);
		if (selectedTrack.size() == 1)
		{
			int count = 0;
			QScrollArea *scroll = selectedTrack.at(0);
			//myscrollarea *my_scroll;
			QLayoutItem *child;
			QGridLayout *layout;
			if (!clickRange.empty()) clickRange.clear();
			if (!movingRange.empty()) movingRange.clear();

			if (scroll == ui->scrollArea_1) layout = ui->gridLayout_2;
			else if (scroll == ui->scrollArea_2) layout = ui->gridLayout_3;
			else
			{
				for (int i = 0; i < addedTrackCount; i++)
				{
					if (scroll == addedTrack.at(i))
					{
						my_scroll = static_cast<myscrollarea*>(scroll);
						layout = my_scroll->getLayout();
						break;
					}
				}
			}
			while ((child = layout->itemAt(count)) != 0)
			{
				cliplabel* item = static_cast<cliplabel*>(child->widget());
				if (item->getCutType() != -1 && item->getEditedMode() != isMoved && item->getEditedMode() != isDeleted && item->getEditedMode() != isSelectedDeleted)
				{
					clickRange.push_back(item->getRange().at(0));
					clickRange.push_back(item->getRange().at(1));
					movingRange.push_back(item->getCutType());
				}
				count++;
			}

			//setClickRange(track_indices);
			scroll->setFrameStyle(QFrame::NoFrame);
			action = ViewTrack;
			playRange();
		}
		else if (selectedTrack.size() == 2)
		{
			if (!clickRange.empty()) clickRange.clear();
			if (!movingRange.empty()) movingRange.clear();

			for (int i = 0; i < clips.size(); i++)
			{
				cliplabel* item = clips.at(i);
				if (item->getCutType() != -1 && item->getEditedMode() != isMoved && item->getEditedMode() != isDeleted && item->getEditedMode() != isCasted)
				{
					for (int i = 0; i < item->getOriginRange().size(); i++)
						clickRange.push_back(item->getOriginRange().at(i));
					movingRange.push_back(item->getOriginMoving());
				}
			}

			//setClickRange(track_indices);
			selectedTrack.at(0)->setFrameStyle(QFrame::NoFrame);
			selectedTrack.at(1)->setFrameStyle(QFrame::NoFrame);
			action = ViewTrack;
			playRange();
		}
		else
		{
			QString tip = "Please select one and only one track.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedTrack.size(); i++)
				selectedTrack.at(i)->setFrameStyle(QFrame::NoFrame);
		}
		ui->actionViewTrack->setChecked(false);
	}
	else
		action = NullOperation;
}*/

bool MainWindow::eventFilter(QObject *widget, QEvent *event)
{
    if (widget == frame_slider)
	{
		/*if (event->type() == QEvent::MouseMove)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			QString tip = "position: (" + QString::number(m->x()) + ", " + QString::number(m->y()) + ")";
			statusBar()->showMessage(tip);
			return true;
		}*/
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			//clickRange = vproc.getRange(m->x(), frame_slider->width());
			if (m->button() == Qt::RightButton)
			{
				labelIndex = round(m->x() * (frame_slider->maximum() - frame_slider->minimum()) / double(frame_slider->width()) + frame_slider->minimum());
				frame_slider->setContextMenuPolicy(Qt::CustomContextMenu);
				connect(frame_slider, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu()));
				if (isCounting)
				{
					double time = (double)(clock() - start) / CLOCKS_PER_SEC;
					logger.push_back(QString::number(time).toStdString() + "  sliderContextMenu");
				}
				return true;
			}
			else
				return false;
		}
		/*else if (event->type() == QEvent::Leave)
		{
			statusBar()->clearMessage();
			return true;
		}*/
		else 
			return false;
	}
	else if (widget == ui->scrollAreaWidgetContents_1 || widget == ui->scrollAreaWidgetContents_2) //&& entered == true) //|| addedTrackCount != 0)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			if (m->button() == Qt::LeftButton)
			{
				/*if (action == SelectTrack)
				{
				if (widget == ui->scrollAreaWidgetContents_1)
				{
				ui->scrollArea_1->setFrameStyle(QFrame::Box);
				selectedTrack.push_back(ui->scrollArea_1);
				}

				else if (widget == ui->scrollAreaWidgetContents_2)
				{
				ui->scrollArea_2->setFrameStyle(QFrame::Box);
				selectedTrack.push_back(ui->scrollArea_2);
				}

				else if (addedTrackCount != 0)
				{
				for (int i = 0; i < addedTrackCount; i++)
				{
				if (widget == addedTrack.at(i)->getCentralWidget())
				{
				addedTrack.at(i)->setFrameStyle(QFrame::Box);
				selectedTrack.push_back(addedTrack.at(i));
				return true;
				}
				}
				}
				}*/

				cliplabel *item;
				if (widget == ui->scrollAreaWidgetContents_1)
					item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(m->pos()));
				else if (widget == ui->scrollAreaWidgetContents_2)
					item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(m->pos()));
				/*else
				{
				QWidget *contents;
				for (int i = 0; i < addedTrackCount; i++)
				{
				contents = addedTrack.at(i)->getCentralWidget();
				if (widget == contents && contents->childAt(m->pos()) != 0)
				{
				item = static_cast<cliplabel*>(contents->childAt(m->pos()));
				break;
				}
				}
				}*/
				if (item->getCutType() == -1)
					return false;
				else 
				{
					setCurrentClip(item);
					if (isCounting)
					{
						double time = (double)(clock() - start) / CLOCKS_PER_SEC;
						logger.push_back(QString::number(time).toStdString() + "  clickOnClip " + QString::number(current_clip_index).toStdString());
					}
					QPixmap pixmap = *item->pixmap();
					QMimeData *mimeData = new QMimeData;
					QByteArray exData;
					QDataStream dataStream(&exData, QIODevice::WriteOnly);
					dataStream << pixmap;
					mimeData->setData("application/x-dnditemdata", exData);
					mimeData->setText(tr("Drag and Drop"));
					QDrag *drag;
					if (widget == ui->scrollAreaWidgetContents_1)
					{
						drag = new QDrag(ui->scrollAreaWidgetContents_1);
						current_empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(current_clip->pos()));
						current_empty_clip->setAcceptDrops(true);
						current_empty_clip->installEventFilter(this);
					}
					else if (widget == ui->scrollAreaWidgetContents_2)
					{
						drag = new QDrag(ui->scrollAreaWidgetContents_2);
						current_empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(current_clip->pos()));
						current_empty_clip->setAcceptDrops(true);
						current_empty_clip->installEventFilter(this);
					}
					//else drag = new QDrag(addedTrack.at(track_index)->getCentralWidget());
					drag->setMimeData(mimeData);
					drag->setPixmap(pixmap.scaledToHeight(50));
					//drag->setHotSpot(m->pos() - item->pos());
					//item->hide();
					if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
						item->show();
					else
						event->ignore();
					return true;
				}

				//selectedClips.push_back(item);

				/*else if (action == MoveClip)
				{
				cliplabel *item;
				//int track_index = -1;
				if (widget == ui->scrollAreaWidgetContents_1)
				{
				item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(m->pos()));

				int counter = item->getCutIndex()/2;
				if (!clickRange.empty()) clickRange.clear(); //vector<Mat> canFrames;
				if (!movingRange.empty()) movingRange.clear();
				vector<int>::iterator it_1;
				vector<bool>::iterator it_2;
				for (int i = 0; i < item->getOriginRange().size(); i++)
				clickRange.push_back(item->getOriginRange().at(i));
				movingRange.push_back(item->getOriginMoving());
				stringstream ss;
				string type = ".jpg";
				ss << (item->getOriginRange().at(0) + item->getOriginRange().at(1)) / 2 << type;
				Mat selectedFrame, refFrame;
				if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") refFrame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") refFrame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") refFrame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") refFrame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
				selectedFrame = refFrame;
				cout << ss.str() << endl;
				ss.str("");
				//canFrames.push_back(refFrame);

				myscrollarea *scroll = new myscrollarea();
				ui->verticalLayout->addWidget(scroll);
				scroll->getCentralWidget()->installEventFilter(this);
				addedTrackCount++;
				addedTrack.push_back(scroll);

				while (counter != 0)
				{
				counter--;
				cliplabel *canClip = stableClip.at(counter);
				if (canClip->getEditedMode() == isDeleted || canClip->getEditedMode() == isCasted || canClip->getEditedMode() == isMoved)
				continue;

				ss << (canClip->getOriginRange().at(0)+canClip->getOriginRange().at(1))/2 << type;
				Mat canFrame;
				if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") canFrame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") canFrame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") canFrame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") canFrame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
				cout << ss.str() << endl;
				ss.str("");
				if (vproc.matchFeatures(refFrame, canFrame) == 0) break;
				else
				{
				canClip->setEditedMode(isSelected);

				if (vproc.matchFeatures(refFrame, canFrame) == -1)
				{
				cliplabel *canClip_1 = movingClip.at(counter);
				canClip_1->setEditedMode(isSelected);
				cliplabel *move2item_1 = new cliplabel(canClip_1->getSrcImages(), canClip_1->width(), canClip_1->height(), canClip_1->getCutIndex(), addedTrackCount + 2, canClip_1->getDisplayScale());
				move2item_1->setOriginRange(canClip_1->getOriginRange());
				move2item_1->setGroupRange(canClip_1->getGroupRange());
				move2item_1->setOriginMoving(canClip_1->getOriginMoving());
				move2item_1->setGroupMovingRange(canClip_1->getGroupMovingRange());
				addedTrack.at(addedTrackCount - 1)->getLayout()->addWidget(move2item_1, 0, 0, Qt::AlignLeft);
				addedTrack.at(addedTrackCount - 1)->addChildrenCount();

				for (int i = canClip_1->getOriginRange().size() - 1; i >= 0; i--)
				{
				it_1 = clickRange.begin();
				clickRange.insert(it_1, canClip_1->getOriginRange().at(i));
				}
				it_2 = movingRange.begin();
				movingRange.insert(it_2, canClip_1->getOriginMoving());
				}

				cliplabel *move2item = new cliplabel(canClip->getSrcImages(), canClip->width(), canClip->height(), canClip->getCutIndex(), addedTrackCount + 2, canClip->getDisplayScale());
				move2item->setOriginRange(canClip->getOriginRange());
				move2item->setGroupRange(canClip->getGroupRange());
				move2item->setOriginMoving(canClip->getOriginMoving());
				move2item->setGroupMovingRange(canClip->getGroupMovingRange());
				addedTrack.at(addedTrackCount - 1)->getLayout()->addWidget(move2item, 0, 0, Qt::AlignLeft);
				addedTrack.at(addedTrackCount - 1)->addChildrenCount();

				for (int i = canClip->getOriginRange().size()-1; i >= 0; i--)
				{
				it_1 = clickRange.begin();
				clickRange.insert(it_1, canClip->getOriginRange().at(i));
				}
				it_2 = movingRange.begin();
				movingRange.insert(it_2, canClip->getOriginMoving());

				//it = canFrames.begin();
				//canFrames.insert(it, canFrame);
				refFrame = canFrame;
				}
				}

				counter = item->getCutIndex() / 2;
				refFrame = selectedFrame; //refFrame = canFrames.at(canFrames.size()-1);
				while (counter != stableClip.size()-1)
				{
				counter++;
				cliplabel *canClip = stableClip.at(counter);
				if (canClip->getEditedMode() == isDeleted || canClip->getEditedMode() == isCasted || canClip->getEditedMode() == isMoved)
				continue;

				ss << (canClip->getOriginRange().at(0)+canClip->getOriginRange().at(1))/2 << type;
				Mat canFrame;
				if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") canFrame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") canFrame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") canFrame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") canFrame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
				cout << ss.str() << endl;
				ss.str("");
				if (vproc.matchFeatures(refFrame, canFrame) == 0) break;
				else
				{
				canClip->setEditedMode(isSelected);

				if (vproc.matchFeatures(refFrame, canFrame) == -1)
				{
				cliplabel *canClip_1 = movingClip.at(counter-1);
				canClip_1->setEditedMode(isSelected);
				cliplabel *move2item_1 = new cliplabel(canClip_1->getSrcImages(), canClip_1->width(), canClip_1->height(), canClip_1->getCutIndex(), addedTrackCount + 2, canClip_1->getDisplayScale());
				move2item_1->setOriginRange(canClip_1->getOriginRange());
				move2item_1->setGroupRange(canClip_1->getGroupRange());
				move2item_1->setOriginMoving(canClip_1->getOriginMoving());
				move2item_1->setGroupMovingRange(canClip_1->getGroupMovingRange());
				addedTrack.at(addedTrackCount - 1)->getLayout()->addWidget(move2item_1, 0, addedTrack.at(addedTrackCount - 1)->getChildrenCount(), Qt::AlignLeft);
				addedTrack.at(addedTrackCount - 1)->addChildrenCount();

				for (int i = 0; i < canClip_1->getOriginRange().size(); i++)
				clickRange.push_back(canClip_1->getOriginRange().at(i));
				movingRange.push_back(canClip_1->getOriginMoving());
				}

				cliplabel *move2item = new cliplabel(canClip->getSrcImages(), canClip->width(), canClip->height(), canClip->getCutIndex(), addedTrackCount + 2, canClip->getDisplayScale());
				move2item->setOriginRange(canClip->getOriginRange());
				move2item->setGroupRange(canClip->getGroupRange());
				move2item->setOriginMoving(canClip->getOriginMoving());
				move2item->setGroupMovingRange(canClip->getGroupMovingRange());
				addedTrack.at(addedTrackCount-1)->getLayout()->addWidget(move2item, 0, addedTrack.at(addedTrackCount-1)->getChildrenCount(), Qt::AlignLeft);
				addedTrack.at(addedTrackCount-1)->addChildrenCount();

				for (int i = 0; i < canClip->getOriginRange().size(); i++)
				clickRange.push_back(canClip->getOriginRange().at(i));
				movingRange.push_back(canClip->getOriginMoving());
				//canFrames.push_back(canFrame);
				refFrame = canFrame;
				}
				}

				//for (int i = 0; i < canFrames.size(); i++)
				//{
				//imshow("Candidate Frames", canFrames.at(i));
				//waitKey(250);
				//}
				vproc.writeVideo(clickRange, movingRange, ViewTrack);
				}
				else if (widget == ui->scrollAreaWidgetContents_2)
				item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(m->pos()));
				else
				{
				QWidget *contents;
				for (int i = 0; i < addedTrackCount; i++)
				{
				contents = addedTrack.at(i)->getCentralWidget();
				if (widget == contents && contents->childAt(m->pos()) != 0)
				{
				item = static_cast<cliplabel*>(contents->childAt(m->pos()));
				track_index = i;
				break;
				}
				}
				}

				QPixmap pixmap = *item->pixmap();
				QMimeData *mimeData = new QMimeData;
				QByteArray exData;
				QDataStream dataStream(&exData, QIODevice::WriteOnly);
				dataStream << pixmap << item->getCutType() << m->pos() << QPoint(m->pos() - item->pos());
				mimeData->setData("application/x-dnditemdata", exData);
				mimeData->setText(tr("Drag and Drop"));
				QDrag *drag;
				if (widget == ui->scrollAreaWidgetContents_1)
				drag = new QDrag(ui->scrollAreaWidgetContents_1);
				else if (widget == ui->scrollAreaWidgetContents_2)
				drag = new QDrag(ui->scrollAreaWidgetContents_2);
				//else drag = new QDrag(addedTrack.at(track_index)->getCentralWidget());
				drag->setMimeData(mimeData);
				drag->setPixmap(pixmap.scaledToHeight(50));
				drag->setHotSpot(m->pos() - item->pos());
				//item->hide();
				if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
				item->close();
				else
				item->show();
				}*/
			}
			else
				return false;
		}
		/*else if (event->type() == QEvent::MouseMove)
		{
			cliplabel *item = current_clip;
			QPixmap pixmap = *item->pixmap();
			QMimeData *mimeData = new QMimeData;
			QByteArray exData;
			QDataStream dataStream(&exData, QIODevice::WriteOnly);
			dataStream << pixmap;
			mimeData->setData("application/x-dnditemdata", exData);
			mimeData->setText(tr("Drag and Drop"));
			QDrag *drag;
			if (widget == ui->scrollAreaWidgetContents_1)
			{
				drag = new QDrag(ui->scrollAreaWidgetContents_1);
				current_empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(current_clip->pos()));
				current_empty_clip->setAcceptDrops(true);
				current_empty_clip->installEventFilter(this);
				//ui->scrollAreaWidgetContents_1->setAcceptDrops(false);
				//ui->scrollAreaWidgetContents_2->setAcceptDrops(true);
			}
			else if (widget == ui->scrollAreaWidgetContents_2)
			{
				drag = new QDrag(ui->scrollAreaWidgetContents_2);
				current_empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(current_clip->pos()));
				current_empty_clip->setAcceptDrops(true);
				current_empty_clip->installEventFilter(this);
				//ui->scrollAreaWidgetContents_1->setAcceptDrops(true);
				//ui->scrollAreaWidgetContents_2->setAcceptDrops(false);
			}
			//else drag = new QDrag(addedTrack.at(track_index)->getCentralWidget());
			drag->setMimeData(mimeData);
			drag->setPixmap(pixmap.scaledToHeight(50));
			//drag->setHotSpot(m->pos() - item->pos());
			//item->hide();
			if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
				item->show();
			else
				event->ignore();
			return true;
		}*/
		else
			return false;
	}
	else if (widget == current_empty_clip)
	{	
		if (event->type() == QEvent::DragEnter)
		{
			QDragEnterEvent *drag = (QDragEnterEvent*)event;
			if (drag->mimeData()->hasFormat("application/x-dnditemdata"))
			{
				//drag->setDropAction(Qt::MoveAction);
				drag->accept();
			}
			else
			{
				drag->ignore();
			}
			return true;
		}
		else if (event->type() == QEvent::DragMove)
		{
			QDragMoveEvent *drag = (QDragMoveEvent*)event;
			if (drag->mimeData()->hasFormat("application/x-dnditemdata"))
			{
				//drag->setDropAction(Qt::MoveAction);
				drag->accept();
			}
			else
			{	
				drag->ignore();
			}
			return true;
		}
		else if (event->type() == QEvent::Drop)
		{
			QDropEvent *drop = (QDropEvent*)event;
			if (drop->mimeData()->hasFormat("application/x-dnditemdata"))
			{
				const QMimeData *mimeData = drop->mimeData();
				QByteArray exData = mimeData->data("application/x-dnditemdata");
				QDataStream dataStream(&exData, QIODevice::ReadOnly);
				QPixmap pixmap;
				QPoint pos = current_clip->pos();//QPoint origin_pos, pos;
				isEdited mode = current_clip->getEditedMode();
				dataStream >> pixmap; //>> origin_pos >> pos;
				//QLabel *item = new QLabel();
				//item->setPixmap(pixmap);
				//item->setAttribute(Qt::WA_DeleteOnClose);
				
				if (mode == isSelected)
				{
					//cliplabel *origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(origin_pos));
					//current_empty_clip = NULL;
					//cliplabel *cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
					current_empty_clip->cast(current_clip);
					current_empty_clip->setAcceptDrops(false);
					current_empty_clip->removeEventFilter(this);
					current_clip->uncast();
					current_clip = current_empty_clip;
					clips.at(current_clip_index) = current_clip;
					myPlayer->setClip(current_clip);
					current_empty_clip = NULL;
					//drop->setDropAction(Qt::MoveAction);
					//drop->accept();
					if (isCounting)
					{
						double time = (double)(clock() - start) / CLOCKS_PER_SEC;
						logger.push_back(QString::number(time).toStdString() + "  dropClip " + QString::number(current_clip_index).toStdString());
					}
					return true;
				}
				else if (mode == isSelectedDeleted)
				{
					//cliplabel *origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(origin_pos));
					//current_empty_clip = NULL;
					//cliplabel *cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(pos));
					current_empty_clip->cast(current_clip);
					current_empty_clip->setAcceptDrops(false);
					current_empty_clip->removeEventFilter(this);
					current_clip->uncast();
					current_clip = current_empty_clip;
					clips.at(current_clip_index) = current_clip;
					myPlayer->setClip(current_clip);
					current_empty_clip = NULL;
					//drop->setDropAction(Qt::MoveAction);
					//drop->accept();
					if (isCounting)
					{
						double time = (double)(clock() - start) / CLOCKS_PER_SEC;
						logger.push_back(QString::number(time).toStdString() + "  recoverClip " + QString::number(current_clip_index).toStdString());
					}
					return true;
				}
				/*else if (cut_type > 2)
					origin = static_cast<cliplabel*>(addedTrack.at(cut_type-3)->getCentralWidget()->childAt(origin_pos));*/
				//origin->setEditedMode(isMoved);
				else
				{
					drop->ignore();
					return false;
				}
				/*if (addedTrackCount != 0)
				{
					for (int i = 0; i < addedTrackCount; i++)
					{
						if (widget == addedTrack.at(i)->getCentralWidget())
						{
							cliplabel *move2item = new cliplabel(origin->getSrcImages(), origin->width(), origin->height(), origin->getCutIndex(), i+3, origin->getDisplayScale());
							move2item->setOriginRange(origin->getOriginRange());
							move2item->setGroupRange(origin->getGroupRange());
							move2item->setOriginMoving(origin->getOriginMoving());
							move2item->setGroupMovingRange(origin->getGroupMovingRange());
							addedTrack.at(i)->getLayout()->addWidget(move2item, 0, addedTrack.at(i)->getChildrenCount(), Qt::AlignLeft);
							addedTrack.at(i)->addChildrenCount();
							return true;
						}
					}
				}*/
			}
			else
			{
				drop->ignore();
				return false;
			}
		}
		else
			return false;
		}
    else 
		return false;
}

/*void MainWindow::playRange()
{
	vproc.writeVideo(clickRange, movingRange, action);
}*/

void MainWindow::on_editRadioButton_clicked()
{
	double time;
	if (isCounting)
		time = (double)(clock() - start) / CLOCKS_PER_SEC;

	if (ui->editRadioButton->isChecked())
	{
		frame_slider->setRange(current_clip->getRange().at(0), current_clip->getRange().at(1));
		frame_slider->setValue(current_clip->getRange().at(0));
		frame_slider->setTickPosition(QSlider::TicksAbove);
		frame_slider->setTickInterval(1);
		frame_slider->setMouseTracking(true);
		frame_slider->setEditMode(true);
		frame_slider->setLabels(current_clip->getCuts());
		frame_slider->setCuts(current_clip->getAutoCuts());
		//ui->frame_slider->setCursor(Qt::PointingHandCursor);
		frame_slider->installEventFilter(this);
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  editRadioButtonOn");
	}
	else
	{	
		current_clip->updatePixmap(fileName);
		QPoint pos = current_clip->pos();
		cliplabel *empty_clip = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
		int width = current_clip->getWidth();
		int height = current_clip->getHeight();
		empty_clip->setFixedSize(width, height);
		empty_clip->setSizeThreshold(width, height);
		initFrameSlider();
		frame_slider->setMouseTracking(false);
		frame_slider->removeEventFilter(this);
		if (isCounting)
			logger.push_back(QString::number(time).toStdString() + "  editRadioButtonOff");
	}
	refresh(current_clip->getRange().at(0));

    /*if (isCut)
    {
		if (ui->editRadioButton->isChecked())
        {
            //frame_slider->setMouseTracking(true);
            //frame_slider->setCursor(Qt::PointingHandCursor);
            //frame_slider->installEventFilter(this);

			ui->scrollAreaWidgetContents_1->setAcceptDrops(true);
			ui->scrollAreaWidgetContents_2->setAcceptDrops(true);
			ui->scrollAreaWidgetContents_1->installEventFilter(this);
			ui->scrollAreaWidgetContents_2->installEventFilter(this);

			//ui->actionSelect->setCheckable(true);
			//ui->actionView->setCheckable(true);
			//ui->actionSwap->setCheckable(true);
			//ui->actionReverse->setCheckable(true);
			//ui->actionCast->setCheckable(true);
			//ui->actionSelectTrack->setCheckable(true);
			//ui->actionAddTrack->setCheckable(true);
			//ui->actionDeleteTrack->setCheckable(true);
			//ui->actionViewTrack->setCheckable(true);
        }
        else
        {
            //frame_slider->setMouseTracking(false);
            //frame_slider->setCursor(Qt::ArrowCursor);
            //frame_slider->removeEventFilter(this);

			ui->scrollAreaWidgetContents_1->setAcceptDrops(false);
			ui->scrollAreaWidgetContents_2->setAcceptDrops(false);
			ui->scrollAreaWidgetContents_1->removeEventFilter(this);
			ui->scrollAreaWidgetContents_2->removeEventFilter(this);

			//ui->actionSelect->setCheckable(false);
			//ui->actionView->setCheckable(false);
			//ui->actionSwap->setCheckable(false);
			//ui->actionReverse->setCheckable(false);
			//ui->actionCast->setCheckable(false);
			//ui->actionSelectTrack->setCheckable(false);
			//ui->actionAddTrack->setCheckable(false);
			//ui->actionDeleteTrack->setCheckable(false);
			//ui->actionViewTrack->setCheckable(false);
        }
    }
    else
    {
        statusBar()->showMessage("Please cut the video first.");
    }*/
}

void MainWindow::on_countTimeButton_clicked()
{
	double time = (double)(clock() - start) / CLOCKS_PER_SEC;

	if (!isCounting)
	{
		start = clock();
		isCounting = true;
		statusBar()->showMessage("Start editing...");
		ui->countTimeButton->setText("End");
		logger.push_back(QString::number(time).toStdString() + "  startEditing");
	}
	else
	{
		end = clock();
		isCounting = false;
		double duration = (double)(end - start) / CLOCKS_PER_SEC;
		QString tip = "Editing duration: " + QString::number(duration);
		statusBar()->showMessage(tip);
		ui->countTimeButton->setText("Start");
		logger.push_back(QString::number(time).toStdString() + "  finishEditing");
		writeLogFile();
	}
}

/*void MainWindow::on_keepRadioButton_clicked()
{
	if (current_clip != NULL)
	{
		if (!ui->keepRadioButton->isChecked() && current_clip->getEditedMode() == isSelected)
		{
			QPoint pos = current_clip->pos();
			cliplabel *cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
			cast2item->cast(current_clip);
			current_clip->uncast();
			current_clip = cast2item;
			clips.at(current_clip_index) = current_clip;
		}
		else if (ui->keepRadioButton->isChecked() && current_clip->getEditedMode() == isSelectedDeleted)
		{
			QPoint pos = current_clip->pos();
			cliplabel *cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(pos));
			cast2item->cast(current_clip);
			current_clip->uncast();
			current_clip = cast2item;
			clips.at(current_clip_index) = current_clip;
		}
	}
	else
	{
		statusBar()->showMessage("Please cut the video first.");
	}
}*/

/*void MainWindow::reverse_action()
{
    //cout << "Reverse from " << clickRange.x << " to " << clickRange.y << endl;
	action = ReverseClip;
	playRange();

	int end = clickRange.size() - 1;
    QString tip = "Reverse from " + QString::number(clickRange.at(1)) + " to " + QString::number(clickRange.at(end));
    statusBar()->showMessage(tip);
}*/

void MainWindow::label_action()
{
	frame_slider->addLabel(labelIndex);
	current_clip->addCut(labelIndex);
	QString tip = "Labeling " + QString::number(labelIndex);
	statusBar()->showMessage(tip);
	disconnect(frame_slider, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu()));
	if (isCounting)
	{
		double time = (double)(clock() - start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(time).toStdString() + "  labelFrame " + QString::number(labelIndex).toStdString());
	}
}

void MainWindow::delete_action()
{
	frame_slider->deleteLabel(labelIndex);
	current_clip->deleteCut(labelIndex);
	QString tip = "Deleting " + QString::number(labelIndex);
	statusBar()->showMessage(tip);
	disconnect(frame_slider, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu()));
	if (isCounting)
	{
		double time = (double)(clock() - start) / CLOCKS_PER_SEC;
		logger.push_back(QString::number(time).toStdString() + "  deleteFrame " + QString::number(labelIndex).toStdString());
	}
}

void MainWindow::show_context_menu()
{
    if (sliderMenu != NULL)
    {
		sliderMenu->hide();
        delete sliderMenu;
        sliderMenu = NULL;
    }

    sliderMenu = new QMenu;

    QAction *labelAction = new QAction(QIcon(":/Images/icons/label.png"), tr("Start/End"), this);
	QAction *deleteAction = new QAction(QIcon(":/Images/icons/delete_32.png"), tr("Delete"), this);

    sliderMenu->addAction(labelAction);
    sliderMenu->addAction(deleteAction);

    connect(labelAction, SIGNAL(triggered(bool)), this, SLOT(label_action()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(delete_action()));

	sliderMenu->exec(QCursor::pos());
}

void MainWindow::updatePlayer(int frameIndex)
{
	if (current_clip->getCutType() == 2 && current_clip->getCuts().empty())
	{
		int current_position = ui->scrollArea_1->horizontalScrollBar()->sliderPosition();
		int base_width = current_clip->getBaseWidth();
		int clip_width = current_clip->width();
		int scroll_width = ui->scrollArea_1->width();
		int indexOffset = frameIndex - current_clip->getRange().at(0);

		if (clip_width > scroll_width && current_position + scroll_width <= ui->scrollAreaWidgetContents_1->width()
			&& indexOffset > 0 && indexOffset % (2 * vproc.getFrameRate()) == 0)
			ui->scrollArea_1->horizontalScrollBar()->setSliderPosition(current_position + base_width);
	}

	stringstream ss;
	string type = ".jpg";
	Mat frame;
	ss << frameIndex << type;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/UserTest_Tra1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/UserTest_Tra2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS1.avi") frame = imread("D:/CCCC/Stop Motion/US_SS1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_SS2.avi") frame = imread("D:/CCCC/Stop Motion/US_SS2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT1.avi") frame = imread("D:/CCCC/Stop Motion/US_XT1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XT2.avi") frame = imread("D:/CCCC/Stop Motion/US_XT2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_SSTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_SSTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_XTTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_XTTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_ZLTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_ZLTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL1.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_ZL2.avi") frame = imread("D:/CCCC/Stop Motion/US_ZL2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ1.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_JJ2.avi") frame = imread("D:/CCCC/Stop Motion/US_JJ2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL1.avi") frame = imread("D:/CCCC/Stop Motion/US_LL1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_LL2.avi") frame = imread("D:/CCCC/Stop Motion/US_LL2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR1.avi") frame = imread("D:/CCCC/Stop Motion/US_XR1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_XR2.avi") frame = imread("D:/CCCC/Stop Motion/US_XR2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK1.avi") frame = imread("D:/CCCC/Stop Motion/US_QK1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/US_QK2.avi") frame = imread("D:/CCCC/Stop Motion/US_QK2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_LLTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_LLTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_XRTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_XRTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_JJTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_JJTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/US_ZXTRA2/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/US_ZXTRA2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic1.avi") frame = imread("D:/CCCC/Stop Motion/Basic1/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic2.avi") frame = imread("D:/CCCC/Stop Motion/Basic2/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Basic3.avi") frame = imread("D:/CCCC/Stop Motion/Basic3/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Real.avi") frame = imread("D:/CCCC/Stop Motion/Real/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/RealTra/1080/0.jpg") frame = imread("D:/CCCC/Stop Motion/RealTra/540/" + ss.str());
	ss.str("");

	cv::Mat temp;
	cvtColor(frame, temp, CV_BGR2RGB);
	QImage current_image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	current_image.bits();

	QPixmap pix(ui->frameLabel->width(), ui->frameLabel->height());
	pix.fill(Qt::black);
	QPainter *paint = new QPainter(&pix);
	int w = pix.width();
	int h = pix.height();
	if (fileName == "D:/CCCC/Stop Motion/UserTest_Tra1/1080/0.jpg")
		paint->drawPixmap((w - h * 4 / 3) / 2, 0, h * 4 / 3, h, QPixmap::fromImage(current_image));
	else
		paint->drawPixmap((w - h * 16 / 9) / 2, 0, h * 16 / 9, h, QPixmap::fromImage(current_image));
	/*if (ui->editRadioButton->isChecked() && frameIndex == current_clip->getRange().at(0))
	{
		stringstream ss_1, ss_2;
		string type = ".jpg";
		Mat frame_1, frame_2;
		int start = current_clip->getRange().at(0);
		int end = current_clip->getRange().at(1);
		ss_1 << (start + end) / 2 << type;
		ss_2 << end << type;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test6/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test6/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test7/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test7/540/" + ss_2.str());
		}
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi")
		{
			frame_1 = imread("D:/CCCC/Stop Motion/Test8/540/" + ss_1.str());
			frame_2 = imread("D:/CCCC/Stop Motion/Test8/540/" + ss_2.str());
		}
		ss_1.str("");
		ss_2.str("");

		cvtColor(frame_1, temp, CV_BGR2RGB);
		QImage image_1((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image_1.bits();
		cvtColor(frame_2, temp, CV_BGR2RGB);
		QImage image_2((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image_2.bits();

		QPixmap pix_1((w - h * 16 / 9) / 3, h * 3 / 5);
		QPixmap pix_2((w - h * 16 / 9) / 6, h / 3);
		QPainter *paint_1 = new QPainter(&pix_1);
		QPainter *paint_2 = new QPainter(&pix_2);
		pix_1.fill(Qt::darkGray);
		pix_2.fill(Qt::darkGray);
		paint_1->drawPixmap(0, (pix_1.height() - pix_1.width() * 9 / 16) / 2, pix_1.width(), pix_1.width() * 9 / 16, QPixmap::fromImage(image_1));
		paint_1->end();
		paint_2->drawPixmap(0, (pix_2.height() - pix_2.width() * 9 / 16) / 2, pix_2.width(), pix_2.width() * 9 / 16, QPixmap::fromImage(image_2));
		paint_2->end();
		paint->drawPixmap((w + h * 16 / 9) / 2, h / 5, pix_1.width(), pix_1.height(), pix_1);
		paint->drawPixmap((w * 5 + h * 16 / 9) / 6, h / 3, pix_2.width(), pix_2.height(), pix_2);
	}*/
	paint->end();
	ui->frameLabel->setStyleSheet("");
	ui->frameLabel->setPixmap(pix);
	ui->frameLabel->repaint();

	if (ui->editRadioButton->isChecked())
		frame_slider->setValue(frameIndex);
}

void MainWindow::updateCurrentClip(int clipIndex)
{
	setCurrentClip(clips[clipIndex]);
}

void MainWindow::updatePlayButtonIcon(bool isPlayingClip)
{
	if (isPlayingClip) 
		ui->playClipButton->setIcon(QIcon(":/Images/icons/play_24.png"));
	else
		ui->playTrackButton->setIcon(QIcon(":/Images/icons/view-track.png"));
}