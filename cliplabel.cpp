#include "cliplabel.h"
#include <iostream>

using namespace std;
using namespace cv;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
}

cliplabel::cliplabel(Mat src, int w, int h, int index, int type, QWidget* parent, Qt::WindowFlags f)
		 : QLabel(parent, f)
{
	cut_index = index;
	cut_type = type;

	isResumed = false;
	isMoved = false;
	isDeleted = false;
	isReversed = false;

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

void cliplabel::getMovingParent(QWidget *mp)
{
    moving_parent = mp;
}

void cliplabel::getMovingPixmap(QPixmap pm)
{
    cursor_pixmap = pm.scaled(QSize(100,100),  Qt::IgnoreAspectRatio);
}

int cliplabel::getCutIndex()
{
	return cut_index;
}

int cliplabel::getCutType()
{
	return cut_type;
}

void cliplabel::enterEvent(QEvent *)
{
	if (!isMoved && !isDeleted)
	{
		if (cut_type == 1)
			this->setStyleSheet("border: 5px outset rgb(85, 170, 255)");
		if (cut_type == 2)
			this->setStyleSheet("border: 5px outset rgb(170, 255, 127)");
	}
}

void cliplabel::leaveEvent(QEvent *)
{
	if (!isMoved && !isDeleted)
		this->setStyleSheet("border: none");
}

void cliplabel::setIsResumed(bool state)
{
	isResumed = state;
	if (isMoved) isMoved = false;
	else if (isDeleted) isDeleted = false;
	this->setStyleSheet("border: none");
}

void cliplabel::setIsMoved(bool isEdited)
{
	isMoved = isEdited;
	this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
}

void cliplabel::setIsDeleted(bool isEdited)
{
	isDeleted = isEdited;
	this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
}

void cliplabel::setIsReversed(bool isEdited)
{
	isReversed = isEdited;
}