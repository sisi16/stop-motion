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

enum isEdited
{
	NotEdited,
	isMoved,
	isDeleted,
	isResumed,
	isReversed,
	isCasted
};

class cliplabel : public QLabel
{
    Q_OBJECT

public:
    cliplabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
	cliplabel(cv::Mat src, int w, int h, int index, int type, QWidget* parent = 0, Qt::WindowFlags f = 0);
    cliplabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~cliplabel();
	int getCutIndex();
	int getCutType();
	cv::Mat getSrcImage();
	isEdited getEditedMode();
	void setEditedMode(isEdited mode);
	void setCutType(int type);
	void setCutIndex(int index);
	void setSrcImage(cv::Mat src);
	void cast(cliplabel *castedClip);
	void uncast();

signals:
	void enter(int value);

protected:
    void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
	int cut_index;
	int cut_type;
	isEdited edited_mode;
	cv::Mat srcImage;
};

#endif // CLIPLABEL_H
