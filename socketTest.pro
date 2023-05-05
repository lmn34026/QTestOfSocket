#-------------------------------------------------
#
# Project created by QtCreator 2023-01-10T15:00:18
#
#-------------------------------------------------

CONFIG += qt

QT += core gui
QT += network
QT += widgets
#QT += serialport

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#greaterThan(QT_MAJOR_VERSION, 4): QT += serialport

TARGET = socketTest
TEMPLATE = app


SOURCES += main.cpp\
    TXDatasForm.cpp \
        mainwindow.cpp \
    utilCommTools.cpp \
    utilUIElement.cpp \
    utilSocket.cpp \
#    utilSerialPort.cpp

HEADERS  += mainwindow.h \
    TXDatasForm.h \
    utilSocket.h \
    utilCommTools.h \
    utilUiElement.h \
#    utilSerialPort.h

FORMS    += mainwindow.ui \
    TXDatasForm.ui

#CONFIG += serialport
#CONFIG += console

QMAKE_CXXFLAGS += -Wno-deprecated-copy

