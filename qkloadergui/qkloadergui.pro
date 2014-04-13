#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T20:54:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = qkloadergui
TEMPLATE = app

INCLUDEPATH += ../../utils

INCLUDEPATH += ..
LIBS += -lqkloader
QMAKE_LIBDIR += ../release

SOURCES += main.cpp\
        qkloadergui.cpp \
    ../../utils/qkutils.cpp

HEADERS  += qkloadergui.h \
    ../../utils/qkutils.h

FORMS    += qkloadergui.ui

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

win32 {
  deploy.commands = python deploy.py
}
unix {
  deploy.commands = ./deploy.py
}
macx {

}
QMAKE_EXTRA_TARGETS += deploy
POST_TARGETDEPS += deploy
