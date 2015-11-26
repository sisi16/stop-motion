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
	void setClickRange(std::vector<int> indices);

protected:
	void resizeEvent(QResizeEvent* ev);

private slots:

    void on_playButton1_clicked();

    void on_stopButton1_clicked();

    void on_pauseButton1_clicked();

    void on_cutButton_clicked();

	void on_okButton_clicked();

    void refresh(int value);

    void seek(int seconds);

    void on_actionLoad_triggered();

    void on_actionCandidates_triggered();

    void on_actionTest_triggered();

	void on_actionSelect_triggered();

	void on_actionResume_triggered();

	void on_actionView_triggered();

	void on_actionSwap_triggered();

	void on_actionDelete_triggered();

	void on_actionReverse_triggered();

	void on_actionCast_triggered();

	void on_actionGroup_triggered();

	void on_actionUngroup_triggered();

	void on_actionZoomIn_triggered();

	void on_actionZoomOut_triggered();

	void on_actionSelectTrack_triggered();

	void on_actionAddTrack_triggered();

	void on_actionDeleteTrack_triggered();

	void on_actionViewTrack_triggered();

	void on_actionItpl_triggered();

    bool eventFilter(QObject *widget, QEvent *event);

    void playRange();

    void on_editCheckBox_clicked();

    void delete_action();

    void reverse_action();

    void show_context_menu();

	void initFrameSlider();

private:
    int resize_count;
    int window_current_width;
    int window_current_height;
	QString fileName;
    Ui::MainWindow *ui;
    videoprocessor vproc;
    QMediaPlayer *mediaplayer_1;
    QMediaPlayer *mediaplayer_2;
    QVideoWidget *videoWidget_1;
    QVideoWidget *videoWidget_2;
    myslider *frame_slider;
    QProgressBar *progressBar;
    QLabel *preview_1;
    QLabel *preview_2;
    bool isCut;
    std::vector<int> clickRange;
	std::vector<bool> movingRange;
	clipOperation action;
    QMenu *sliderMenu;
	std::vector<cliplabel *> selectedClip;
	std::vector<cliplabel *> stableClip;
	std::vector<cliplabel *> movingClip;
	int addedTrackCount;
	std::vector<myscrollarea *> addedTrack;
	std::vector<QScrollArea *> selectedTrack;
	std::vector<QPoint> seletedPos;
};

#endif // MAINWINDOW_H
