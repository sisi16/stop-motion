#include "cliplabel.h"
#include <iostream>

using namespace std;

cliplabel::cliplabel(QWidget* parent, Qt::WindowFlags f)
         : QLabel(parent, f)
{
}

cliplabel::cliplabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
         : QLabel(text, parent, f)
{
}

cliplabel::~cliplabel()
{

}

void cliplabel::getMovingParent(QWidget *w)
{
    main_window = w;
}

void cliplabel::getMovingPixmap(QPixmap pm)
{
    cursor_pixmap = pm.scaled(QSize(100,100),  Qt::IgnoreAspectRatio);
}

void cliplabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        main_window->setCursor(QCursor(cursor_pixmap, -1, -1));
    }
}

void cliplabel::mousePressEvent(QMouseEvent *ev)
{
    /*if(ev->button() == Qt::LeftButton)
    {
        offset = ev->pos();
        cout << offset.x() << " " << offset.y() << endl;
    }*/
}

void cliplabel::mouseMoveEvent(QMouseEvent *ev)
{
    /*if (!(ev->buttons() & Qt::LeftButton))
        return;
    if ((ev->pos() - offset).manhattanLength() < QApplication::startDragDistance())
        return;
    if (ev->button() == Qt::LeftButton)
    {
        //setCursor(QCursor(QPixmap(":/icons/ungroup_48.png")));
        this->move(mapToGlobal(ev->pos() - offset));
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText("Clip 0");
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(":/Images/icons/ungroup_48.png"));
        drag->exec();
    }*/
}

