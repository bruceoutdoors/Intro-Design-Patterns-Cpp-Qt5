include (../../common.pri)

QT += xml
CONFIG += qtestlib debug

INCLUDEPATH += $$(CPPLIBS)/customer $$(CPPLIBS)/dataobjects 

# Input
HEADERS +=  testxmlimport.h
SOURCES += testxmlimport.cpp

LIBS    += -lcustomer -ldataobjects  -L$$(CPPLIBS)

