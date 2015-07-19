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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_1;
    QSlider *timeLineSlider;
    QScrollArea *scrollArea_1;
    QWidget *scrollAreaWidgetContents_1;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_3;
    QFrame *line_1;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cutButton;
    QPushButton *playButton1;
    QPushButton *pauseButton1;
    QPushButton *stopButton1;
    QCheckBox *editCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *bgLabel_2;
    QHBoxLayout *horizontalLayout_1;
    QLabel *bgLabel_1;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_1 = new QGridLayout();
        gridLayout_1->setSpacing(6);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
        timeLineSlider = new QSlider(centralWidget);
        timeLineSlider->setObjectName(QStringLiteral("timeLineSlider"));
        timeLineSlider->setOrientation(Qt::Horizontal);

        gridLayout_1->addWidget(timeLineSlider, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_1, 11, 1, 1, 5);

        scrollArea_1 = new QScrollArea(centralWidget);
        scrollArea_1->setObjectName(QStringLiteral("scrollArea_1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea_1->sizePolicy().hasHeightForWidth());
        scrollArea_1->setSizePolicy(sizePolicy1);
        scrollArea_1->setFrameShape(QFrame::NoFrame);
        scrollArea_1->setWidgetResizable(true);
        scrollAreaWidgetContents_1 = new QWidget();
        scrollAreaWidgetContents_1->setObjectName(QStringLiteral("scrollAreaWidgetContents_1"));
        scrollAreaWidgetContents_1->setGeometry(QRect(0, 0, 1262, 104));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        scrollArea_1->setWidget(scrollAreaWidgetContents_1);

        gridLayout->addWidget(scrollArea_1, 12, 1, 1, 5);

        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        sizePolicy1.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy1);
        scrollArea_2->setFrameShape(QFrame::NoFrame);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1262, 103));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout->addWidget(scrollArea_2, 13, 1, 1, 5);

        line_1 = new QFrame(centralWidget);
        line_1->setObjectName(QStringLiteral("line_1"));
        line_1->setFrameShape(QFrame::HLine);
        line_1->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_1, 8, 1, 1, 5);

        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy2);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Images/icons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon13);
        cancelButton->setIconSize(QSize(20, 20));

        gridLayout->addWidget(cancelButton, 5, 4, 1, 1);

        okButton = new QPushButton(centralWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        sizePolicy2.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy2);
        okButton->setStyleSheet(QStringLiteral(""));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Images/icons/tick.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon14);
        okButton->setIconSize(QSize(20, 20));

        gridLayout->addWidget(okButton, 5, 3, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cutButton = new QPushButton(centralWidget);
        cutButton->setObjectName(QStringLiteral("cutButton"));
        sizePolicy2.setHeightForWidth(cutButton->sizePolicy().hasHeightForWidth());
        cutButton->setSizePolicy(sizePolicy2);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Images/icons/cut_32.png"), QSize(), QIcon::Normal, QIcon::Off);
        cutButton->setIcon(icon15);
        cutButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(cutButton);

        playButton1 = new QPushButton(centralWidget);
        playButton1->setObjectName(QStringLiteral("playButton1"));
        sizePolicy2.setHeightForWidth(playButton1->sizePolicy().hasHeightForWidth());
        playButton1->setSizePolicy(sizePolicy2);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Images/icons/play_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton1->setIcon(icon16);
        playButton1->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(playButton1);

        pauseButton1 = new QPushButton(centralWidget);
        pauseButton1->setObjectName(QStringLiteral("pauseButton1"));
        sizePolicy2.setHeightForWidth(pauseButton1->sizePolicy().hasHeightForWidth());
        pauseButton1->setSizePolicy(sizePolicy2);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Images/icons/pause_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton1->setIcon(icon17);
        pauseButton1->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pauseButton1);

        stopButton1 = new QPushButton(centralWidget);
        stopButton1->setObjectName(QStringLiteral("stopButton1"));
        sizePolicy2.setHeightForWidth(stopButton1->sizePolicy().hasHeightForWidth());
        stopButton1->setSizePolicy(sizePolicy2);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Images/icons/stop_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton1->setIcon(icon18);
        stopButton1->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(stopButton1);


        gridLayout->addLayout(horizontalLayout_3, 5, 1, 1, 1);

        editCheckBox = new QCheckBox(centralWidget);
        editCheckBox->setObjectName(QStringLiteral("editCheckBox"));
        sizePolicy2.setHeightForWidth(editCheckBox->sizePolicy().hasHeightForWidth());
        editCheckBox->setSizePolicy(sizePolicy2);
        editCheckBox->setStyleSheet(QStringLiteral("font: 75 12pt \"Times New Roman\";"));

        gridLayout->addWidget(editCheckBox, 10, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        bgLabel_2 = new QLabel(centralWidget);
        bgLabel_2->setObjectName(QStringLiteral("bgLabel_2"));
        bgLabel_2->setStyleSheet(QLatin1String("background-color: rgb(130, 130, 130);\n"
""));

        horizontalLayout_2->addWidget(bgLabel_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 3, 2, 3);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        bgLabel_1 = new QLabel(centralWidget);
        bgLabel_1->setObjectName(QStringLiteral("bgLabel_1"));
        bgLabel_1->setStyleSheet(QLatin1String("background-color: rgb(130, 130, 130);\n"
"\n"
""));

        horizontalLayout_1->addWidget(bgLabel_1);


        gridLayout->addLayout(horizontalLayout_1, 0, 1, 2, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(32, 32));
        MainWindow->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuEdit->addAction(actionCandidates);
        menuEdit->addAction(actionTest);
        mainToolBar->addAction(actionConfirm);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSwap);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDelete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionResume);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionReverse);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGroup);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUngroup);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionItpl);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoomIn);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoomOut);

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
        cancelButton->setText(QString());
        okButton->setText(QString());
        cutButton->setText(QString());
        playButton1->setText(QString());
        pauseButton1->setText(QString());
        stopButton1->setText(QString());
        editCheckBox->setText(QApplication::translate("MainWindow", "Edit Mode", 0));
        bgLabel_2->setText(QString());
        bgLabel_1->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
