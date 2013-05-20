include (../../common.pri)
INCLUDEPATH	+= ../../dataobjects \
                    ../../metadata
LIBS += -ldataobjects -lmetadata -L$$CPPLIBS

QT += testlib
TEMPLATE = app
TARGET = preference
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += testpreference.h
SOURCES += testpreference.cpp
