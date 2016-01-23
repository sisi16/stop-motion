#include "cliplabel.h"
#include <iostream>

using namespace std;
using namespace cv;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
	cut_index = -1;
	cut_type = -1;
	//track_index = -1;
	edited_mode = NotEdited;
}

cliplabel::cliplabel(vector<Mat> src, int bw, int w, int h, int index, int type, int l, QWidget* parent, Qt::WindowFlags f)
		 : QLabel(parent, f)
{
	w_threshold = w;
	h_threshold = h;
	srcImages = src;
	cut_index = index;
	cut_type = type;
	//track_index = type;
	length = l;
	edited_mode = NotEdited;

	this->setScaledContents(true);
	cv::Mat temp;
	QPixmap *pm = new QPixmap(w, h);
	//pixmap->fill(Qt::transparent);
	QPainter *painter = new QPainter(pm);

	for (int i = 0; i < length; i++)
	{
		if (cut_type == 1)
			cv::cvtColor(src.at(0), temp, CV_BGR2RGB);
		else
			cv::cvtColor(src.at(i), temp, CV_BGR2RGB);
		QImage image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image.bits();
		if (cut_type == 1)
		{
			if (i == 0)
				painter->drawPixmap(0, 0, bw, h, QPixmap::fromImage(image));
			else
			{
				QPixmap img = QPixmap::fromImage(image);
				painter->drawPixmap(bw+bw/10*(i-1), 0, bw / 10, h, img, img.width() / 10 * 9, 0, 0, 0);
			}
		}
		else
			painter->drawPixmap(i*bw, 0, bw, h, QPixmap::fromImage(image));
	}
	painter->end();
	this->setPixmap(*pm);
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

/*int cliplabel::getTrackIndex()
{
	return track_index;
}*/

int cliplabel::getWidth()
{
	return w_threshold;
}

int cliplabel::getHeight()
{
	return h_threshold;
}


vector<Mat> cliplabel::getSrcImages()
{
	return srcImages;
}

isEdited cliplabel::getEditedMode()
{
	return edited_mode;
}

vector<int> cliplabel::getRange()
{
	return range;
}

void cliplabel::enterEvent(QEvent *)
{
	if (edited_mode != isSelected && edited_mode != isMoved && edited_mode != isDeleted && edited_mode != isCasted)
	{
		if (cut_type == 1)
			this->setStyleSheet("border: 5px outset rgb(85, 170, 255)");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px outset rgb(170, 255, 127)");
		else if (cut_type > 2)
			this->setStyleSheet("border: 5px outset rgb(255, 255, 127)");
		//emit enter(cut_index);
	}
}

void cliplabel::leaveEvent(QEvent *)
{
	if (edited_mode != isSelected && edited_mode != isMoved && edited_mode != isDeleted && edited_mode != isCasted && cut_type != -1)
		this->setStyleSheet("border: none");
}

void cliplabel::setEditedMode(isEdited mode)
{
	edited_mode = mode;

	switch (mode)
	{
	case NotEdited:
		this->setStyleSheet("border: none");
		break;

	case isSelected:
		if (cut_type == 1)
			this->setStyleSheet("border: 5px inset blue");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px inset green");
		break;

	case isResumed:
		this->setStyleSheet("border: none");
		break;

	case isMoved:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isDeleted:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isSelectedDeleted:
		if (cut_type == 1)
			this->setStyleSheet("border: 5px dashed blue");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px dashed green");
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

/*void cliplabel::setTrackIndex(int index)
{
	track_index = index;
}*/

void cliplabel::setCutType(int type)
{
	cut_type = type;
}

void cliplabel::setSrcImages(vector<Mat> src)
{
	srcImages = src;
}

void cliplabel::cast(cliplabel *castedClip)
{
	this->setScaledContents(true);
	this->setPixmap(*castedClip->pixmap());
	w_threshold = castedClip->getWidth();
	h_threshold = castedClip->getHeight();
	cut_type = castedClip->getCutType();
	cut_index = castedClip->getCutIndex();
	if (castedClip->getEditedMode() == isSelectedDeleted)
		this->setEditedMode(isSelected);
	else if (castedClip->getEditedMode() == isSelected)
		this->setEditedMode(isSelectedDeleted);
	srcImages = castedClip->getSrcImages();
	range = castedClip->getRange();
	this->setMouseTracking(true);
	this->setCursor(Qt::PointingHandCursor);
}

void cliplabel::uncast()
{
	this->setPixmap(QPixmap(""));
	this->setScaledContents(false);
	this->setEditedMode(NotEdited);
	cut_index = -1;
	cut_type = -1;
	srcImages.clear();
	range.clear();
	this->setMouseTracking(false);
	this->setCursor(Qt::ArrowCursor);
}

void cliplabel::setSizeThreshold(int w, int h)
{
	w_threshold = w;
	h_threshold = h;
}

void cliplabel::setRange(vector<int> rng)
{
	range = rng;
}

/*void cliplabel::zoomIn()
{
	int w = this->width();
	int h = this->height();
	if (this->cut_index != -1)
	{
	QPixmap *pixmap = new QPixmap(2 * w, h);
	QPainter *painter = new QPainter(pixmap);
	if (2 * w > w_threshold)
	{
	painter->drawPixmap(0, 0, w, h, *this->pixmap());
	painter->fillRect(w, 0, w, h, Qt::black);
	}
	else
	painter->drawPixmap(0, 0, 2*w, h, *this->pixmap());
	painter->end();
	this->setPixmap(*pixmap);
	this->setFixedSize(2 * w, h);
	}
	else
	this->setFixedWidth(2 * w);
}*/

/*void cliplabel::zoomOut()
{
	int w = floor(0.5*this->width());
	int h = this->height();
	if (this->cut_index != -1)
	{
		if (this->width() > w_threshold && w <= w_threshold)
			this->setPixmap(*pm); //painter->drawPixmap(0, 0, w, h, *this->pixmap(), 0, 0, w, h);
		else
		{
			QPixmap *pixmap = new QPixmap(w, h);
			QPainter *painter = new QPainter(pixmap);
			painter->drawPixmap(0, 0, w, h, *this->pixmap(), 0, 0, w, h);
			painter->end();
			this->setPixmap(*pixmap);
		}
		this->setFixedSize(w, h);
	}
	else
		this->setFixedWidth(w);
}*/