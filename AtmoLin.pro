#-------------------------------------------------
#
# Project created by QtCreator 2015-09-14T22:15:44
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = AtmoLin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    atmolight.cpp \
    ledarea.cpp

HEADERS  += mainwindow.h \
    atmolight.h \
    ledarea.h

FORMS    += mainwindow.ui

include(support/Qt-Color-Widgets/color_widgets.pri)

RESOURCES += \
    res.qrc
