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
