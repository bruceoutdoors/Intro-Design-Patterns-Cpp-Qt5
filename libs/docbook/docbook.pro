include (../libs.pri)

TEMPLATE=lib
# Input
HEADERS += docbookdoc.h docbookwalker.h docbook_export.h
SOURCES += docbookdoc.cpp docbookwalker.cpp

# We need this in order to find XML header files.
QT += xml 

win32 {
    DEFINES += DOCBOOK_DLL 
}


