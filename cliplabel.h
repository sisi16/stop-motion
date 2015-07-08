#ifndef CLIPLABEL_H
#define CLIPLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QPixmap>
#include <QCursor>
#include <QWidget>

class cliplabel : public QLabel
{
    Q_OBJECT

public:
    cliplabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
    cliplabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    void getMovingParent(QWidget* w);
    void getMovingPixmap(QPixmap pm);
    ~cliplabel();

protected:
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    QPoint offset;
    QWidget* main_window;
    QPixmap cursor_pixmap;
};

#endif // CLIPLABEL_H