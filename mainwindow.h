#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QMenu>
#include <QPalette>
#include <QScrollBar>
#include <QMimeData>
#include <QDrag>
#include "videoprocessor.h"
#include "myslider.h"
#include "cliplabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void setClickRange(int index);

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

	void on_actionResume_triggered();

	void on_actionView_triggered();

	void on_actionSwap_triggered();

	void on_actionDelete_triggered();

	void on_actionReverse_triggered();

	void on_actionCast_triggered();

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
    cv::Point3i clickRange;
	clipOperation action;
    QMenu *sliderMenu;
};

#endif // MAINWINDOW_H
