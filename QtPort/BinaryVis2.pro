#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T22:11:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryVis2
TEMPLATE = app


SOURCES +=\
    OpenGLWindow.cpp \
    readfile.cpp \
    main.cpp \
    gradient.cpp \
    interpolate.cpp

HEADERS  += \
    OpenGLWindow.h \
    readfile.h \
    gradient.h \
    interpolate.h

FORMS    += mainwindow.ui
