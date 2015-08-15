#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>

class myscrollarea : public QScrollArea
{
    Q_OBJECT

public:
    myscrollarea(QWidget *parent = 0);
    ~myscrollarea();
	void setIsDeleted(bool isDeleted);
	void addChildrenCount();
	bool getIsDeleted();
	QWidget *getCentralWidget();
	QGridLayout *getLayout();
	int getChildrenCount();

private:
	bool deleted;
	QWidget *central_widget;
	QGridLayout *layout;
	int children_count;
};

#endif // MYSCROLLAREA_H
