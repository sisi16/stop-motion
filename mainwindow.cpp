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
	ui->scrollArea_1->setBackgroundRole(QPalette::Midlight);
	ui->scrollArea_2->setBackgroundRole(QPalette::Mid);
	videoWidget_1 = new QVideoWidget;
	videoWidget_2 = new QVideoWidget;
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

void MainWindow::setClickRange(int index)
{
	if (index == 0) clickRange.x = 0;
	else clickRange.x = vproc.getSceneCuts().at(index-1) + 1;
	clickRange.y = vproc.getSceneCuts().at(index);
	clickRange.z = index;
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
		child = ui->gridLayout_1->takeAt(0);
		child->widget()->setVisible(0);
		ui->gridLayout_1->removeWidget(child->widget());
		delete child;

		frame_slider->setRange(0, mediaplayer_1->duration() / 1000);
		frame_slider->setValue(0);
		frame_slider->setTickPosition(QSlider::TicksAbove);
		frame_slider->setTickInterval(5);
		connect(frame_slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
		ui->gridLayout_1->addWidget(frame_slider);
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
    ui->gridLayout_1->addWidget(progressBar);
    progressBar->show();

	vproc.readBuffers();
	if (vproc.getSceneCuts().empty() || vproc.getCutTypes().empty())
		vproc.cut2Scenes();
	//vproc.writeBuffers();
	frame_slider->updateParams(vproc.getSceneCuts(), vproc.getCutTypes());
    isCut = true;
    statusBar()->clearMessage();

    progressBar->hide();
    ui->gridLayout_1->removeWidget(progressBar);
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
    if ((child = ui->gridLayout_1->takeAt(1)) != 0)
    {
        child->widget()->setVisible(0);
        ui->gridLayout_1->removeWidget(child->widget());
        delete child;
    }
    ui->gridLayout_1->addWidget(current_frame);
}

void MainWindow::seek(int seconds)
{
    mediaplayer_1->setPosition(seconds * 1000);
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
        while ((child = ui->gridLayout_1->takeAt(0)) != 0)  {
            child->widget()->setVisible(0);
            ui->gridLayout_1->removeWidget(child->widget());
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
            ui->gridLayout_1->addWidget(label, i/10, i%10, 0);
        }
    }
}

void MainWindow::on_actionTest_triggered()
{
	vector<int> scene_cuts = vproc.getSceneCuts();
	vector<int> cut_types = vproc.getCutTypes();
	int height = ui->scrollArea_1->height();
	int width;
	int index;
	
	for (int i = 0; i < vproc.getSceneCuts().size(); i++)
	{
		if (i == 0)
		{
			index = scene_cuts.at(0) / 2;
			width = floor(height * 0.02 * (scene_cuts.at(0)+1));
		}
		else
		{
			index = (scene_cuts.at(i - 1) + 1 + scene_cuts.at(i)) / 2;
			width = floor(height * 0.02 * (scene_cuts.at(i)-scene_cuts.at(i-1)));
		}
		cliplabel *clip = new cliplabel(vproc.getFrames().at(index), width, height, i, cut_types.at(i));
		QLabel *empty_clip = new QLabel();
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

		connect(clip, SIGNAL(clicked()), this, SLOT(playRange()));
		//this->setAcceptDrops(true);
		//clip_0->getMovingParent(this);
		//clip_0->getMovingPixmap(QPixmap::fromImage(image));
	}

	connect(ui->scrollArea_1->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_2->horizontalScrollBar(), SLOT(setValue(int)));
	connect(ui->scrollArea_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->scrollArea_1->horizontalScrollBar(), SLOT(setValue(int)));
}

bool MainWindow::eventFilter(QObject *widget, QEvent *event)
{
    if (widget != frame_slider) return false;

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *m = (QMouseEvent*)event;
        QString tip = "position: (" + QString::number(m->x()) + ", " + QString::number(m->y()) + ")";
        statusBar()->showMessage(tip);
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

	if (sender() != frame_slider)
	{
		cliplabel* clip = dynamic_cast<cliplabel*>(sender());
		setClickRange(clip->getCutIndex());
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
        }
        else
        {
            frame_slider->setMouseTracking(false);
            frame_slider->setCursor(Qt::ArrowCursor);
            frame_slider->removeEventFilter(this);
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

    QString tip = "Delete from " + QString::number(clickRange.x) + " to " + QString::number(clickRange.y);
    statusBar()->showMessage(tip);
}

void MainWindow::reverse_action()
{
    //cout << "Reverse from " << clickRange.x << " to " << clickRange.y << endl;
	action = ReverseClip;
	playRange();

    QString tip = "Reverse from " + QString::number(clickRange.x) + " to " + QString::number(clickRange.y);
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
