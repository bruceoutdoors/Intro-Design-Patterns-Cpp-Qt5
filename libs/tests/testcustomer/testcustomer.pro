include (../../common.pri)

INCLUDEPATH	+= $$(CPPLIBS)/dataobjects $$(CPPLIBS)/customer
LIBS += -ldataobjects -lcustomer -L$$(CPPLIBS)

CONFIG += qtestlib
QT += xml

HEADERS += testcustomer.h testcustomerlist.h
SOURCES += testcustomer.cpp testcustomerlist.cpp

