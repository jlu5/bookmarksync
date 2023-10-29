#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T23:22:13
#
#-------------------------------------------------

QT       += core gui KIOCore KIOFileWidgets KIconThemes
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookmarksync
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
    kdeplacefilterproxymodel.cpp \
    bookmarksync.cpp \
    bookmarksyncbackend.cpp \
    bookmarksynckdebackend.cpp \
    backendwidget.cpp \
    placeeditdialog.cpp \
    bookmarksyncgtkbackend.cpp \
    placesitemmodel.cpp \
    bookmarksyncqtbackend.cpp

HEADERS += \
    kdeplacefilterproxymodel.h \
    bookmarksync.h \
    bookmarksyncbackend.h \
    place.h \
    bookmarksynckdebackend.h \
    backendwidget.h \
    placeeditdialog.h \
    bookmarksyncgtkbackend.h \
    placesitemmodel.h \
    bookmarksyncqtbackend.h

FORMS += \
    bookmarksync.ui \
    backendwidget.ui \
    placeeditdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target
