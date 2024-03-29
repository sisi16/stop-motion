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
    //myslider(Qt::Orientation orientation, std::vector<int> idc, std::vector<int> ref, QWidget *parent = 0);
    //void updateParams(std::vector<int> idc, std::vector<int> ref);
    ~myslider();
	void setEditMode(bool onOrOff);
	void addLabel(int index);
	void deleteLabel(int index);
	void setLabels(std::vector<int> l);
	void clearLabels();
	void setCuts(std::vector<int> c);
	void clearCuts();
	std::vector<int> *getLabeledIndices();

public slots:
	//void highLight(int value);

protected:
    void paintEvent(QPaintEvent *ev);

private:
	bool editModeOn = false;
	std::vector<int> labels;
	std::vector<int> labeledIndices;
	std::vector<int> cuts;
	//int highLightIndex;
    //std::vector<int> indices;
    //std::vector<int> reference;
};

#endif // MYSLIDER_H
