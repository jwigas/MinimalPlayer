#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T10:55:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinimalPlayer-withVLCBackend
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    videowidget.h

FORMS    += mainwindow.ui

CONFIG  += static

LIBS        += -LD:\Home\Documents\kode\QtCode\VLCQt_1.1.0_win32_msvc2015\lib -lVLCQtCore -lVLCQtWidgets
LIBS        += -LD:\Home\Documents\kode\QtCode\VLCQt_1.1.0_win32_msvc2015\bin
INCLUDEPATH += D:\Home\Documents\kode\QtCode\VLCQt_1.1.0_win32_msvc2015\include
