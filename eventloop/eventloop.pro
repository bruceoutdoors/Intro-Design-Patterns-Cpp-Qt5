include (../libs/common.pri)

LIBS += -lobjectbrowser -L$$CPPLIBS
INCLUDEPATH += ../libs/objectbrowser

QT       += widgets

#TARGET = events
TEMPLATE = app

SOURCES += main.cpp\
        keysequencelabel.cpp 

HEADERS  += keysequencelabel.h 

FORMS    += keysequencelabel.ui 
