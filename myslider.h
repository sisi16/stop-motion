#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include <QStyleOptionSlider>
#include <QDebug>
#include <QPainter>

class myslider : public QSlider
{
public:
    myslider(Qt::Orientation orientation, QWidget *parent = 0);
    myslider(Qt::Orientation orientation, std::vector<int> idc, std::vector<int> ref, QWidget *parent = 0);
    void updateParams(std::vector<int> idc, std::vector<int> ref);
    ~myslider();

protected:
    void paintEvent(QPaintEvent *ev);

private:
    std::vector<int> indices;
    std::vector<int> reference;
};

#endif // MYSLIDER_H
