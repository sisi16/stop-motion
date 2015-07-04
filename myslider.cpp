#include "myslider.h"
#include <iostream>

using namespace std;

myslider::myslider(Qt::Orientation orientation, QWidget *parent)
        : QSlider(orientation, parent)
{
}

myslider::myslider(Qt::Orientation orientation, vector<int> idc, vector<int> ref, QWidget *parent)
        : QSlider(orientation, parent)
{
    indices = idc;
    reference = ref;
}

myslider::~myslider()
{
}

void myslider::updateParams(std::vector<int> idc, std::vector<int> ref)
{
    indices = idc;
    reference = ref;
}

void myslider::paintEvent(QPaintEvent *ev)
{
    QStyleOptionSlider opt;
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
        for (int i = 0; i < indices.size(); i++)
        {
            double start, end, size;

			size = 6472;//1425;//size = double(reference.size());
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

            switch (reference.at(indices.at(i)))
            {
                case 1:
                    painter.fillRect(rect, QBrush(Qt::red));
                    break;
                case 2:
                    painter.fillRect(rect, QBrush(Qt::yellow));
                    break;
                case 3:
                    painter.fillRect(rect, QBrush(Qt::blue));
                    break;
                case 4:
                    painter.fillRect(rect, QBrush(Qt::green));
                    break;
            }
        }
    }

    painter.fillRect(handle_rect, QBrush(Qt::gray));
}
