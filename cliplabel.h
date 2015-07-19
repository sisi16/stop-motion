#ifndef CLIPLABEL_H
#define CLIPLABEL_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QPixmap>
#include <QCursor>
#include <QWidget>

enum OperationSender
{
	FrameSlider,
	ClipLabel
};

class cliplabel : public QLabel
{
    Q_OBJECT

public:
    cliplabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
	cliplabel(cv::Mat src, int w, int h, int index, int type, QWidget* parent = 0, Qt::WindowFlags f = 0);
    cliplabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~cliplabel();
	void getMovingParent(QWidget* mp);
    void getMovingPixmap(QPixmap pm);
	int getCutIndex();
	int getCutType();
	void setIsResumed(bool state);
	void setIsMoved(bool isEdited);
	void setIsDeleted(bool isEdited);
	void setIsReversed(bool isEdited);

signals:
	void dblClicked();

protected:
    void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
	int cut_index;
	int cut_type;
	bool isResumed;
	bool isMoved;
	bool isDeleted;
	bool isReversed;
    QPoint offset;
    QWidget* moving_parent;
    QPixmap cursor_pixmap;
};

#endif // CLIPLABEL_H
