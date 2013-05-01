include (../../common.pri)
DEPENDPATH += ../testmetadata
INCLUDEPATH += ../testmetadata

INCLUDEPATH += $$(CPPLIBS)/filetagger $$(CPPLIBS)/metadata $$(CPPLIBS)/dataobjects
LIBS += -lfiletagger -lmetadata -ldataobjects -ltag

QT       += testlib gui

TARGET = testfiletagger
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_testfiletagger.cpp testtracks.cpp
HEADERS += testtracks.h \
    tst_testfiletagger.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
