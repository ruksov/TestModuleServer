include($$PWD/../../Global.pri)

QT += core network sql gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YAServerApp
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp

release: DESTDIR = $$PWD/../../bin/YAServer/release
debug:   DESTDIR = $$PWD/../../bin/YAServer/debug

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui
