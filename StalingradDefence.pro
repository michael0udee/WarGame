#-------------------------------------------------
#
# Project created by QtCreator 2017-03-03T12:27:08
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StalingradDefence
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    game.cpp \
    scenegui.cpp \
    settings.cpp \
    weapon.cpp \
    enemy.cpp \
    menu.cpp \
    player.cpp \
    obstacle.cpp \
    playerinfo.cpp \
    statistics.cpp \
    object.cpp \
    ranking.cpp

HEADERS  += \
    game.h \
    scenegui.h \
    settings.h \
    weapon.h \
    enemy.h \
    menu.h \
    player.h \
    obstacle.h \
    playerinfo.h \
    statistics.h \
    object.h \
    ranking.h

FORMS    += \
    settings.ui \
    menu.ui \
    playerinfodialog.ui \
    playerinfodialog.ui \
    rankingDialog.ui

RESOURCES += \
    images.qrc \
    music.qrc
