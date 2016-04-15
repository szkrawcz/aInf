QT += core
QT -= gui
QT += sql

CONFIG += c++11

TARGET = TrackNewCratedFiles
CONFIG += console
CONFIG -= app_bundle


TEMPLATE = app

SOURCES += main.cpp \
    dirgrinder.cpp \
    sqlgrinder.cpp

HEADERS += \
    dirgrinder.h \
    sqlgrinder.h
