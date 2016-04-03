/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionCandidates;
    QAction *actionTest;
    QAction *actionSet;
    QAction *actionSave;
    QAction *actionConfirm;
    QAction *actionDelete;
    QAction *actionResume;
    QAction *actionReverse;
    QAction *actionGroup;
    QAction *actionUngroup;
    QAction *actionItpl;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionSwap;
    QAction *actionView;
    QAction *actionCast;
    QAction *actionSelect;
    QAction *actionAddTrack;
    QAction *actionDeleteTrack;
    QAction *actionSelectTrack;
    QAction *actionViewTrack;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *frameLabel;
    QGridLayout *gridLayout_1;
    QFrame *line_3;
    QLabel *trackLabel;
    QLabel *clipLabel;
    QPushButton *playTrackButton;
    QFrame *line_4;
    QRadioButton *editRadioButton;
    QPushButton *playClipButton;
    QPushButton *nextButton;
    QPushButton *preButton;
    QPushButton *pauseButton;
    QFrame *line;
    QScrollArea *scrollArea_1;
    QWidget *scrollAreaWidgetContents_1;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_3;
    QFrame *line_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/icons/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon);
        actionCandidates = new QAction(MainWindow);
        actionCandidates->setObjectName(QStringLiteral("actionCandidates"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionSet = new QAction(MainWindow);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/icons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionConfirm = new QAction(MainWindow);
        actionConfirm->setObjectName(QStringLiteral("actionConfirm"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/icons/tick_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfirm->setIcon(icon3);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/icons/delete_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon4);
        actionResume = new QAction(MainWindow);
        actionResume->setObjectName(QStringLiteral("actionResume"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Images/icons/resume_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionResume->setIcon(icon5);
        actionReverse = new QAction(MainWindow);
        actionReverse->setObjectName(QStringLiteral("actionReverse"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Images/icons/reverse_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReverse->setIcon(icon6);
        actionGroup = new QAction(MainWindow);
        actionGroup->setObjectName(QStringLiteral("actionGroup"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Images/icons/group_48.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGroup->setIcon(icon7);
        actionUngroup = new QAction(MainWindow);
        actionUngroup->setObjectName(QStringLiteral("actionUngroup"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Images/icons/ungroup_48.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUngroup->setIcon(icon8);
        actionItpl = new QAction(MainWindow);
        actionItpl->setObjectName(QStringLiteral("actionItpl"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Images/icons/interpolation_48.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionItpl->setIcon(icon9);
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Images/icons/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon10);
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Images/icons/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon11);
        actionSwap = new QAction(MainWindow);
        actionSwap->setObjectName(QStringLiteral("actionSwap"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Images/icons/swap.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSwap->setIcon(icon12);
        actionView = new QAction(MainWindow);
        actionView->setObjectName(QStringLiteral("actionView"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Images/icons/play_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView->setIcon(icon13);
        actionCast = new QAction(MainWindow);
        actionCast->setObjectName(QStringLiteral("actionCast"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Images/icons/cast.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCast->setIcon(icon14);
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Images/icons/select-clip.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon15);
        actionAddTrack = new QAction(MainWindow);
        actionAddTrack->setObjectName(QStringLiteral("actionAddTrack"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Images/icons/add-track.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddTrack->setIcon(icon16);
        actionDeleteTrack = new QAction(MainWindow);
        actionDeleteTrack->setObjectName(QStringLiteral("actionDeleteTrack"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Images/icons/delete-track.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteTrack->setIcon(icon17);
        actionSelectTrack = new QAction(MainWindow);
        actionSelectTrack->setObjectName(QStringLiteral("actionSelectTrack"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Images/icons/select-track.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectTrack->setIcon(icon18);
        actionViewTrack = new QAction(MainWindow);
        actionViewTrack->setObjectName(QStringLiteral("actionViewTrack"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Images/icons/view-track.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionViewTrack->setIcon(icon19);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frameLabel = new QLabel(centralWidget);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        sizePolicy.setHeightForWidth(frameLabel->sizePolicy().hasHeightForWidth());
        frameLabel->setSizePolicy(sizePolicy);
        frameLabel->setStyleSheet(QLatin1String("background-color: rgb(130, 130, 130);\n"
"\n"
""));

        verticalLayout->addWidget(frameLabel);


        gridLayout->addLayout(verticalLayout, 0, 0, 2, 3);

        gridLayout_1 = new QGridLayout();
        gridLayout_1->setSpacing(6);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy1);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_1->addWidget(line_3, 3, 0, 1, 4);

        trackLabel = new QLabel(centralWidget);
        trackLabel->setObjectName(QStringLiteral("trackLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(trackLabel->sizePolicy().hasHeightForWidth());
        trackLabel->setSizePolicy(sizePolicy2);
        trackLabel->setStyleSheet(QLatin1String("font: 75 18pt \"Times New Roman\";\n"
"color: darkblue;"));

        gridLayout_1->addWidget(trackLabel, 1, 0, 1, 4);

        clipLabel = new QLabel(centralWidget);
        clipLabel->setObjectName(QStringLiteral("clipLabel"));
        sizePolicy2.setHeightForWidth(clipLabel->sizePolicy().hasHeightForWidth());
        clipLabel->setSizePolicy(sizePolicy2);
        clipLabel->setStyleSheet(QLatin1String("font: 75 18pt \"Times New Roman\";\n"
"color: darkblue;"));

        gridLayout_1->addWidget(clipLabel, 4, 0, 1, 4);

        playTrackButton = new QPushButton(centralWidget);
        playTrackButton->setObjectName(QStringLiteral("playTrackButton"));
        sizePolicy2.setHeightForWidth(playTrackButton->sizePolicy().hasHeightForWidth());
        playTrackButton->setSizePolicy(sizePolicy2);
        playTrackButton->setIcon(icon19);

        gridLayout_1->addWidget(playTrackButton, 2, 0, 1, 1);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        sizePolicy1.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy1);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_1->addWidget(line_4, 0, 0, 1, 4);

        editRadioButton = new QRadioButton(centralWidget);
        editRadioButton->setObjectName(QStringLiteral("editRadioButton"));
        sizePolicy2.setHeightForWidth(editRadioButton->sizePolicy().hasHeightForWidth());
        editRadioButton->setSizePolicy(sizePolicy2);
        editRadioButton->setStyleSheet(QStringLiteral("font: 75 12pt \"Times New Roman\";"));
        editRadioButton->setAutoExclusive(false);

        gridLayout_1->addWidget(editRadioButton, 5, 0, 1, 2);

        playClipButton = new QPushButton(centralWidget);
        playClipButton->setObjectName(QStringLiteral("playClipButton"));
        sizePolicy2.setHeightForWidth(playClipButton->sizePolicy().hasHeightForWidth());
        playClipButton->setSizePolicy(sizePolicy2);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/Images/icons/play_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        playClipButton->setIcon(icon20);
        playClipButton->setIconSize(QSize(20, 20));

        gridLayout_1->addWidget(playClipButton, 6, 0, 1, 1);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        sizePolicy2.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy2);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/Images/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon21);
        nextButton->setIconSize(QSize(20, 20));

        gridLayout_1->addWidget(nextButton, 6, 3, 1, 1);

        preButton = new QPushButton(centralWidget);
        preButton->setObjectName(QStringLiteral("preButton"));
        sizePolicy2.setHeightForWidth(preButton->sizePolicy().hasHeightForWidth());
        preButton->setSizePolicy(sizePolicy2);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/Images/icons/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        preButton->setIcon(icon22);
        preButton->setIconSize(QSize(20, 20));

        gridLayout_1->addWidget(preButton, 6, 2, 1, 1);

        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        sizePolicy2.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy2);
        pauseButton->setIcon(icon4);
        pauseButton->setIconSize(QSize(20, 20));

        gridLayout_1->addWidget(pauseButton, 6, 1, 1, 1);


        gridLayout->addLayout(gridLayout_1, 1, 4, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 5);

        scrollArea_1 = new QScrollArea(centralWidget);
        scrollArea_1->setObjectName(QStringLiteral("scrollArea_1"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollArea_1->sizePolicy().hasHeightForWidth());
        scrollArea_1->setSizePolicy(sizePolicy3);
        scrollArea_1->setFrameShape(QFrame::NoFrame);
        scrollArea_1->setWidgetResizable(true);
        scrollAreaWidgetContents_1 = new QWidget();
        scrollAreaWidgetContents_1->setObjectName(QStringLiteral("scrollAreaWidgetContents_1"));
        scrollAreaWidgetContents_1->setGeometry(QRect(0, 0, 1262, 153));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        scrollArea_1->setWidget(scrollAreaWidgetContents_1);

        gridLayout->addWidget(scrollArea_1, 11, 0, 1, 5);

        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        sizePolicy3.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy3);
        scrollArea_2->setFrameShape(QFrame::NoFrame);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1262, 152));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout->addWidget(scrollArea_2, 12, 0, 1, 5);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShadow(QFrame::Sunken);
        line_2->setFrameShape(QFrame::VLine);

        gridLayout->addWidget(line_2, 0, 3, 2, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionCandidates->setText(QApplication::translate("MainWindow", "Get Candidates", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
        actionSet->setText(QApplication::translate("MainWindow", "Set", 0));
#ifndef QT_NO_TOOLTIP
        actionSet->setToolTip(QApplication::translate("MainWindow", "Settings", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save", 0));
#endif // QT_NO_TOOLTIP
        actionConfirm->setText(QApplication::translate("MainWindow", "Confirm", 0));
#ifndef QT_NO_TOOLTIP
        actionConfirm->setToolTip(QApplication::translate("MainWindow", "Confirm", 0));
#endif // QT_NO_TOOLTIP
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindow", "Delete", 0));
#endif // QT_NO_TOOLTIP
        actionResume->setText(QApplication::translate("MainWindow", "Resume", 0));
#ifndef QT_NO_TOOLTIP
        actionResume->setToolTip(QApplication::translate("MainWindow", "Resume", 0));
#endif // QT_NO_TOOLTIP
        actionReverse->setText(QApplication::translate("MainWindow", "Reverse", 0));
#ifndef QT_NO_TOOLTIP
        actionReverse->setToolTip(QApplication::translate("MainWindow", "Reverse", 0));
#endif // QT_NO_TOOLTIP
        actionGroup->setText(QApplication::translate("MainWindow", "Group", 0));
#ifndef QT_NO_TOOLTIP
        actionGroup->setToolTip(QApplication::translate("MainWindow", "Group", 0));
#endif // QT_NO_TOOLTIP
        actionUngroup->setText(QApplication::translate("MainWindow", "Ungroup", 0));
#ifndef QT_NO_TOOLTIP
        actionUngroup->setToolTip(QApplication::translate("MainWindow", "Un-group", 0));
#endif // QT_NO_TOOLTIP
        actionItpl->setText(QApplication::translate("MainWindow", "Itpl", 0));
#ifndef QT_NO_TOOLTIP
        actionItpl->setToolTip(QApplication::translate("MainWindow", "Interpolate", 0));
#endif // QT_NO_TOOLTIP
        actionZoomIn->setText(QApplication::translate("MainWindow", "ZoomIn", 0));
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("MainWindow", "Zoom in", 0));
#endif // QT_NO_TOOLTIP
        actionZoomOut->setText(QApplication::translate("MainWindow", "ZoomOut", 0));
#ifndef QT_NO_TOOLTIP
        actionZoomOut->setToolTip(QApplication::translate("MainWindow", "Zoom out", 0));
#endif // QT_NO_TOOLTIP
        actionSwap->setText(QApplication::translate("MainWindow", "Swap", 0));
#ifndef QT_NO_TOOLTIP
        actionSwap->setToolTip(QApplication::translate("MainWindow", "Swap", 0));
#endif // QT_NO_TOOLTIP
        actionView->setText(QApplication::translate("MainWindow", "View", 0));
#ifndef QT_NO_TOOLTIP
        actionView->setToolTip(QApplication::translate("MainWindow", "View", 0));
#endif // QT_NO_TOOLTIP
        actionCast->setText(QApplication::translate("MainWindow", "Cast", 0));
#ifndef QT_NO_TOOLTIP
        actionCast->setToolTip(QApplication::translate("MainWindow", "Cast", 0));
#endif // QT_NO_TOOLTIP
        actionSelect->setText(QApplication::translate("MainWindow", "Select", 0));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("MainWindow", "Select", 0));
#endif // QT_NO_TOOLTIP
        actionAddTrack->setText(QApplication::translate("MainWindow", "AddTrack", 0));
#ifndef QT_NO_TOOLTIP
        actionAddTrack->setToolTip(QApplication::translate("MainWindow", "Add track", 0));
#endif // QT_NO_TOOLTIP
        actionDeleteTrack->setText(QApplication::translate("MainWindow", "DeleteTrack", 0));
#ifndef QT_NO_TOOLTIP
        actionDeleteTrack->setToolTip(QApplication::translate("MainWindow", "Delete track", 0));
#endif // QT_NO_TOOLTIP
        actionSelectTrack->setText(QApplication::translate("MainWindow", "SelectTrack", 0));
#ifndef QT_NO_TOOLTIP
        actionSelectTrack->setToolTip(QApplication::translate("MainWindow", "Select track", 0));
#endif // QT_NO_TOOLTIP
        actionViewTrack->setText(QApplication::translate("MainWindow", "viewTrack", 0));
#ifndef QT_NO_TOOLTIP
        actionViewTrack->setToolTip(QApplication::translate("MainWindow", "View track", 0));
#endif // QT_NO_TOOLTIP
        frameLabel->setText(QString());
        trackLabel->setText(QApplication::translate("MainWindow", "Track:", 0));
        clipLabel->setText(QApplication::translate("MainWindow", "Clip:", 0));
        playTrackButton->setText(QString());
        editRadioButton->setText(QApplication::translate("MainWindow", "Edit", 0));
        playClipButton->setText(QString());
        nextButton->setText(QString());
        preButton->setText(QString());
        pauseButton->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
