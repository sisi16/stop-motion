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

void cliplabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
		if (cut_type == 1)
			this->setStyleSheet("border: 5px inset rgb(0, 0, 255)");
		if (cut_type == 2)
			this->setStyleSheet("border: 5px inset rgb(0, 255, 0)");
		emit dblClicked();
    }
}

void cliplabel::enterEvent(QEvent *)
{
	if (cut_type == 1)
		this->setStyleSheet("border: 5px outset rgb(85, 170, 255)");
	if (cut_type == 2)
		this->setStyleSheet("border: 5px outset rgb(170, 255, 127)");
}

void cliplabel::leaveEvent(QEvent *)
{
	this->setStyleSheet("border: none");
}

