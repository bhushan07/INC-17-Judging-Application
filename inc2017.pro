#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T02:44:27
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
QT       +=printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inc2017
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    home.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    home.h \
    dialog.h

FORMS    += mainwindow.ui \
    home.ui \
    dialog.ui
