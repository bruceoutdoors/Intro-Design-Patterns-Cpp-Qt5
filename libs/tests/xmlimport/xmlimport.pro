include (../../common.pri)

QT += xml testlib
CONFIG += debug

INCLUDEPATH += ../../customer \
                ../../dataobjects

# Input
HEADERS +=  testxmlimport.h
SOURCES += testxmlimport.cpp

LIBS    += -lcustomer -ldataobjects  -L$$CPPLIBS

