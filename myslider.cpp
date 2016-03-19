#include "myslider.h"
#include <iostream>

using namespace std;

myslider::myslider(Qt::Orientation orientation, QWidget *parent)
        : QSlider(orientation, parent)
{
	//highLightIndex = -1;
}

/*myslider::myslider(Qt::Orientation orientation, vector<int> idc, vector<int> ref, QWidget *parent)
        : QSlider(orientation, parent)
{
    indices = idc;
    reference = ref;
	highLightIndex = -1;
}*/

myslider::~myslider()
{
	if (!labels.empty())
		labels.clear();
}

void myslider::setEditMode(bool onOrOff)
{
	editModeOn = onOrOff;
}

void myslider::addLabel(int index)
{
	int size = labels.size();
	if (size == 0 || (size != 0 && labels[size - 1] != labels[size - 2]))
	{
		labels.push_back(index);
		labels.push_back(index);
		sort(labels.begin(), labels.end());
	}
	else
		labels[size-1] = index;
}

void myslider::deleteLabel(int index)
{
	for (int i = 0; i < labels.size(); i+=2)
		if (index >= labels[i] && index <= labels[i + 1])
		{
			labels.erase(labels.begin() + i);
			labels.erase(labels.begin() + i);
		}
	/*if (labels.size() == 1) labels.pop_back();
	else
	{
		for (int i = 0; i < labels.size(); i++)
			if (index == labels.at(i)) labels.erase(labels.begin() + i);//labels.at(i) = -1;
	}*/
}

void myslider::setLabels(std::vector<int> l)
{
	labels = l;
}

void myslider::clearLabels()
{
	if (!labels.empty())
		labels.clear();
}

void myslider::setCuts(std::vector<int> c)
{
	cuts = c;
}

void myslider::clearCuts()
{
	if (!cuts.empty())
		cuts.clear();
}

std::vector<int> *myslider::getLabeledIndices()
{
	return &labeledIndices;
}


/*void myslider::updateParams(std::vector<int> idc, std::vector<int> ref)
{
    indices = idc;
    reference = ref;
}*/

/*void myslider::highLight(int value)
{
	highLightIndex = value;
}*/

void myslider::paintEvent(QPaintEvent *ev)
{
	QSlider::paintEvent(ev);
	QPainter *painter = new QPainter(this);
	painter->setOpacity(0.5);
	if (editModeOn)
	{
		if (!labels.empty())
		{
			/*if (labels.size() % 2 != 0)
			{
				painter->setPen(QPen(Qt::blue, 8));
				for (int i = 0; i < labels.size(); i++)
				{
					int x = round((labels.at(i) - this->minimum())*this->width() / double(this->maximum() - this->minimum()));
					if (x == 0) painter->setPen(QPen(Qt::blue, 16));
					painter->drawLine(x, 0, x, this->height() / 2);
					if (x == 0) painter->setPen(QPen(Qt::blue, 8));
				}
			}*/
			//else
			//{
				painter->setPen(QPen(Qt::blue, 8));
				for (int i = 0; i < labels.size(); i += 2)
				{
					int x_1 = round((labels.at(i) - this->minimum())*this->width() / double(this->maximum() - this->minimum()));
					int x_2 = round((labels.at(i + 1) - this->minimum())*this->width() / double(this->maximum() - this->minimum()));
					if (x_1 == x_2) painter->drawLine(x_1, 0, x_1, this->height() / 2);
					else painter->fillRect(x_1, 0, x_2 - x_1, this->height() / 2, Qt::blue);
				}
			//}
		}

		if (!cuts.empty())
		{
			for (int i = 0; i < cuts.size(); i += 2)
			{
				int x_1 = round((cuts.at(i) - this->minimum())*this->width() / double(this->maximum() - this->minimum()));
				int x_2 = round((cuts.at(i + 1) - this->minimum())*this->width() / double(this->maximum() - this->minimum()));
				painter->fillRect(x_1, 0, x_2 - x_1, this->height() / 2, QColor(255, 165, 0));
			}

		}
	}
	else
	{
		painter->setPen(QPen(Qt::red, 8));
		for (int i = 0; i < labeledIndices.size(); i++)
		{
			if (labeledIndices.at(i) != -1)
			{
				int x = round(labeledIndices.at(i)*this->width() / double(this->maximum() - this->minimum()));
				if (x == 0) painter->setPen(QPen(Qt::red, 16));
				painter->drawLine(x, 0, x, this->height() / 2);
				if (x == 0) painter->setPen(QPen(Qt::red, 8));
			}
		}
	}
	painter->end();

    /*QStyleOptionSlider opt;
    initStyleOption(&opt);

    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderHandle;
    if (TickPosition() != NoTicks)
    {
        opt.subControls |= QStyle::SC_SliderTickmarks;
    }

    QRect groove_rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRect handle_rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    QSlider::paintEvent(ev);
    QPainter painter(this);

    if (!indices.empty() && !reference.empty())
    {
		double start, end;
		double size = double(indices.at(indices.size() - 1) + 1); //size = 4717;//size = 6284;//size = 597;//size = 930;//size = 155;//size = 1425;//size = 6472;//size = 150;//size = double(reference.size());
        for (int i = 0; i < indices.size(); i++)
        {
   			if (i == 0)
            {
                start = 0;
                end = (indices.at(i)+1)/size;
            }
            else
            {
                start = (indices.at(i-1)+1)/size;
                end = (indices.at(i)-indices.at(i-1))/size;
            }

            QRect rect(groove_rect.left()+start*groove_rect.width(), groove_rect.top(), end*groove_rect.width(), groove_rect.height());
			
			switch (reference.at(i))
            {
				case 1:
				{
					if (i != highLightIndex)
						painter.fillRect(rect, QBrush(Qt::darkBlue));
					else
						painter.fillRect(rect, QBrush(Qt::cyan));
					break;
				}
				case 2:
				{
					if (i != highLightIndex)
						painter.fillRect(rect, QBrush(Qt::darkGreen));
					else
						painter.fillRect(rect, QBrush(Qt::green));
					break;
				}
                case 3:
                    painter.fillRect(rect, QBrush(Qt::blue));
                    break;
                case 4:
                    painter.fillRect(rect, QBrush(Qt::green));
                    break;
            }
        }
    }
    painter.fillRect(handle_rect, QBrush(Qt::gray));*/
}
