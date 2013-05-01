TEMPLATE=lib
include (../libs.pri)

win32 {
    DEFINES += FILETAGGER_DLL
}

INCLUDEPATH += ../metadata ../dataobjects
LIBS += -lmetadata -ldataobjects -ltag
TAGLIB_DIR=$$(TAGLIB_DIR)
!isEmpty( TAGLIB_DIR ) {
    INCLUDEPATH += $$(TAGLIB_DIR)/include
}

HEADERS += \
    tmetadataloader.h 

SOURCES += \
    tmetadataloader.cpp 
OTHER_FILES += README.txt
