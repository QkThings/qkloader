#-------------------------------------------------
#
# Project created by QtCreator 2014-04-13T04:02:34
#
#-------------------------------------------------

QT       += core gui

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = efm32_loader
TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp\
        mainwindow.cpp \
    efm32loader.cpp \
    xmodem.cpp \
    clhandler.cpp

HEADERS  += mainwindow.h \
    efm32loader.h \
    xmodem.h \
    clhandler.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
