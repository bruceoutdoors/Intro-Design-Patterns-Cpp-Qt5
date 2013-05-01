include (../../common.pri)

TEMPLATE = app
LIBS += -lcards2 -L$$(CPPLIBS)
INCLUDEPATH +=  $$(CPPLIBS)/cards2

# Input
HEADERS += cardtable.h
SOURCES += boxes.cpp  \ 
           cardtable.cpp

