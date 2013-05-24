include (../../libs/common.pri)
QT += widgets
TEMPLATE = app
LIBS += -lcards2 -L$$CPPLIBS
INCLUDEPATH += ../../libs/cards2

# Input
HEADERS += cardtable.h
SOURCES += boxes.cpp  \ 
           cardtable.cpp

