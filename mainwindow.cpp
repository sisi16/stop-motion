#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <iostream>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isCut = false;
    resize_count = -1;
    window_current_width = this->width();
    window_current_height = this->height() - ui->menuBar->height() - ui->mainToolBar->height();
	ui->scrollArea->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_1->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_2->setBackgroundRole(QPalette::Midlight);
	videoWidget_1 = new QVideoWidget;
	videoWidget_2 = new QVideoWidget;
	addedTrackCount = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* ev)
{
    resize_count++;
	int video1_current_width, video1_current_height, video2_current_width, video2_current_height;
    if (resize_count > 0)
    {
		if (videoWidget_1->parent() != 0)
		{
			video1_current_width = videoWidget_1->width();
			video1_current_height = videoWidget_1->height();
		}

		if (videoWidget_2->parent() != 0)
		{
			video2_current_width = videoWidget_2->width();
			video2_current_height = videoWidget_2->height();
		}
    }

	QMainWindow::resizeEvent(ev);

    if (resize_count > 0)
    {
		if (videoWidget_1->parent() != 0)
		{
			int video_width = floor(this->width()*video1_current_width / double(window_current_width));
			int video_height = floor(this->height()*video1_current_height / double(window_current_height));
			videoWidget_1->setFixedSize(video_width, video_height);
		}
		if (videoWidget_2->parent() != 0)
		{
			int video_width = floor(this->width()*video2_current_width / double(window_current_width));
			int video_height = floor(this->height()*video2_current_height / double(window_current_height));
			videoWidget_2->setFixedSize(video_width, video_height);
		}
    }

    window_current_width = this->width();
    window_current_height = this->height() - ui->menuBar->height() - ui->mainToolBar->height();
}

void MainWindow::setClickRange(vector<int> indices)
{
	if (!clickRange.empty()) clickRange.clear();
		
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
    QLayoutItem *child;

	if (videoWidget_1->parent() == 0)
    {
		child = ui->horizontalLayout_1->takeAt(0);
        child->widget()->setVisible(0);
		ui->horizontalLayout_1->removeWidget(child->widget());
        delete child;

        videoWidget_1->setFixedSize(ui->bgLabel_1->width(), ui->bgLabel_1->height());//videoWidget_1->setFixedSize(460, 345);
		ui->horizontalLayout_1->addWidget(videoWidget_1);
    }

	if (frame_slider->parent() == 0)
    {
		child = ui->verticalLayout_2->takeAt(0);
		child->widget()->setVisible(0);
		ui->verticalLayout_2->removeWidget(child->widget());
		delete child;

		frame_slider->setRange(0, mediaplayer_1->duration()); //frame_slider->setRange(0, 30000);
		frame_slider->setValue(0);
		frame_slider->setTickPosition(QSlider::TicksAbove);
		frame_slider->setTickInterval(500);
		connect(frame_slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
		ui->verticalLayout_2->addWidget(frame_slider);
    }

	mediaplayer_1->play();
}

void MainWindow::on_stopButton1_clicked()
{
    mediaplayer_1->stop();
}

void MainWindow::on_pauseButton1_clicked()
{
    mediaplayer_1->pause();
}

void MainWindow::on_cutButton_clicked()
{
    progressBar = vproc.getProgressBar();
	ui->verticalLayout_2->addWidget(progressBar);
    progressBar->show();

	vproc.readBuffers();
	//if (vproc.getSceneCuts().empty() || vproc.getCutTypes().empty())
		//vproc.cut2Scenes();
	//vproc.writeBuffers();
	frame_slider->updateParams(vproc.getSceneCuts(), vproc.getCutTypes());
    isCut = true;
    statusBar()->clearMessage();

    progressBar->hide();
	ui->verticalLayout_2->removeWidget(progressBar);
    delete progressBar;

	//vproc.test();
}

void MainWindow::on_okButton_clicked()
{
	
}

void MainWindow::refresh(int value)
{
    QLabel* current_frame = new QLabel;
    current_frame->setScaledContents(true);
    current_frame->setFixedSize(0, 0);

    cv::Mat temp;
    cvtColor(vproc.getFrames().at(value), temp, CV_BGR2RGB);
    QImage current_image((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    current_image.bits();

    current_frame->setPixmap(QPixmap::fromImage(current_image));
    current_frame->pixmap()->size().scale(size(), Qt::IgnoreAspectRatio);
    current_frame->setFixedSize(640, 480);

    QLayoutItem *child;
	if ((child = ui->verticalLayout_2->takeAt(1)) != 0)
    {
        child->widget()->setVisible(0);
		ui->verticalLayout_2->removeWidget(child->widget());
        delete child;
    }
	ui->verticalLayout_2->addWidget(current_frame);
}

void MainWindow::seek(int seconds)
{
	mediaplayer_1->setPosition(seconds);//mediaplayer_1->setPosition(seconds * 1000);
}

void MainWindow::on_actionLoad_triggered()
{
    mediaplayer_1 = new QMediaPlayer;
    mediaplayer_2 = new QMediaPlayer;
    //videoWidget_1 = new QVideoWidget;
	//videoWidget_2 = new QVideoWidget;
    mediaplayer_1->setVideoOutput(videoWidget_1);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Video Files(*.mp4 *.avi *.mov);;All files (*.*)" ));
    if (fileName.isEmpty())
        return;

    vproc.readVideo(fileName.toStdString());
	//cout << vproc.getNumOfFrames() << endl;
    mediaplayer_1->setMedia(QUrl::fromLocalFile(fileName));
	ui->bgLabel_1->setStyleSheet("background-color: rgb(0, 0, 0); image: url(D:/CCCC/Stop Motion/2015_05/preview.png);");
	initFrameSlider();
    /*preview_1 = new QLabel;
    preview_1->setScaledContents(true);

	cv::Mat temp;
    cv::cvtColor(vproc.getFrames().at(0), temp, CV_BGR2RGB);
	cv::imwrite("D:/CCCC/Stop Motion/2015_05/preview.png", temp);
	QImage image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	image.bits();

	int height = ui->bgLabel_1->height();
	int width = floor(height * image.width() / double(image.height()));

    preview_1->setPixmap(QPixmap::fromImage(image));
    preview_1->pixmap()->size().scale(image.size(), Qt::KeepAspectRatio);
    preview_1->setFixedSize(width, height);

    QLayoutItem *child;
	if ((child = ui->horizontalLayout_1->takeAt(0)) != 0)  {
        child->widget()->setVisible(0);
		ui->horizontalLayout_1->removeWidget(child->widget());
        delete child;
    }

	ui->horizontalLayout_1->addWidget(preview_1, Qt::AlignCenter);*/
    //preview_1->setPixmap(pm.scaled(width, height, Qt::KeepAspectRatio));
}

void MainWindow::on_actionCandidates_triggered()
{
    cv::Mat temp;

    vproc.calAvgOpFlows();

    if (!vproc.getStableFrames().empty())
    {
        QLayoutItem *child;
		while ((child = ui->verticalLayout_2->takeAt(0)) != 0)  {
            child->widget()->setVisible(0);
			ui->verticalLayout_2->removeWidget(child->widget());
            delete child;
        }

        vector<int> stable_frames = vproc.getStableFrames();
        int displays_count = signed(stable_frames.size());
        int label_height = 0.0;
        int rows_count = displays_count / 10;

        if (displays_count % 10 == 0)
            label_height = (640/rows_count >= 113) ? 113 : 640/rows_count;
        else
            label_height = (640/(rows_count+1) >= 113) ? 113 : 640/(rows_count+1);

        for (int i = 0; i < displays_count; i++) {
            QLabel* label = new QLabel;
            label->setScaledContents(true);
            label->setFixedSize(0, 0);

            int frame_index = stable_frames.at(i);
            cvtColor(vproc.getFrames().at(frame_index), temp, CV_BGR2RGB);
            QImage image((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
            image.bits();

            label->setPixmap(QPixmap::fromImage(image));
            label->pixmap()->size().scale(size(), Qt::IgnoreAspectRatio);
            label->setFixedSize(170, label_height);
			//ui->verticalLayout_2->addWidget(label, i / 10, i % 10, 0);
        }
    }
}

void MainWindow::on_actionTest_triggered()
{
	vector<int> scene_cuts = vproc.getSceneCuts();
	vector<int> cut_types = vproc.getCutTypes();
	vector<Mat> frames = vproc.getFrames();
	int frameRate = vproc.getFrameRate();
	int height = floor(0.8 * ui->scrollArea_1->height());
	int base_width = ceil(height * vproc.getFrameWidth() / double(vproc.getFrameHeight()));
	int base, width, length;
	
	for (int i = 0; i < scene_cuts.size(); i++)
	{
		vector<Mat> srcImages;
		if (i == 0)
			base = 0;
		else
			base = scene_cuts.at(i-1) + 1;
		length = (scene_cuts.at(i)-base+1) / frameRate + 1;
		width = base_width * length;
		for (int j = 0; j < length; j++)
			srcImages.push_back(frames.at(base+j*frameRate));
		
		cliplabel *clip = new cliplabel(srcImages, width, height, i, cut_types.at(i));
		vector<int> range;
		range.push_back(base);
		range.push_back(scene_cuts.at(i));
		clip->setOriginRange(range);
		clip->setGroupRange(range);
		cliplabel *empty_clip = new cliplabel();
		empty_clip->setFixedSize(width, height);
		empty_clip->setSizeThreshold(width, height);

		if (cut_types.at(i) == 1)
		{
			ui->gridLayout_2->addWidget(clip, 0, i, Qt::AlignLeft);
			ui->gridLayout_3->addWidget(empty_clip, 0, i, Qt::AlignLeft);
		}
		else
		{
			ui->gridLayout_3->addWidget(clip, 0, i, Qt::AlignLeft);
			ui->gridLayout_2->addWidget(empty_clip, 0, i, Qt::AlignLeft);
		}

		connect(clip, SIGNAL(enter(int)), frame_slider, SLOT(highLight(int)));
	}

	connect(ui->scrollArea_1->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_2->horizontalScrollBar(), SLOT(setValue(int)));
	connect(ui->scrollArea_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_1->horizontalScrollBar(), SLOT(setValue(int)));
}

void MainWindow::on_actionSelect_triggered()
{
	if (!ui->actionSelect->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionSelect->isChecked())
	{
		selectedClip.clear();
		seletedPos.clear();
		action = SelectClip;
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionResume_triggered()
{
	if (!ui->actionResume->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionResume->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		for (int i = 0; i < selectedClip.size(); i++)
		{
			cliplabel *item = selectedClip.at(i);
			QPoint pos = seletedPos.at(i);
			if (item->getEditedMode() == isCasted)
			{
				cliplabel *cast2item;
				if (item->getCutType() == 1)
					cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(pos));
				else
					cast2item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(pos));
				cast2item->uncast();
			}
			item->setEditedMode(isResumed);
		}
		action = ResumeClip;
		ui->actionResume->setChecked(false);
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionView_triggered()
{
	if (!ui->actionView->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionView->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		if (selectedClip.size() == 1)
		{
			cliplabel *item = selectedClip.at(0);
			//setClickRange(item->getGroupIndices());
			if (!clickRange.empty()) clickRange.clear();
			clickRange = item->getGroupRange();
			action = ViewClip;
			playRange();
			item->setEditedMode(NotEdited);
		}
		else
		{
			QString tip = "Please select one and only one clip.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedClip.size(); i++)
			{
				cliplabel *item = selectedClip.at(i);
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

void MainWindow::on_actionDelete_triggered()
{
	if (!ui->actionDelete->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionDelete->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		if (selectedClip.size() == 1 && selectedClip.at(0)->getIsGrouped() == false)
		{
			cliplabel *item = selectedClip.at(0);
			//setClickRange(item->getGroupIndices());
			if (!clickRange.empty()) clickRange.clear();
			clickRange = item->getOriginRange();
			clickRange.push_back(item->getCutIndex());
			action = DeleteClip;
			playRange();
			item->setEditedMode(isDeleted);
		}
		else
		{
			QString tip = "Please select one and only one clip.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedClip.size(); i++)
			{
				cliplabel *item = selectedClip.at(i);
				item->setEditedMode(NotEdited);
			}
		}
		ui->actionDelete->setChecked(false);
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionReverse_triggered()
{
	if (!ui->actionReverse->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionReverse->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		if (selectedClip.size() == 1)
		{
			cliplabel *item = selectedClip.at(0);
			//setClickRange(item->getGroupIndices());
			if (!clickRange.empty()) clickRange.clear();
			clickRange = item->getGroupRange();
			action = ReverseClip;
			playRange();
		}
		else
		{
			QString tip = "Please select one and only one clip.";
			statusBar()->showMessage(tip);
			for (int i = 0; i < selectedClip.size(); i++)
			{
				cliplabel *item = selectedClip.at(i);
				item->setEditedMode(NotEdited);
			}
		}
		ui->actionReverse->setChecked(false);
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionCast_triggered()
{
	if (!ui->actionCast->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionCast->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		for (int i = 0; i < selectedClip.size(); i++)
		{
			cliplabel *item = selectedClip.at(i);
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
}

void MainWindow::on_actionGroup_triggered()
{
	if (!ui->actionGroup->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionGroup->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		int cut_index; //track_index;
		int cut_type = selectedClip.at(0)->getCutType();
		int size = selectedClip.size();
		vector<int> group_indices;
		vector<int> group_range;
		vector<int> current_range;
		cliplabel *item;
		if (cut_type == 1)
		{
			for (int i = 0; i < size; i++)
			{
				item = selectedClip.at(i);
				current_range = item->getOriginRange();
				cut_index = item->getCutIndex();
				group_indices.push_back(cut_index);
				for (int j = 0; j < current_range.size(); j++)
					group_range.push_back(current_range.at(j));
				item->setEditedMode(isGrouped);
				item->setIsGrouped(true);
				if (i < size - 1)
					ui->gridLayout_2->itemAt(cut_index + 1)->widget()->setStyleSheet("image: url(:/Images/icons/connect.png);");
			}
			for (int i = 0; i < size; i++)
			{
				selectedClip.at(i)->setGroupIndices(group_indices);
				selectedClip.at(i)->setGroupRange(group_range);
			}
		} 
		else if (cut_type == 2)
		{
			for (int i = 0; i < size; i++)
			{
				item = selectedClip.at(i);
				current_range = item->getOriginRange();
				cut_index = selectedClip.at(i)->getCutIndex();
				group_indices.push_back(cut_index);
				for (int j = 0; j < current_range.size(); j++)
					group_range.push_back(current_range.at(j));
				selectedClip.at(i)->setEditedMode(isGrouped);
				item->setIsGrouped(true);
				if (i < size - 1)
					ui->gridLayout_3->itemAt(cut_index + 1)->widget()->setStyleSheet("image: url(:/Images/icons/connect.png);");
			}
			for (int i = 0; i < size; i++)
			{
				selectedClip.at(i)->setGroupIndices(group_indices);
				selectedClip.at(i)->setGroupRange(group_range);
			}
		}
		/*else if (cut_type > 2)
		{
			QGridLayout *layout = addedTrackLayout.at(cut_type - 3);
			for (int i = 0; i < size; i++)
			{	
				cut_index = selectedClip.at(i)->getCutIndex();
				track_index = selectedClip.at(i)->getTrackIndex();
				group_indices.push_back(cut_index);
				selectedClip.at(i)->setEditedMode(isGrouped);
				if (i < size - 1)
				{
					layout->itemAt(track_index + 1)->widget()->setStyleSheet("image: url(:/Images/icons/connect.png);");
				}
			}
		}*/

		/*for (int i = 0; i < size; i++)
		{
			selectedClip.at(i)->setGroupIndices(group_indices);
			selectedClip.at(i)->setGroupRange(group_range);
		}*/
		//action = GroupClip;
		ui->actionGroup->setChecked(false);
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionUngroup_triggered()
{
	if (!ui->actionUngroup->isCheckable())
	{
		QString tip = "Please enable edit mode first.";
		statusBar()->showMessage(tip);
	}
	else if (ui->actionUngroup->isChecked() && !selectedClip.empty() && !seletedPos.empty())
	{
		ui->actionSelect->setChecked(false);
		selectedClip.at(0)->setEditedMode(NotEdited);

		int cut_index; //track_index;
		int cut_type = selectedClip.at(0)->getCutType();
		vector<int> group_indices = selectedClip.at(0)->getGroupIndices();
		int size = group_indices.size();

		if (cut_type == 1)
		{
			for (int i = 0; i < size; i++)
			{
				cut_index = group_indices.at(i);
				cliplabel* item = static_cast<cliplabel*>(ui->gridLayout_2->itemAt(cut_index)->widget());
				item->setUnGroupIndices();
				item->setUnGroupRange();
				item->setEditedMode(NotEdited);
				item->setIsGrouped(false);
				if (i < size - 1)
					ui->gridLayout_2->itemAt(cut_index + 1)->widget()->setStyleSheet("image: none");
			}
		}
		else if (cut_type == 2)
		{
			for (int i = 0; i < size; i++)
			{
				cut_index = group_indices.at(i);
				cliplabel* item = static_cast<cliplabel*>(ui->gridLayout_3->itemAt(cut_index)->widget());
				item->setUnGroupIndices();
				item->setUnGroupRange();
				item->setEditedMode(NotEdited);
				item->setIsGrouped(false);
				if (i < size - 1)
					ui->gridLayout_3->itemAt(cut_index + 1)->widget()->setStyleSheet("image: none");
			}
		}
		/*else if (cut_type > 2)
		{
			QGridLayout *layout = addedTrackLayout.at(cut_type - 3);
			for (int i = 0; i < size; i++)
			{
				cliplabel* item = static_cast<cliplabel*>(layout->itemAt(cut_index)->widget());
				track_index = item->getTrackIndex();
				item->setUnGroupIndices();
				if (i < size - 1)
					layout->itemAt(track_index + 1)->widget()->setStyleSheet("image: none");
			}
		}*/

		//action = GroupClip;
		ui->actionUngroup->setChecked(false);
	}
	else
		action = NullOperation;
}

void MainWindow::on_actionZoomIn_triggered()
{
	int currentSliderWidth = frame_slider->width();
	frame_slider->setFixedWidth(2*currentSliderWidth);

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
}

void MainWindow::on_actionZoomOut_triggered()
{
	int current_width = frame_slider->width();
	frame_slider->setFixedWidth(floor(0.5 * current_width));

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
}

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

void MainWindow::on_actionAddTrack_triggered()
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
}

void MainWindow::on_actionDeleteTrack_triggered()
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
}

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
			myscrollarea *my_scroll;
			QLayoutItem *child;
			QGridLayout *layout;
			if (!clickRange.empty()) clickRange.clear();

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
				if (item->getEditedMode() != isMoved && item->getEditedMode() != isDeleted && item->getEditedMode() != isCasted)
				{
					for (int i = 0; i < item->getOriginRange().size(); i++)
						clickRange.push_back(item->getOriginRange().at(i));
				}
				count++;
			}

			//setClickRange(track_indices);
			scroll->setFrameStyle(QFrame::NoFrame);
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
}

void MainWindow::on_actionItpl_triggered()
{
	cliplabel* item = static_cast<cliplabel*>(ui->gridLayout_2->itemAt(1)->widget());
	item->setFixedWidth(500);
}

bool MainWindow::eventFilter(QObject *widget, QEvent *event)
{
    if (widget == frame_slider)
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
	}

	else if (widget == ui->scrollAreaWidgetContents_1 || widget == ui->scrollAreaWidgetContents_2 || addedTrackCount != 0)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *m = (QMouseEvent*)event;
			if (m->button() == Qt::LeftButton)
			{
				if (action == SelectTrack)
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
				}

				else if (action == SelectClip)
				{
					cliplabel *item;
					if (widget == ui->scrollAreaWidgetContents_1)
						item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(m->pos()));
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
								break;
							}
						}
					}

					item->setEditedMode(isSelected);
					selectedClip.push_back(item);
					seletedPos.push_back(m->pos());
				}

				else if (action == MoveClip)
				{
					cliplabel *item;
					int track_index = -1;
					if (widget == ui->scrollAreaWidgetContents_1)
						item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(m->pos()));
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
					else
						drag = new QDrag(addedTrack.at(track_index)->getCentralWidget());
					drag->setMimeData(mimeData);
					drag->setPixmap(pixmap.scaledToHeight(50));
					drag->setHotSpot(m->pos() - item->pos());
					//item->hide();
					if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
						item->close();
					else
						item->show();
				}
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
				else if (cut_type > 2)
					origin = static_cast<cliplabel*>(addedTrack.at(cut_type-3)->getCentralWidget()->childAt(origin_pos));
				origin->setEditedMode(isMoved);

				if (addedTrackCount != 0)
				{
					for (int i = 0; i < addedTrackCount; i++)
					{
						if (widget == addedTrack.at(i)->getCentralWidget())
						{
							cliplabel *move2item = new cliplabel(origin->getSrcImages(), origin->width(), origin->height(), origin->getCutIndex(), i+3);
							move2item->setOriginRange(origin->getOriginRange());
							move2item->setGroupRange(origin->getGroupRange());
							addedTrack.at(i)->getLayout()->addWidget(move2item, 0, addedTrack.at(i)->getChildrenCount(), Qt::AlignLeft);
							addedTrack.at(i)->addChildrenCount();
							return true;
						}
					}
				}
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
	int width, height;

	if (mediaplayer_2->mediaStatus() == QMediaPlayer::EndOfMedia)
	{
		width = videoWidget_2->width();
		height = videoWidget_2->height();

		mediaplayer_2->setMedia(QMediaContent());

		QLayoutItem *child;
		if ((child = ui->horizontalLayout_2->takeAt(0)) != 0)
		{
			child->widget()->setVisible(0);
			ui->horizontalLayout_2->removeWidget(child->widget());
			delete child;
		}
		delete mediaplayer_2;

		videoWidget_2 = new QVideoWidget;
		mediaplayer_2 = new QMediaPlayer;
	}
	else
	{
		width = ui->bgLabel_2->width();
		height = ui->bgLabel_2->height();
	}

	vproc.writeVideo(clickRange, action);

    mediaplayer_2->setVideoOutput(videoWidget_2);
    videoWidget_2->setFixedSize(width, height);

    QLayoutItem *child;
	if ((child = ui->horizontalLayout_2->takeAt(0)) != 0)
    {
        child->widget()->setVisible(0);
		ui->horizontalLayout_2->removeWidget(child->widget());
        delete child;
    }

    mediaplayer_2->setMedia(QUrl::fromLocalFile("D:/CCCC/Stop Motion/2015_05/range.avi"));
	ui->horizontalLayout_2->addWidget(videoWidget_2);
    mediaplayer_2->play();
}

void MainWindow::on_editCheckBox_clicked()
{
    if (isCut)
    {
        if (ui->editCheckBox->isChecked())
        {
            //frame_slider->setMouseTracking(true);
            //frame_slider->setCursor(Qt::PointingHandCursor);
            //frame_slider->installEventFilter(this);

			ui->scrollAreaWidgetContents_1->setAcceptDrops(true);
			ui->scrollAreaWidgetContents_2->setAcceptDrops(true);
			ui->scrollAreaWidgetContents_1->installEventFilter(this);
			ui->scrollAreaWidgetContents_2->installEventFilter(this);

			ui->actionSelect->setCheckable(true);
			ui->actionResume->setCheckable(true);
			ui->actionView->setCheckable(true);
			ui->actionSwap->setCheckable(true);
			ui->actionDelete->setCheckable(true);
			ui->actionReverse->setCheckable(true);
			ui->actionCast->setCheckable(true);
			ui->actionGroup->setCheckable(true);
			ui->actionUngroup->setCheckable(true);
			ui->actionSelectTrack->setCheckable(true);
			ui->actionAddTrack->setCheckable(true);
			ui->actionDeleteTrack->setCheckable(true);
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

			ui->actionSelect->setCheckable(false);
			ui->actionResume->setCheckable(false);
			ui->actionView->setCheckable(false);
			ui->actionSwap->setCheckable(false);
			ui->actionDelete->setCheckable(false);
			ui->actionReverse->setCheckable(false);
			ui->actionCast->setCheckable(false);
			ui->actionGroup->setCheckable(false);
			ui->actionUngroup->setCheckable(false);
			ui->actionSelectTrack->setCheckable(false);
			ui->actionAddTrack->setCheckable(false);
			ui->actionDeleteTrack->setCheckable(false);
			ui->actionViewTrack->setCheckable(false);
        }
    }
    else
    {
        statusBar()->showMessage("Please cut the video first.");
    }
}

void MainWindow::delete_action()
{
    //cout << "Delete from " << clickRange.x << " to " << clickRange.y << endl;
	action = DeleteClip;
	playRange();

	int end = clickRange.size() - 1;
    QString tip = "Delete from " + QString::number(clickRange.at(1)) + " to " + QString::number(clickRange.at(end));
    statusBar()->showMessage(tip);
}

void MainWindow::reverse_action()
{
    //cout << "Reverse from " << clickRange.x << " to " << clickRange.y << endl;
	action = ReverseClip;
	playRange();

	int end = clickRange.size() - 1;
    QString tip = "Reverse from " + QString::number(clickRange.at(1)) + " to " + QString::number(clickRange.at(end));
    statusBar()->showMessage(tip);
}

void MainWindow::show_context_menu()
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
}

void MainWindow::initFrameSlider()
{
	vector<int> sc = vproc.getSceneCuts();
	vector<int> ft = vproc.getCutTypes();
	frame_slider = new myslider(Qt::Horizontal, sc, ft);
}
