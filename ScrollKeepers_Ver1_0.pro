#-------------------------------------------------
#
# Project created by QtCreator 2017-04-04T09:41:55
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScrollKeepers_Ver1_0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    enemy.cpp \
    bullet.cpp \
    scrollgame.cpp \
    dragon.cpp \
    ehatchbutton.cpp \
    edragon.cpp \
    phatchbutton.cpp \
    pdragon.cpp \
    fdragon.cpp \
    fhatchbutton.cpp \
    idragon.cpp \
    ihatchbutton.cpp \

HEADERS  += mainwindow.h \
    enemy.h \
    bullet.h \
    scrollgame.h \
    dragon.h \
    ehatchbutton.h \
    edragon.h \
    phatchbutton.h \
    pdragon.h \
    fdragon.h \
    fhatchbutton.h \
    idragon.h \
    ihatchbutton.h \


RESOURCES += \
    img.qrc
