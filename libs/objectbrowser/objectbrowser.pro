include (../libs.pri)

TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .
TARGET=objectbrowser

# Input
FORMS += qobjectbrowser.ui

HEADERS += qobjectbrowser.h qobjecttree.h obexport.h qobjectbrowseraction.h
SOURCES += qobjectbrowser.cpp qobjecttree.cpp qobjectbrowseraction.cpp

RESOURCES += objectbrowser.qrc
win32 {
    CONFIG += dll
    DEFINES += OBJECTBROWSER_DLL
}


OTHER_FILES += README.txt
