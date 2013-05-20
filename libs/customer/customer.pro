#include (../libs.pri)
TEMPLATE=lib
QT += widgets
#LIBS += -ldataobjects

win32: LIBS += -L$$PWD/../../build-libs-Qt_5_0_2-Debug/dataobjects/debug/ -ldataobjects

INCLUDEPATH +=  ../dataobjects 

# Input
HEADERS += custType.h customer.h customerlist.h  customerfactory.h 
SOURCES += custType.cpp customer.cpp customerlist.cpp customerfactory.cpp 

win32 {
    CONFIG += dll 
    DEFINES += CUSTOMER_DLL
}



