#include "cliplabel.h"
#include <iostream>

using namespace std;
using namespace cv;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
	cut_index = -1;
	cut_type = -1;
	track_index = -1;
	group_from = -1;
	group_to = -1;
	edited_mode = NotEdited;
}

cliplabel::cliplabel(vector<Mat> src, int w, int h, int index, int type, QWidget* parent, Qt::WindowFlags f)
		 : QLabel(parent, f)
{
	w_threshold = w;
	h_threshold = h;
	srcImages = src;
	cut_index = index;
	cut_type = type;
	track_index = index;

	group_from = -1;
	group_to = -1;
	groupIndices.push_back(cut_index);
	edited_mode = NotEdited;

	this->setScaledContents(true);
	cv::Mat temp;
	QPixmap *pixmap = new QPixmap(w, h);
	//pixmap->fill(Qt::transparent);
	QPainter *painter = new QPainter(pixmap);

	int length = src.size();
	int base_width = w / length;
	for (int i = 0; i < length; i++)
	{
		cv::cvtColor(src.at(i), temp, CV_BGR2RGB);
		QImage image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image.bits();
		painter->drawPixmap(i*base_width, 0, base_width, h, QPixmap::fromImage(image));
	}
	painter->end();
	this->setPixmap(*pixmap);
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

int cliplabel::getTrackIndex()
{
	return track_index;
}

int cliplabel::getGroupFrom()
{
	return group_from;
}

int cliplabel::getGroupTo()
{
	return group_to;
}

vector<Mat> cliplabel::getSrcImages()
{
	return srcImages;
}

isEdited cliplabel::getEditedMode()
{
	return edited_mode;
}

vector<int> cliplabel::getGroupIndices()
{
	return groupIndices;
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
		else if (cut_type > 2)
			this->setStyleSheet("border: 5px inset yellow");
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

	case isCasted:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isGrouped:
		this->setStyleSheet("border: none");
		break;

	default:
		break;
	}
}

void cliplabel::setCutIndex(int index)
{
	cut_index = index;
}

void cliplabel::setTrackIndex(int index)
{
	track_index = index;
}

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

void cliplabel::setGroupIndex(int from, int to)
{
	group_from = from;
	group_to = to;
}

void cliplabel::setSizeThreshold(int w, int h)
{
	w_threshold = w;
	h_threshold = h;
}

void cliplabel::setGroupIndices(vector<int> indices)
{
	groupIndices = indices;
}

void cliplabel::setUnGroupIndices()
{
	groupIndices.clear();
	groupIndices.push_back(cut_index);
}

void cliplabel::clearGroupIndices()
{
	groupIndices.clear();
}

void cliplabel::zoomIn()
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
}

void cliplabel::zoomOut()
{
	int w = floor(0.5*this->width());
	int h = this->height();
	if (this->cut_index != -1)
	{
		QPixmap *pixmap = new QPixmap(w, h);
		QPainter *painter = new QPainter(pixmap);
		if (this->width() > w_threshold && w <= w_threshold)
			painter->drawPixmap(0, 0, w, h, *this->pixmap(), 0, 0, w, h);
		else
			painter->drawPixmap(0, 0, w, h, *this->pixmap());
		painter->end();
		this->setPixmap(*pixmap);
		this->setFixedSize(w, h);
	}
	else
		this->setFixedWidth(w);
}