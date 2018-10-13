#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T20:21:19
#
#-------------------------------------------------

QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp \
    mainwidget.cpp \
    gamewidget.cpp

HEADERS  += \
    mainwidget.h \
    gamewidget.h

RESOURCES += \
    snakeResouce.qrc \
    listenresource.qrc
