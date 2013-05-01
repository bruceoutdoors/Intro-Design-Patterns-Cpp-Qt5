include (../libs.pri)

TEMPLATE = lib
QT += gui

# For locating the files.
RESOURCES = cards2.qrc
SOURCES += cardpics.cpp \
    card.cpp
HEADERS += cardpics.h \
    card.h \
    cards_export.h

win32 {
	DEFINES += CARDS_DLL 
}
