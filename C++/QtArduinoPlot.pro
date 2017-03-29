#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T21:43:28
#
#-------------------------------------------------

QT       += core gui\
            printsupport\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtArduinoPlot
TEMPLATE = app


SOURCES +=  main.cpp\
            mainwindow.cpp \
            qcustomplot.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h

FORMS    += mainwindow.ui
