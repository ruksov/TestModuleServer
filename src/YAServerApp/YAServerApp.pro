include($$PWD/../YAServerLib/YAServerLib.pri)
include ($$PWD/../DatabaseManagerLib/DatabaseManagerLib.pri)
include ($$PWD/../ClientInfoLib/ClientInfoLib.pri)

QT += core network sql gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YAServerApp
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp


