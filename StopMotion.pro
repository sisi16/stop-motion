#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T15:22:51
#
#-------------------------------------------------

QT       += core gui
LIBS+=$$PWD\lib\*.lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets\
                                        multimedia\
                                        multimediawidgets

TARGET = StopMotion
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           videoprocessor.cpp \
           opflow.cpp \
           handdetection.cpp \
           myslider.cpp

HEADERS  += mainwindow.h \
            videoprocessor.h \
            opflow.h \
            handdetection.h \
            myslider.h

FORMS    += mainwindow.ui
