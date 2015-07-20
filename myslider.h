#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include <QStyleOptionSlider>
#include <QDebug>
#include <QPainter>

class myslider : public QSlider
{
	Q_OBJECT

public:
    myslider(Qt::Orientation orientation, QWidget *parent = 0);
    myslider(Qt::Orientation orientation, std::vector<int> idc, std::vector<int> ref, QWidget *parent = 0);
    void updateParams(std::vector<int> idc, std::vector<int> ref);
    ~myslider();

public slots:
	void highLight(int value);

protected:
    void paintEvent(QPaintEvent *ev);

private:
	int highLightIndex;
    std::vector<int> indices;
    std::vector<int> reference;
};

#endif // MYSLIDER_H
