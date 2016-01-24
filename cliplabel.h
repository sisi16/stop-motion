#ifndef CLIPLABEL_H
#define CLIPLABEL_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QCursor>
#include <QWidget>

enum isEdited
{
	NotEdited,
	isSelected,
	isDeleted,
	isSelectedDeleted,
	isMoved,
	isViewed
	//isReversed,
};

class cliplabel : public QLabel
{
    Q_OBJECT

public:
    cliplabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
	cliplabel(std::vector<cv::Mat> src, int bw, int w, int h, int index, int type, int l, QWidget* parent = 0, Qt::WindowFlags f = 0);
    cliplabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~cliplabel();
	int getCutIndex();
	int getCutType();
	int getWidth();
	int getHeight();
	std::vector<cv::Mat> getSrcImages();
	isEdited getEditedMode();
	std::vector<int> getRange();
	bool getOriginMoving();
	void setEditedMode(isEdited mode);
	void setCutType(int type);
	void setCutIndex(int index);
	void setSrcImages(std::vector<cv::Mat> src);
	void setSizeThreshold(int w, int h);
	void setRange(std::vector<int> rng);
	void setOriginMoving(bool isMoving);
	void cast(cliplabel *castedClip);
	void uncast();
	//void zoomIn();
	//void zoomOut();

protected:
    void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

signals:
	void signalEntered(bool entered);

private:
	int w_threshold;
	int h_threshold;
	int cut_index;
	int cut_type;
	int length;
	std::vector<int> range;
	isEdited edited_mode;
	std::vector<cv::Mat> srcImages;
};

#endif // CLIPLABEL_H
