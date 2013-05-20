include (../../common.pri)

INCLUDEPATH +=  ../../dataobjects \
                ../../customer
LIBS += -ldataobjects -lcustomer -L$$CPPLIBS

# qtestlib is deprecated
#CONFIG += qtestlib
QT += xml testlib

HEADERS += testcustomer.h testcustomerlist.h
SOURCES += testcustomer.cpp testcustomerlist.cpp

