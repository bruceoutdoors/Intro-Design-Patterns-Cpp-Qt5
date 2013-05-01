
include (../common.pri)
LIBS	+= -ldataobjects -L$$(CPPLIBS) 
INCLUDEPATH += $$(CPPLIBS)/dataobjects


TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += customer.h
SOURCES += findchildren.cpp customer.cpp
