#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T12:21:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtBinAdmin_Release_New_UI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    subchild.cpp \
    nodeitem.cpp \
    treescene.cpp

HEADERS  += mainwindow.h \
    subchild.h \
    nodeitem.h \
    treescene.h

FORMS    += mainwindow.ui \
    subchild.ui

RESOURCES += \
    bstu.qrc

DISTFILES += \
    README.MD
