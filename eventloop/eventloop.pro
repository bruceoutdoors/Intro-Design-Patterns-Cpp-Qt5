include (../common.pri)

LIBS += -lobjectbrowser -L$$(CPPLIBS)
INCLUDEPATH += $$(CPPLIBS)/objectbrowser

QT       += core gui

#TARGET = events
TEMPLATE = app

SOURCES += main.cpp\
        keysequencelabel.cpp 

HEADERS  += keysequencelabel.h 

FORMS    += keysequencelabel.ui 
