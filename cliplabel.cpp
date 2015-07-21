#include "cliplabel.h"
#include <iostream>

using namespace std;
using namespace cv;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
	cut_index = -1;
	cut_type = -1;
	edited_mode = NotEdited;
}

cliplabel::cliplabel(Mat src, int w, int h, int index, int type, QWidget* parent, Qt::WindowFlags f)
		 : QLabel(parent, f)
{
	srcImage = src;
	cut_index = index;
	cut_type = type;

	edited_mode = NotEdited;

	this->setScaledContents(true);
	cv::Mat temp;
	cv::cvtColor(src, temp, CV_BGR2RGB);
	QImage image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	image.bits();
	this->setPixmap(QPixmap::fromImage(image));
	this->setFixedSize(w, h);

	this->setMouseTracking(true);
	this->setCursor(Qt::PointingHandCursor);
}

cliplabel::cliplabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
         : QLabel(text, parent, f)
{
}

cliplabel::~cliplabel()
{

}

int cliplabel::getCutIndex()
{
	return cut_index;
}

int cliplabel::getCutType()
{
	return cut_type;
}

Mat cliplabel::getSrcImage()
{
	return srcImage;
}

isEdited cliplabel::getEditedMode()
{
	return edited_mode;
}

void cliplabel::enterEvent(QEvent *)
{
	if (edited_mode != isMoved && edited_mode != isDeleted && edited_mode != isCasted)
	{
		if (cut_type == 1)
			this->setStyleSheet("border: 5px outset rgb(85, 170, 255)");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px outset rgb(170, 255, 127)");
		//emit enter(cut_index);
	}
}

void cliplabel::leaveEvent(QEvent *)
{
	if (edited_mode != isMoved && edited_mode != isDeleted && edited_mode != isCasted)
		this->setStyleSheet("border: none");
}

void cliplabel::setEditedMode(isEdited mode)
{
	edited_mode = mode;

	switch (mode)
	{
	case isResumed:
		this->setStyleSheet("border: none");
		break;

	case isMoved:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isDeleted:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isCasted:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	default:
		break;
	}
}

void cliplabel::setCutIndex(int index)
{
	cut_index = index;
}

void cliplabel::setCutType(int type)
{
	cut_type = type;
}

void cliplabel::setSrcImage(Mat src)
{
	srcImage = src;
}

void cliplabel::cast(cliplabel *castedClip)
{
	this->setScaledContents(true);
	this->setPixmap(*castedClip->pixmap());
	edited_mode = NotEdited;
	cut_index = castedClip->getCutIndex();
	if (cut_type == 1) cut_type = 2;
	else cut_type = 1;
	this->setMouseTracking(true);
	this->setCursor(Qt::PointingHandCursor);
}

void cliplabel::uncast()
{
	this->setPixmap(QPixmap(""));
	this->setScaledContents(false);
	edited_mode = NotEdited;
	cut_index = -1;
	cut_type = -1;
	this->setMouseTracking(false);
	this->setCursor(Qt::ArrowCursor);
}