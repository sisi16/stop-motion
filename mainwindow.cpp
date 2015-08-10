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

void MainWindow::setClickRange(int index, int groupFrom, int groupTo)
{
	if (!clickRange.empty()) clickRange.clear();
	if (groupFrom != -1 && groupTo != -1)
	{
		clickRange.push_back(index);
		for (int i = groupFrom; i <= groupTo; i+=2)
		{
			if (i == 0) clickRange.push_back(0);
			else clickRange.push_back(vproc.getSceneCuts().at(i-1) + 1);
			clickRange.push_back(vproc.getSceneCuts().at(i));
		}
	}
	else {
		clickRange.push_back(index);
		if (index == 0) clickRange.push_back(0);
		else clickRange.push_back(vproc.getSceneCuts().at(index-1) + 1);
		clickRange.push_back(vproc.getSceneCuts().at(index));
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

		frame_slider->setRange(0, 30000);//frame_slider->setRange(0, mediaplayer_1->duration() / 1000);
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
	
	for (int i = 0; i < vproc.getSceneCuts().size(); i++)
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
		cliplabel *empty_clip = new cliplabel();
		empty_clip->setFixedSize(width, height);

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
			setClickRange(item->getCutIndex(), item->getGroupFrom(), item->getGroupTo());
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
		if (selectedClip.size() == 1)
		{
			cliplabel *item = selectedClip.at(0);
			setClickRange(item->getCutIndex(), item->getGroupFrom(), item->getGroupTo());
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
			setClickRange(item->getCutIndex(), item->getGroupFrom(), item->getGroupTo());
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
		int index;
		int size = selectedClip.size();
		int start = selectedClip.at(0)->getCutIndex();
		int end = selectedClip.at(size - 1)->getCutIndex();
		if (selectedClip.at(0)->getCutType() == 1)
		{
			for (int i = 0; i < size; i++)
			{
				selectedClip.at(i)->setEditedMode(isGrouped);
				selectedClip.at(i)->setGroupIndex(start, end);
				if (i < size - 1)
				{
					index = selectedClip.at(i)->getCutIndex();
					ui->gridLayout_2->itemAt(index + 1)->widget()->setStyleSheet("image: url(:/Images/icons/connect.png);");
				}
			}
		} 
		else
		{
			for (int i = 0; i < size; i++)
			{
				selectedClip.at(i)->setEditedMode(isGrouped);
				selectedClip.at(i)->setGroupIndex(start, end);
				if (i < size - 1)
				{
					index = selectedClip.at(i)->getCutIndex();
					ui->gridLayout_3->itemAt(index + 1)->widget()->setStyleSheet("image: url(:/Images/icons/connect.png);");
				}
			}
		}
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

		int index;
		int start = selectedClip.at(0)->getGroupFrom();
		int end = selectedClip.at(0)->getGroupTo();

		if (selectedClip.at(0)->getCutType() == 1)
		{
			for (int i = start; i <= end; i+=2)
			{
				cliplabel* item = static_cast<cliplabel*>(ui->gridLayout_2->itemAt(i)->widget());
				item->setGroupIndex(-1, -1);
				if (i < end)
					ui->gridLayout_2->itemAt(i + 1)->widget()->setStyleSheet("image: none");
			}
		}
		else
		{
			for (int i = start; i <= end; i+=2)
			{
				cliplabel* item = static_cast<cliplabel*>(ui->gridLayout_3->itemAt(i)->widget());
				item->setGroupIndex(-1, -1);
				if (i < end)
					ui->gridLayout_3->itemAt(i + 1)->widget()->setStyleSheet("image: none");
			}
		}
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
		QScrollArea *scroll = new QScrollArea();
		ui->verticalLayout->addWidget(scroll);
		scroll->installEventFilter(this);
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
			QScrollArea *item = selectedTrack.at(i);
			item->setStyleSheet("border: none");
			item->removeEventFilter(this);
			item->hide();
		}
		ui->actionDeleteTrack->setChecked(false);
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

	else if (widget == ui->scrollAreaWidgetContents_1 || widget == ui->scrollAreaWidgetContents_2)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *m = (QMouseEvent*)event;

			if (m->button() == Qt::LeftButton)
			{
				cliplabel *item;
				if (widget == ui->scrollAreaWidgetContents_1)
					item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(m->pos()));
				else
					item = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(m->pos()));

				if (action == SelectClip)
				{
					item->setEditedMode(isSelected);
					selectedClip.push_back(item);
					seletedPos.push_back(m->pos());
				}

				else if (action == MoveClip)
				{
					QPixmap pixmap = *item->pixmap();
					QMimeData *mimeData = new QMimeData;
					QByteArray exData;
					QDataStream dataStream(&exData, QIODevice::WriteOnly);
					dataStream << pixmap << m->pos() << QPoint(m->pos() - item->pos());
					mimeData->setData("application/x-dnditemdata", exData);
					mimeData->setText(tr("Drag and Drop"));
					QDrag *drag;
					if (widget == ui->scrollAreaWidgetContents_1)
						drag = new QDrag(ui->scrollAreaWidgetContents_1);
					else
						drag = new QDrag(ui->scrollAreaWidgetContents_2);
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
				dataStream >> pixmap >> origin_pos >> pos;
				QLabel *item = new QLabel();
				item->setPixmap(pixmap);
				item->setAttribute(Qt::WA_DeleteOnClose);
				cliplabel *origin;
				if (widget == ui->scrollAreaWidgetContents_1)
					origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_1->childAt(origin_pos));
				else
					origin = static_cast<cliplabel*>(ui->scrollAreaWidgetContents_2->childAt(origin_pos));
				origin->setEditedMode(isMoved);
			}
			return true;
		}

		return true;
	}
	
	else if (addedTrackCount != 0 && event->type() == QEvent::MouseButtonPress)
	{
		for (int i = 0; i < addedTrackCount; i++)
		{
			QScrollArea *item = addedTrack.at(i);
			if (widget == item)
			{
				item->setStyleSheet("border: 5px inset orange");
				selectedTrack.push_back(item);
				return true;
			}
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
            frame_slider->setMouseTracking(true);
            frame_slider->setCursor(Qt::PointingHandCursor);
            frame_slider->installEventFilter(this);

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
        }
        else
        {
            frame_slider->setMouseTracking(false);
            frame_slider->setCursor(Qt::ArrowCursor);
            frame_slider->removeEventFilter(this);

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
