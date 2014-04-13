#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T20:20:01
#
#-------------------------------------------------

QT       -= gui
QT += serialport

TARGET = qkloader
TEMPLATE = lib

DEFINES += QKLOADER_LIBRARY

SOURCES += qkloader.cpp \
    xmodem.cpp

HEADERS += qkloader.h\
        qkloader_global.h \
    xmodem.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS +=

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
