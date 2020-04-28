TEMPLATE     = app
CONFIG      += qt debug resources
#QMAKE_CXXFLAGS_DEBUG = -g -Wall
QMAKE_LIBS   = -ldl
HEADERS      = nw.h   nw_main_win.h   nw_help.h
SOURCES      = nw.cpp nw_main_win.cpp nw_help.cpp
RESOURCES    = nw.qrc
TARGET       = nw
