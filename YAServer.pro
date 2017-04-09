TEMPLATE = subdirs

SUBDIRS = \
          src/ClientGUI\
          src/YAServerApp\
          src/ClientInfoLib\
          src/DatabaseManagerLib\
          src/YAServerLib

ClientGUI.file = ClientGUI/ClientGUI.pro
YAServerApp.file = YAServerApp/YAServerApp.pro
ClientInfoLib.file = ClientInfoLib/ClientInfoLib.pro
DatabaseManagerLib.file = DatabaseManagerLib/DatabaseManagerLib.pro
YaServerLib.file = YAServerLib/YaServerLib.pro

YAServerApp.depends = ClientInfoLib DatabaseManagerLib YAServerLib

OBJECTS_DIR = ./obj
