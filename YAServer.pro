TEMPLATE = subdirs

SUBDIRS = \
          src/ClientGUI\
          src/YAServerApp\
          src/ClientInfoLib\
          src/DatabaseManagerLib\
          src/YAServerLib

YAServerApp.depends = ClientInfoLib DatabaseManagerLib YAServerLib

OBJECTS_DIR = ./obj
