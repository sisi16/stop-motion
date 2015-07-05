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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionCandidates;
    QAction *actionTest;
    QAction *actionOpen;
    QAction *actionSet;
    QAction *actionSave;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *bgLabel_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *confirmButton;
    QPushButton *deleteButton;
    QPushButton *resumeButton;
    QPushButton *reverseButton;
    QPushButton *groupButton;
    QPushButton *ungroupButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *bgLabel_4;
    QGridLayout *gridLayout;
    QSlider *timeLineSlider;
    QFrame *line;
    QCheckBox *editCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *horizontalLayout_1;
    QPushButton *playButton1;
    QPushButton *pauseButton1;
    QPushButton *stopButton1;
    QVBoxLayout *vLayout_2;
    QLabel *bgLabel_2;
    QVBoxLayout *vLayout_1;
    QLabel *bgLabel_1;
    QPushButton *cutButton;
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
        actionCandidates = new QAction(MainWindow);
        actionCandidates->setObjectName(QStringLiteral("actionCandidates"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSet = new QAction(MainWindow);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/icons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        bgLabel_3 = new QLabel(centralWidget);
        bgLabel_3->setObjectName(QStringLiteral("bgLabel_3"));
        bgLabel_3->setStyleSheet(QStringLiteral("background-color: rgb(229, 229, 229);"));

        horizontalLayout_5->addWidget(bgLabel_3);


        gridLayout_2->addLayout(horizontalLayout_5, 13, 1, 1, 14);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        confirmButton = new QPushButton(centralWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(confirmButton);

        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        horizontalLayout_3->addWidget(deleteButton);

        resumeButton = new QPushButton(centralWidget);
        resumeButton->setObjectName(QStringLiteral("resumeButton"));

        horizontalLayout_3->addWidget(resumeButton);

        reverseButton = new QPushButton(centralWidget);
        reverseButton->setObjectName(QStringLiteral("reverseButton"));

        horizontalLayout_3->addWidget(reverseButton);

        groupButton = new QPushButton(centralWidget);
        groupButton->setObjectName(QStringLiteral("groupButton"));

        horizontalLayout_3->addWidget(groupButton);

        ungroupButton = new QPushButton(centralWidget);
        ungroupButton->setObjectName(QStringLiteral("ungroupButton"));

        horizontalLayout_3->addWidget(ungroupButton);


        gridLayout_2->addLayout(horizontalLayout_3, 11, 2, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        bgLabel_4 = new QLabel(centralWidget);
        bgLabel_4->setObjectName(QStringLiteral("bgLabel_4"));
        bgLabel_4->setStyleSheet(QStringLiteral("background-color: rgb(210, 210, 210);"));

        horizontalLayout_6->addWidget(bgLabel_4);


        gridLayout_2->addLayout(horizontalLayout_6, 14, 1, 1, 14);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        timeLineSlider = new QSlider(centralWidget);
        timeLineSlider->setObjectName(QStringLiteral("timeLineSlider"));
        timeLineSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(timeLineSlider, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 12, 1, 1, 14);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 9, 1, 1, 14);

        editCheckBox = new QCheckBox(centralWidget);
        editCheckBox->setObjectName(QStringLiteral("editCheckBox"));
        editCheckBox->setStyleSheet(QStringLiteral("font: 75 12pt \"Times New Roman\";"));

        gridLayout_2->addWidget(editCheckBox, 11, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        okButton = new QPushButton(centralWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        sizePolicy1.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(cancelButton);


        gridLayout_2->addLayout(horizontalLayout_2, 6, 3, 1, 1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        playButton1 = new QPushButton(centralWidget);
        playButton1->setObjectName(QStringLiteral("playButton1"));
        sizePolicy1.setHeightForWidth(playButton1->sizePolicy().hasHeightForWidth());
        playButton1->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(playButton1);

        pauseButton1 = new QPushButton(centralWidget);
        pauseButton1->setObjectName(QStringLiteral("pauseButton1"));
        sizePolicy1.setHeightForWidth(pauseButton1->sizePolicy().hasHeightForWidth());
        pauseButton1->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(pauseButton1);

        stopButton1 = new QPushButton(centralWidget);
        stopButton1->setObjectName(QStringLiteral("stopButton1"));
        sizePolicy1.setHeightForWidth(stopButton1->sizePolicy().hasHeightForWidth());
        stopButton1->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(stopButton1);


        gridLayout_2->addLayout(horizontalLayout_1, 6, 1, 1, 1);

        vLayout_2 = new QVBoxLayout();
        vLayout_2->setSpacing(6);
        vLayout_2->setObjectName(QStringLiteral("vLayout_2"));
        bgLabel_2 = new QLabel(centralWidget);
        bgLabel_2->setObjectName(QStringLiteral("bgLabel_2"));
        bgLabel_2->setStyleSheet(QStringLiteral("background-color: rgb(159, 159, 159);"));

        vLayout_2->addWidget(bgLabel_2);


        gridLayout_2->addLayout(vLayout_2, 0, 3, 3, 12);

        vLayout_1 = new QVBoxLayout();
        vLayout_1->setSpacing(0);
        vLayout_1->setObjectName(QStringLiteral("vLayout_1"));
        vLayout_1->setSizeConstraint(QLayout::SetDefaultConstraint);
        vLayout_1->setContentsMargins(-1, -1, 0, -1);
        bgLabel_1 = new QLabel(centralWidget);
        bgLabel_1->setObjectName(QStringLiteral("bgLabel_1"));
        bgLabel_1->setStyleSheet(QStringLiteral("background-color: rgb(159, 159, 159);"));

        vLayout_1->addWidget(bgLabel_1);


        gridLayout_2->addLayout(vLayout_1, 0, 1, 3, 2);

        cutButton = new QPushButton(centralWidget);
        cutButton->setObjectName(QStringLiteral("cutButton"));
        sizePolicy1.setHeightForWidth(cutButton->sizePolicy().hasHeightForWidth());
        cutButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(cutButton, 6, 2, 1, 1);

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
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        MainWindow->insertToolBarBreak(mainToolBar);
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

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionCandidates->setText(QApplication::translate("MainWindow", "Get Candidates", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open File", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSet->setText(QApplication::translate("MainWindow", "Set", 0));
#ifndef QT_NO_TOOLTIP
        actionSet->setToolTip(QApplication::translate("MainWindow", "Settings", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "save", 0));
        bgLabel_3->setText(QString());
        confirmButton->setText(QApplication::translate("MainWindow", "Confirm", 0));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", 0));
        resumeButton->setText(QApplication::translate("MainWindow", "Resume", 0));
        reverseButton->setText(QApplication::translate("MainWindow", "Reverse", 0));
        groupButton->setText(QApplication::translate("MainWindow", "Group", 0));
        ungroupButton->setText(QApplication::translate("MainWindow", "Un-group", 0));
        bgLabel_4->setText(QString());
        editCheckBox->setText(QApplication::translate("MainWindow", "Edit Mode", 0));
        okButton->setText(QApplication::translate("MainWindow", "OK", 0));
        cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
        playButton1->setText(QApplication::translate("MainWindow", "Play", 0));
        pauseButton1->setText(QApplication::translate("MainWindow", "Pause", 0));
        stopButton1->setText(QApplication::translate("MainWindow", "Stop", 0));
        bgLabel_2->setText(QString());
        bgLabel_1->setText(QString());
        cutButton->setText(QApplication::translate("MainWindow", "Cut", 0));
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
