INCLUDEPATH += $$PWD

HEADERS += $$PWD/src/ClientInfoLib/clientinfo.h\
           $$PWD/src/DatabaseManagerLib/databasemanager.h\
           $$PWD/src/DatabaseManagerLib/stdafx.h\
           $$PWD/src/YAServerLib/dialog.h\
           $$PWD/src/YAServerLib/stdafx.h\
           $$PWD/src/YAServerLib/yaserver.h

SOURCES += $$PWD/src/DatabaseManagerLib/databasemanager.cpp\
           $$PWD/src/YAServerLib/dialog.cpp\
           $$PWD/src/YAServerLib/yaserver.cpp

FORMS += $$PWD/src/YAServerLib/dialog.ui


release: DESTDIR = $$PWD/bin/release
debug:   DESTDIR = $$PWD/bin/debug

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui
