QT += core
QT -= gui

CONFIG += c++11

TARGET = CryptoProject
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cryptoclass.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += $$PWD/../OpenSSL/include

win32-msvc*{
CONFIG(debug, debug|release){
message("debug")
CRYPTOLIB = $$PWD/../OpenSSL/msvc32/debug/
}
CONFIG(release, debug|release){
message("release")
CRYPTOLIB = $$PWD/../OpenSSL/msvc32/release/
}
}else: win32-g++{
CRYPTOLIB = $$PWD/../OpenSSL/mingw32/
}
message($$CRYPTOLIB)



LIBS += -L$$CRYPTOLIB
LIBS += \
-llibssl\
-llibcrypto



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    cryptoclass.h
