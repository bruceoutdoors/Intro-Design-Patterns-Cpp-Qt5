TEMPLATE=lib
include (../libs.pri)


# libmultimediakit, from mobility:
CONFIG += mobility
MOBILITY = multimedia

win32 {
    DEFINES += MOBILITYMETADATA_DLL
}

LIBS += -ldataobjects -lmetadata -L$$(CPPLIBS)
INCLUDEPATH += $$(CPPLIBS)/dataobjects $$(CPPLIBS)/metadata 


HEADERS += \
    metadataloader.h \
    mobmetaexport.h

SOURCES += \
    metadataloader.cpp
