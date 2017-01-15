#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T23:13:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServer
TEMPLATE = app
RC_FILE = TestServer.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    Clog.cpp \
    dialogsettings.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    Clog.h \
    dialogsettings.h \
    settings.h

FORMS    += mainwindow.ui \
    dialogsettings.ui
