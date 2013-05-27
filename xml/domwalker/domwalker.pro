# include common qmake settings
include (../../libs/common.pri)

QT += widgets

# this project depends on libdataobjects:
LIBS += -ldataobjects 

# this directory contains the libraries:
LIBS += -L$$CPPLIBS

# Search here for headers:
INCLUDEPATH += ../../libs/dataobjects

QT += xml gui

CONFIG += console
TEMPLATE = app

SOURCES += main.cpp slacker.cpp domwalker.cpp xmltreemodel.cpp
HEADERS += slacker.h domwalker.h xmltreemodel.h
