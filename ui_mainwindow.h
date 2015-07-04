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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QLabel *blueLabel_2;
    QLabel *greenLabel_2;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QVBoxLayout *vLayout_2;
    QLabel *bgLabel_2;
    QPushButton *playButton1;
    QPushButton *pauseButton1;
    QFrame *line;
    QPushButton *cutButton;
    QPushButton *stopButton1;
    QLabel *yellowLabel_1;
    QVBoxLayout *vLayout_1;
    QLabel *bgLabel_1;
    QLabel *redLabel_1;
    QGridLayout *gridLayout;
    QCheckBox *editCheckBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        blueLabel_2 = new QLabel(centralWidget);
        blueLabel_2->setObjectName(QStringLiteral("blueLabel_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(blueLabel_2->sizePolicy().hasHeightForWidth());
        blueLabel_2->setSizePolicy(sizePolicy1);
        blueLabel_2->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 255);\n"
"font: 75 10pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(blueLabel_2, 12, 0, 1, 1);

        greenLabel_2 = new QLabel(centralWidget);
        greenLabel_2->setObjectName(QStringLiteral("greenLabel_2"));
        sizePolicy1.setHeightForWidth(greenLabel_2->sizePolicy().hasHeightForWidth());
        greenLabel_2->setSizePolicy(sizePolicy1);
        greenLabel_2->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 0);\n"
"font: 75 10pt \"Times New Roman\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(greenLabel_2, 13, 0, 1, 1);

        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(cancelButton, 6, 7, 1, 1);

        okButton = new QPushButton(centralWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        sizePolicy2.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(okButton, 6, 6, 1, 1);

        vLayout_2 = new QVBoxLayout();
        vLayout_2->setSpacing(6);
        vLayout_2->setObjectName(QStringLiteral("vLayout_2"));
        bgLabel_2 = new QLabel(centralWidget);
        bgLabel_2->setObjectName(QStringLiteral("bgLabel_2"));
        bgLabel_2->setStyleSheet(QStringLiteral("background-color: rgb(159, 159, 159);"));

        vLayout_2->addWidget(bgLabel_2);


        gridLayout_2->addLayout(vLayout_2, 0, 6, 6, 3);

        playButton1 = new QPushButton(centralWidget);
        playButton1->setObjectName(QStringLiteral("playButton1"));
        sizePolicy2.setHeightForWidth(playButton1->sizePolicy().hasHeightForWidth());
        playButton1->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(playButton1, 6, 1, 1, 1);

        pauseButton1 = new QPushButton(centralWidget);
        pauseButton1->setObjectName(QStringLiteral("pauseButton1"));
        sizePolicy2.setHeightForWidth(pauseButton1->sizePolicy().hasHeightForWidth());
        pauseButton1->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(pauseButton1, 6, 2, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 9, 1, 1, 8);

        cutButton = new QPushButton(centralWidget);
        cutButton->setObjectName(QStringLiteral("cutButton"));
        sizePolicy2.setHeightForWidth(cutButton->sizePolicy().hasHeightForWidth());
        cutButton->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(cutButton, 6, 4, 1, 1);

        stopButton1 = new QPushButton(centralWidget);
        stopButton1->setObjectName(QStringLiteral("stopButton1"));
        sizePolicy2.setHeightForWidth(stopButton1->sizePolicy().hasHeightForWidth());
        stopButton1->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stopButton1, 6, 3, 1, 1);

        yellowLabel_1 = new QLabel(centralWidget);
        yellowLabel_1->setObjectName(QStringLiteral("yellowLabel_1"));
        sizePolicy1.setHeightForWidth(yellowLabel_1->sizePolicy().hasHeightForWidth());
        yellowLabel_1->setSizePolicy(sizePolicy1);
        yellowLabel_1->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 0);\n"
"font: 75 10pt \"Times New Roman\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(yellowLabel_1, 11, 0, 1, 1);

        vLayout_1 = new QVBoxLayout();
        vLayout_1->setSpacing(0);
        vLayout_1->setObjectName(QStringLiteral("vLayout_1"));
        vLayout_1->setSizeConstraint(QLayout::SetDefaultConstraint);
        vLayout_1->setContentsMargins(-1, -1, 0, -1);
        bgLabel_1 = new QLabel(centralWidget);
        bgLabel_1->setObjectName(QStringLiteral("bgLabel_1"));
        bgLabel_1->setStyleSheet(QStringLiteral("background-color: rgb(159, 159, 159);"));

        vLayout_1->addWidget(bgLabel_1);


        gridLayout_2->addLayout(vLayout_1, 0, 1, 6, 5);

        redLabel_1 = new QLabel(centralWidget);
        redLabel_1->setObjectName(QStringLiteral("redLabel_1"));
        sizePolicy1.setHeightForWidth(redLabel_1->sizePolicy().hasHeightForWidth());
        redLabel_1->setSizePolicy(sizePolicy1);
        redLabel_1->setStyleSheet(QLatin1String("background-color: rgb(255, 0, 0);\n"
"font: 75 10pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(redLabel_1, 10, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 10, 1, 4, 8);

        editCheckBox = new QCheckBox(centralWidget);
        editCheckBox->setObjectName(QStringLiteral("editCheckBox"));
        editCheckBox->setStyleSheet(QStringLiteral("font: 75 12pt \"Times New Roman\";"));

        gridLayout_2->addWidget(editCheckBox, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionLoad);
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
        blueLabel_2->setText(QApplication::translate("MainWindow", "Hoff & Stable   ", 0));
        greenLabel_2->setText(QApplication::translate("MainWindow", "Hoff & Moving", 0));
        cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
        okButton->setText(QApplication::translate("MainWindow", "OK", 0));
        bgLabel_2->setText(QString());
        playButton1->setText(QApplication::translate("MainWindow", "Play", 0));
        pauseButton1->setText(QApplication::translate("MainWindow", "Pause", 0));
        cutButton->setText(QApplication::translate("MainWindow", "Cut", 0));
        stopButton1->setText(QApplication::translate("MainWindow", "Stop", 0));
        yellowLabel_1->setText(QApplication::translate("MainWindow", "Hon & Moving", 0));
        bgLabel_1->setText(QString());
        redLabel_1->setText(QApplication::translate("MainWindow", "Hon & Stable   ", 0));
        editCheckBox->setText(QApplication::translate("MainWindow", "Edit Mode", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
