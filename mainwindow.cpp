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
    isCut = false;
	entered = false;
    //resize_count = -1;
    //window_current_width = this->width();
    //window_current_height = this->height() - ui->menuBar->height() - ui->mainToolBar->height();
	ui->frameLabel->setScaledContents(true);
	//ui->scrollArea->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_1->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_2->setBackgroundRole(QPalette::Midlight);
	//addedTrackCount = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::setClickRange(vector<int> indices)
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
}

void MainWindow::on_playButton1_clicked()
{
	if (!clickRange.empty()) clickRange.clear();
	clickRange = current_clip->getRange();

	int start = -1;
	int end = -1;
	Mat frame;
	stringstream ss;
	string type = ".jpg";
	int frameRate = vproc.getFrameRate();

	start = clickRange.at(0);
	end = clickRange.at(1);

	if (current_clip->getCutType() == 2)
	{
		int delay = 500 / frameRate;//delay = 1000 / frame_rate;
		for (int j = start; j <= end; j++)
		{
			ss << j << type;
			if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
			refresh(frame);
			Sleep(delay);
			ss.str("");
		}
	}
	else
	{
		ss << (start + end) / 2 << type;
		if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
		else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
		refresh(frame);
		ss.str("");
	}

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

void MainWindow::on_nextButton_clicked()
{
	if (current_clip_index < clips.size() - 1)
		setCurrentClip(clips.at(current_clip_index+1));
}

void MainWindow::on_pauseButton_clicked()
{
    //mediaplayer_1->pause();
}

void MainWindow::on_cutButton_clicked()
{
    /*progressBar = vproc.getProgressBar();
	ui->verticalLayout_2->addWidget(progressBar);
    progressBar->show();*/

	vproc.readBuffers();
	/*if (vproc.getSceneCuts().empty() || vproc.getCutTypes().empty())
		vproc.cut2Scenes();
	vproc.writeBuffers();*/
	//frame_slider->updateParams(vproc.getSceneCuts(), vproc.getCutTypes());
    isCut = true;
    statusBar()->clearMessage();

    /*progressBar->hide();
	ui->verticalLayout_2->removeWidget(progressBar);
    delete progressBar;*/

	visualizeClips();
	current_clip = clips.at(0);
	current_clip_index = 0;
	if (current_clip->getEditedMode() == NotEdited)
	{
		current_clip->setEditedMode(isSelected);
		ui->keepRadioButton->setChecked(true);
	}
	else
	{
		current_clip->setEditedMode(isSelectedDeleted);
		ui->keepRadioButton->setChecked(false);
	}
	//vproc.test();
}

void MainWindow::refresh(Mat img)
{
    cv::Mat temp;
    cvtColor(img, temp, CV_BGR2RGB);
    QImage current_image((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    current_image.bits();

	QPixmap pix(ui->frameLabel->width(), ui->frameLabel->height());
	pix.fill(Qt::black);
	QPainter *paint = new QPainter(&pix);
	paint->drawPixmap((pix.width()-pix.height()*16/9)/2, 0, pix.height()*16/9, pix.height(), QPixmap::fromImage(current_image));
	paint->end();
    
	ui->frameLabel->setStyleSheet("");
	ui->frameLabel->setPixmap(pix);
	ui->frameLabel->repaint();
}

void MainWindow::seek(int seconds)
{
	//mediaplayer_1->setPosition(seconds);//mediaplayer_1->setPosition(seconds * 1000);
}

void MainWindow::slotEntered(bool isEntered)
{
	entered = isEntered;
}

void MainWindow::on_actionLoad_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Video Files(*.mp4 *.avi *.mov);;All files (*.*)" ));
    if (fileName.isEmpty())
        return;

    vproc.readVideo(fileName.toStdString());
	ui->frameLabel->setStyleSheet("background-color: rgb(0, 0, 0); image: url(D:/CCCC/Stop Motion/Videos/preview.png);");
	//initFrameSlider();
}

void MainWindow::visualizeClips()
{
	vector<int> scene_cuts = vproc.getSceneCuts();
	vector<int> cut_types = vproc.getCutTypes();
	//vector<Mat> frames = vproc.getFrames();
	int frameRate = vproc.getFrameRate();
	int height = floor(0.8 * ui->scrollArea_1->height());
	int base_width = ceil(height * vproc.getFrameWidth() / double(vproc.getFrameHeight()));
	int base, width, cut_size, length;
	
	/*myscrollarea *scroll = new myscrollarea();
	ui->verticalLayout->addWidget(scroll);
	scroll->getCentralWidget()->installEventFilter(this);
	addedTrackCount++;
	addedTrack.push_back(scroll);*/

	stringstream ss;
	string type = ".jpg";

	ifstream flowfile;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") flowfile.open("D:/CCCC/Stop Motion/Test6/suggestion_threshold.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") flowfile.open("D:/CCCC/Stop Motion/Test7/suggestion_threshold.txt");
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") flowfile.open("D:/CCCC/Stop Motion/Test8/suggestion_threshold.txt");

	for (int i = 0; i < scene_cuts.size(); i++)
	{
		vector<Mat> srcImages;
		if (i == 0)
			base = 0;
		else
			base = scene_cuts.at(i-1) + 1;
		cut_size = scene_cuts.at(i) - base + 1;

		if (cut_size % (2*frameRate) == 0)
			length = cut_size / (2*frameRate);
		else
			length = cut_size / (2*frameRate) + 1;
		
		if (cut_types.at(i) == 1)
			width = base_width + base_width/10*(length-1);
		else
			width = base_width * length;

		for (int j = 0; j < length; j++)
		{
			ss << base + 2*j*frameRate << type;
			if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test/480/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str()));
			else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") srcImages.push_back(imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str()));
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

		if (cut_types.at(i) == 1)
		{
			cliplabel *empty_clip = new cliplabel();
			empty_clip->setFixedSize(width, height);
			empty_clip->setSizeThreshold(width, height);

			if (stableClips.size() != 0)
			{
				/*Mat previousFrame, currentFrame;
				ss << (clip->getOriginRange().at(0) + clip->getOriginRange().at(1)) / 2 << type;
				if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") currentFrame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
				ss.str("");
				ss << (stableClip.at(stableClip.size() - 1)->getOriginRange().at(0) + stableClip.at(stableClip.size() - 1)->getOriginRange().at(1)) / 2 << type;
				if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test6/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
				else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") previousFrame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
				ss.str("");
				cout << vproc.calAvgOpFlow(previousFrame, currentFrame) << endl;*/
				
				float avgOpFlow;
				flowfile >> avgOpFlow;

				cliplabel *previousMovingClip = movingClips.at(movingClips.size() - 1);
				cliplabel *previousEmptyClip = new cliplabel();
				int previous_w = previousMovingClip->getWidth();
				int previous_h = previousMovingClip->getHeight();
				previousEmptyClip->setFixedSize(previous_w, previous_h);
				empty_clip->setSizeThreshold(previous_w, previous_h);

				if (avgOpFlow >= 0.005 && avgOpFlow <= 0.9)
				{
					movingClips.at(movingClips.size() - 1)->setEditedMode(isDeleted);
					ui->gridLayout_3->addWidget(previousMovingClip, 0, i-1, Qt::AlignLeft);
					ui->gridLayout_2->addWidget(previousEmptyClip, 0, i-1, Qt::AlignLeft);
				}
				else
				{
					ui->gridLayout_2->addWidget(previousMovingClip, 0, i - 1, Qt::AlignLeft);
					ui->gridLayout_3->addWidget(previousEmptyClip, 0, i - 1, Qt::AlignLeft);
				}
			}
			ui->gridLayout_2->addWidget(clip, 0, i, Qt::AlignLeft);
			ui->gridLayout_3->addWidget(empty_clip, 0, i, Qt::AlignLeft);
			stableClips.push_back(clip);
		}
		else
			movingClips.push_back(clip);

		connect(clip, SIGNAL(signalEntered(bool)), this, SLOT(slotEntered(bool)));
	}

	flowfile.close();

	connect(ui->scrollArea_1->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_2->horizontalScrollBar(), SLOT(setValue(int)));
	connect(ui->scrollArea_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_1->horizontalScrollBar(), SLOT(setValue(int)));
	ui->scrollArea_1->setBackgroundRole(QPalette::Dark);
	ui->scrollArea_2->setBackgroundRole(QPalette::Dark);

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

void MainWindow::on_actionView_triggered()
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
}

void MainWindow::on_actionSwap_triggered()
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
}

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

void MainWindow::on_actionSelectTrack_triggered()
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
}

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

void MainWindow::on_actionViewTrack_triggered()
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
			/*else
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
			}*/
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
		/*else if (selectedTrack.size() == 2)
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
		}*/
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
}

bool MainWindow::eventFilter(QObject *widget, QEvent *event)
{
    /*if (widget == frame_slider)
	{
		if (event->type() == QEvent::MouseMove)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			QString tip = "position: (" + QString::number(m->x()) + ", " + QString::number(m->y()) + ")";
			statusBar()->showMessage(tip);
			return true;
		}
		else if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			clickRange = vproc.getRange(m->x(), frame_slider->width());

			if (m->button() == Qt::LeftButton)
			{
				action = ViewClip;
				playRange();
			}
			else if (m->button() == Qt::RightButton)
			{
				frame_slider->setContextMenuPolicy(Qt::CustomContextMenu);
				connect(frame_slider, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu()));
			}

			return true;
		}
		else if (event->type() == QEvent::Leave)
		{
			statusBar()->clearMessage();
			return true;
		}

		return true;
	}*/

	if ((widget == ui->scrollAreaWidgetContents_1 || widget == ui->scrollAreaWidgetContents_2) && entered == true) //|| addedTrackCount != 0)
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
				setCurrentClip(item);
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

			return true;
		}

		else if (event->type() == QEvent::DragEnter)
		{
			QDragEnterEvent *drag = (QDragEnterEvent*)event;
			if (drag->mimeData()->hasFormat("application/x-dnditemdata"))
				drag->accept();
			else
				drag->ignore();
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
				QPoint origin_pos, pos;
				int cut_type;
				dataStream >> pixmap >> cut_type >> origin_pos >> pos;
				QLabel *item = new QLabel();
				item->setPixmap(pixmap);
				item->setAttribute(Qt::WA_DeleteOnClose);
				cliplabel *origin;
				if (cut_type == 1)
					origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(origin_pos));
				else if (cut_type == 2)
					origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(origin_pos));
				/*else if (cut_type > 2)
					origin = static_cast<cliplabel*>(addedTrack.at(cut_type-3)->getCentralWidget()->childAt(origin_pos));*/
				origin->setEditedMode(isMoved);

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
			return true;
		}

		return true;
	}

    else 
		return false;
}

void MainWindow::playRange()
{
	vproc.writeVideo(clickRange, movingRange, action);
}

void MainWindow::on_editRadioButton_clicked()
{
    if (isCut)
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
			ui->actionView->setCheckable(true);
			ui->actionSwap->setCheckable(true);
			//ui->actionReverse->setCheckable(true);
			//ui->actionCast->setCheckable(true);
			ui->actionSelectTrack->setCheckable(true);
			//ui->actionAddTrack->setCheckable(true);
			//ui->actionDeleteTrack->setCheckable(true);
			ui->actionViewTrack->setCheckable(true);
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
			ui->actionView->setCheckable(false);
			ui->actionSwap->setCheckable(false);
			//ui->actionReverse->setCheckable(false);
			//ui->actionCast->setCheckable(false);
			ui->actionSelectTrack->setCheckable(false);
			//ui->actionAddTrack->setCheckable(false);
			//ui->actionDeleteTrack->setCheckable(false);
			ui->actionViewTrack->setCheckable(false);
        }
    }
    else
    {
        statusBar()->showMessage("Please cut the video first.");
    }
}

void MainWindow::on_keepRadioButton_clicked()
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
}

void MainWindow::setCurrentClip(cliplabel *clip)
{
	if (current_clip->getEditedMode() == isSelected)
		current_clip->setEditedMode(NotEdited);
	else if (current_clip->getEditedMode() == isSelectedDeleted)
		current_clip->setEditedMode(isDeleted);
	
	current_clip = clip;
	current_clip_index = clip->getCutIndex();
	
	if (current_clip->getEditedMode() == NotEdited)
	{
		current_clip->setEditedMode(isSelected);
		ui->keepRadioButton->setChecked(true);
	}
	else if (current_clip->getEditedMode() == isDeleted)
	{
		current_clip->setEditedMode(isSelectedDeleted);
		ui->keepRadioButton->setChecked(false);
	}

	stringstream ss;
	string type = ".jpg";
	Mat frame;
	ss << current_clip->getRange().at(0) << type;
	if (fileName == "D:/CCCC/Stop Motion/Videos/Test.avi") frame = imread("D:/CCCC/Stop Motion/Test/480/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test4.avi") frame = imread("D:/CCCC/Stop Motion/Test4/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test5.avi") frame = imread("D:/CCCC/Stop Motion/Test5/270/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test6.avi") frame = imread("D:/CCCC/Stop Motion/Test6/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/540/" + ss.str());
	else if (fileName == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/540/" + ss.str());
	ss.str("");

	refresh(frame);
}

/*void MainWindow::reverse_action()
{
    //cout << "Reverse from " << clickRange.x << " to " << clickRange.y << endl;
	action = ReverseClip;
	playRange();

	int end = clickRange.size() - 1;
    QString tip = "Reverse from " + QString::number(clickRange.at(1)) + " to " + QString::number(clickRange.at(end));
    statusBar()->showMessage(tip);
}*/

/*void MainWindow::show_context_menu()
{
    if (sliderMenu)
    {
        delete sliderMenu;
        sliderMenu = NULL;
    }

    sliderMenu =new QMenu;

    QAction *deleteAction = new QAction(tr("Delete"),this);
    QAction *reverseAction = new QAction(tr("Reverse"),this);

    sliderMenu->addAction(deleteAction);
    sliderMenu->addAction(reverseAction);

    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(delete_action()));
    connect(reverseAction, SIGNAL(triggered(bool)), this, SLOT(reverse_action()));

    sliderMenu->exec(QCursor::pos());
}*/

/*void MainWindow::initFrameSlider()
{
	vector<int> sc = vproc.getSceneCuts();
	vector<int> ft = vproc.getCutTypes();
	frame_slider = new myslider(Qt::Horizontal, sc, ft);
}*/
