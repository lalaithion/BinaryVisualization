#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T22:11:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryVis2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TextureWidget.cpp \
    displaywidget.cpp \
    OpenGLWindow.cpp \
    exampleMain.cpp

HEADERS  += mainwindow.h \
    TextureWidget.h \
    displaywidget.h \
    main.h \
    OpenGLWindow.h

FORMS    += mainwindow.ui
