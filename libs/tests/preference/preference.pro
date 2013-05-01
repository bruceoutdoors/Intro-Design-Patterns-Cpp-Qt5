include (../../common.pri)
INCLUDEPATH	+= $$(CPPLIBS)/dataobjects $$(CPPLIBS)/metadata
LIBS += -ldataobjects -lmetadata -L$$(CPPLIBS)

CONFIG += qtestlib
TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += testpreference.h
SOURCES += testpreference.cpp
