#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>
#include <QPalette>
#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>
#include <QMimeData>
#include <QDrag>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "videoprocessor.h"
#include "myslider.h"
#include "cliplabel.h"
#include "myscrollarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	//void setClickRange(std::vector<int> indices);
	void refresh(int index);
	void visualizeClips();
	void setCurrentClip(cliplabel *clip);
	void cutVideo();
	void initFrameSlider();
	void drawScatterPlot();
	int round(double r);

protected:
	bool eventFilter(QObject *widget, QEvent *event);
	//void resizeEvent(QResizeEvent* ev);

private slots:

    void on_playClipButton_clicked();
	
	void on_preButton_clicked();
    
	void on_nextButton_clicked();

    void on_pauseButton_clicked();

	void on_playTrackButton_clicked();

    void seek(int index);

	void slotEntered(bool isEntered);

    void on_actionLoad_triggered();

	//void on_actionSelect_triggered();

	//void on_actionView_triggered();

	//void on_actionSwap_triggered();

	//void on_actionReverse_triggered();

	//void on_actionCast_triggered();

	//void on_actionZoomIn_triggered();

	//void on_actionZoomOut_triggered();

	//void on_actionSelectTrack_triggered();

	//void on_actionAddTrack_triggered();

	//void on_actionDeleteTrack_triggered();

	//void on_actionViewTrack_triggered();

    //void playRange();

	void on_editRadioButton_clicked();

	void on_keepRadioButton_clicked();

    //void reverse_action();

	void label_action();

	void delete_action();

	void show_context_menu();

private:
    //int resize_count;
    //int window_current_width;
    //int window_current_height;
	QString fileName;
    Ui::MainWindow *ui;
    videoprocessor vproc;
    myslider *frame_slider;
    QProgressBar *progressBar;
	cliplabel *current_clip = NULL;
	int current_clip_index = -1;
	int labelIndex = -1;
    bool isCut;
	bool entered;
    //std::vector<int> clickRange;
	//std::vector<int> movingRange;
	//clipOperation action;
    QMenu *sliderMenu = NULL;
	//std::vector<cliplabel *> selectedClips;
	std::vector<cliplabel *> clips;
	//int addedTrackCount;
	//std::vector<myscrollarea *> addedTrack;
	//std::vector<QScrollArea *> selectedTrack;
	//std::vector<QPoint> seletedPos;
};

#endif // MAINWINDOW_H
