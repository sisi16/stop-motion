#include "myscrollarea.h"

myscrollarea::myscrollarea(QWidget *parent)
			: QScrollArea(parent)
{
	deleted = false;
	children_count = 0;
	
	this->setWidgetResizable(true);
	central_widget = new QWidget();
	central_widget->setGeometry(0, 0, 1200, 80);
	central_widget->setAcceptDrops(true);

	layout = new QGridLayout(central_widget);
	this->setWidget(central_widget);
	
}

myscrollarea::~myscrollarea()
{

}

void myscrollarea::setIsDeleted(bool isDeleted)
{
	deleted = isDeleted;
}

void myscrollarea::addChildrenCount()
{
	children_count++;
}

bool myscrollarea::getIsDeleted()
{
	return deleted;
}

QWidget *myscrollarea::getCentralWidget()
{
	return central_widget;
}

QGridLayout *myscrollarea::getLayout()
{
	return layout;
}

int myscrollarea::getChildrenCount()
{
	return children_count;
}