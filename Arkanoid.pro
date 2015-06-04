#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T20:58:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arkanoid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    m_block.cpp \
    paddle.cpp \
    ball.cpp \
    drop.cpp \
    functiontimer.cpp \
    score.cpp

HEADERS  += mainwindow.h \
    board.h \
    m_block.h \
    paddle.h \
    ball.h \
    drop.h \
    functiontimer.h \
    score.h

FORMS    += mainwindow.ui \
    board.ui
