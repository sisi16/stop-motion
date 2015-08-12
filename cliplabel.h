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
	isMoved,
	isDeleted,
	isResumed,
	isReversed,
	isCasted,
	isGrouped
};

class cliplabel : public QLabel
{
    Q_OBJECT

public:
    cliplabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
	cliplabel(std::vector<cv::Mat> src, int w, int h, int index, int type, QWidget* parent = 0, Qt::WindowFlags f = 0);
    cliplabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~cliplabel();
	int getCutIndex();
	int getCutType();
	int getTrackIndex();
	int getGroupFrom();
	int getGroupTo();
	std::vector<cv::Mat> getSrcImages();
	isEdited getEditedMode();
	std::vector<int> getGroupIndices();
	void setEditedMode(isEdited mode);
	void setCutType(int type);
	void setCutIndex(int index);
	void setTrackIndex(int index);
	void setSrcImages(std::vector<cv::Mat> src);
	void setGroupIndex(int from, int to);
	void setSizeThreshold(int w, int h);
	void setUnGroupIndices();
	void setGroupIndices(std::vector<int> indices);
	void clearGroupIndices();
	void cast(cliplabel *castedClip);
	void uncast();
	void zoomIn();
	void zoomOut();

signals:
	void enter(int value);

protected:
    void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
	int w_threshold;
	int h_threshold;
	int cut_index;
	int cut_type;
	int track_index;
	int group_from;
	int group_to;
	std::vector<int> groupIndices;
	isEdited edited_mode;
	std::vector<cv::Mat> srcImages;
};

#endif // CLIPLABEL_H
