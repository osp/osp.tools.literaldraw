#-------------------------------------------------
#
# Project created by QtCreator 2010-12-11T16:04:19
#
#-------------------------------------------------

QT       += core gui svg

TARGET = LiteralDraw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    literal.cpp \
    draw.cpp \
    svgview.cpp \
    command.cpp

HEADERS  += mainwindow.h \
    literal.h \
    draw.h \
    svgview.h \
    command.h

FORMS    += mainwindow.ui \
    literal.ui \
    draw.ui \
    svgview.ui

CONFIG  += debug
