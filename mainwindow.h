#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QMenu>
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

    bool eventFilter(QObject *widget, QEvent *event);

    void playRange();

    void on_editCheckBox_clicked();

    void delete_action();

    void reverse_action();

    void show_context_menu();

private:
    int resize_count;
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
