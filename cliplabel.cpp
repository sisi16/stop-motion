#include "cliplabel.h"
#include <iostream>

using namespace std;
using namespace cv;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
	cut_index = -1;
	cut_type = -1;
	sorted = false;
	edited_mode = NotEdited;
	this->setScaledContents(true);
	this->setMouseTracking(false);
	this->setCursor(Qt::ArrowCursor);
}

cliplabel::cliplabel(vector<Mat> src, int bw, int w, int h, int index, int type, int l, QWidget* parent, Qt::WindowFlags f)
		 : QLabel(parent, f)
{
	w_base = bw;
	w_threshold = w;
	h_threshold = h;
	srcImages = src;
	cut_index = index;
	cut_type = type;
	length = l;
	sorted = false;
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
				int x = bw + bw / 10 * (i - 1);
				painter->drawPixmap(x, 0, bw / 10, h, img, img.width() / 10 * 9, 0, 0, 0);
				painter->drawLine(x, 0, x, h);
			}
		}
		else
			painter->drawPixmap(i*bw, 0, bw, h, QPixmap::fromImage(image));
	}
	painter->drawRect(0, 0, pm->width()-1, pm->height()-1);
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

vector<int> cliplabel::getCuts()
{
	if (!sorted)
	{
		sort(cuts.begin(), cuts.end());
		sorted = true;
	}
	return cuts;
}

vector<int> cliplabel::getAutoCuts()
{
	return autoCuts;
}

bool cliplabel::isSorted()
{
	return sorted;
}

void cliplabel::enterEvent(QEvent *)
{
	if (edited_mode != isSelected && edited_mode != isSelectedDeleted && edited_mode != isDeleted && edited_mode != isViewed)
	{
		if (cut_type == 1)
			this->setStyleSheet("border: 5px outset rgb(85, 170, 255)");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px outset rgb(170, 255, 127)");
		else if (cut_type > 2)
			this->setStyleSheet("border: 5px outset rgb(255, 255, 127)");
	}
	//emit signalEntered(true);
}

void cliplabel::leaveEvent(QEvent *)
{
	if (edited_mode != isSelected && edited_mode != isSelectedDeleted && edited_mode != isDeleted && edited_mode != isViewed)
		this->setStyleSheet("border: none");
	//emit signalEntered(false);
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

	case isDeleted: //3px
		this->setStyleSheet("border: 5px dashed rgb(0, 0, 0)");
		break;

	case isSelectedDeleted:
		if (cut_type == 1)
			this->setStyleSheet("border: 5px dashed blue");
		else if (cut_type == 2)
			this->setStyleSheet("border: 5px dashed green");
		break;

	case isMoved:
		this->setStyleSheet("border: 3px dashed rgb(0, 0, 0)");
		break;

	case isViewed:
		this->setStyleSheet("border: 5px inset orange");
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

void cliplabel::setSrcImages(vector<Mat> src)
{
	srcImages = src;
}

void cliplabel::cast(cliplabel *castedClip)
{
	//this->setScaledContents(true);
	this->setPixmap(*castedClip->pixmap());
	cut_type = castedClip->getCutType();
	cut_index = castedClip->getCutIndex();
	sorted = castedClip->isSorted();
	if (castedClip->getEditedMode() == isSelectedDeleted)
		this->setEditedMode(isSelected);
	else if (castedClip->getEditedMode() == isSelected)
		this->setEditedMode(isSelectedDeleted);
	srcImages = castedClip->getSrcImages();
	range = castedClip->getRange();
	cuts = castedClip->getCuts();
	this->setMouseTracking(true);
	this->setCursor(Qt::PointingHandCursor);
}

void cliplabel::uncast()
{
	this->setPixmap(QPixmap(""));
	//this->setScaledContents(false);
	this->setEditedMode(NotEdited);
	cut_index = -1;
	cut_type = -1;
	sorted = false;
	srcImages.clear();
	range.clear();
	this->setMouseTracking(false);
	this->setCursor(Qt::ArrowCursor);
}

void cliplabel::updatePixmap(QString file)
{
	if (!cuts.empty() && !sorted)
	{
		srcImages.clear();

		stringstream ss;
		string type = ".jpg";
		Mat frame;
		for (size_t i = 0; i < cuts.size(); i++)
		{
			if (i % 2 == 1 && cuts[i-1] == cuts[i])
				continue;
			else
				ss << cuts[i] << type;
			if (file == "D:/CCCC/Stop Motion/Videos/Test7.avi") frame = imread("D:/CCCC/Stop Motion/Test7/270/" + ss.str());
			else if (file == "D:/CCCC/Stop Motion/Videos/Test8.avi") frame = imread("D:/CCCC/Stop Motion/Test8/270/" + ss.str());
			ss.str("");

			srcImages.push_back(frame);
		}

		paintPixmap();
	}
}

void cliplabel::paintPixmap()
{
	length = srcImages.size();
	w_threshold = length * w_base;
	QPixmap *pm = new QPixmap(w_threshold, h_threshold);
	QPainter *painter = new QPainter(pm);
	Mat temp;

	for (int i = 0; i < length; i++)
	{
		cv::cvtColor(srcImages[i], temp, CV_BGR2RGB);
		QImage image((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		image.bits();
		painter->drawPixmap(i*w_base, 0, w_base, h_threshold, QPixmap::fromImage(image));
	}
	painter->drawRect(0, 0, w_threshold - 1, h_threshold - 1);
	painter->end();
	this->setPixmap(*pm);
	this->setFixedSize(w_threshold, h_threshold);
	this->repaint();
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

void cliplabel::addCut(int index)
{
	int size = cuts.size();
	if (size == 0 || (size != 0 && cuts[size - 1] != cuts[size - 2]))
	{
		cuts.push_back(index);
		cuts.push_back(index);
	}
	else
		cuts[size - 1] = index;
	sorted = false;
}

void cliplabel::deleteCut(int index)
{
	for (int i = 0; i < cuts.size(); i+=2)
		if (index >= cuts[i] && index <= cuts[i + 1])
		{
			cuts.erase(cuts.begin() + i);
			cuts.erase(cuts.begin() + i);
		}
	/*if (cuts.size() == 1) cuts.pop_back();
	else
	{
		for (int i = 0; i < cuts.size(); i++)
			if (index == cuts.at(i)) cuts.erase(cuts.begin() + i);
	}*/
	sorted = false;
}

void cliplabel::setAutoCuts(vector<int> acs)
{
	autoCuts = acs;
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