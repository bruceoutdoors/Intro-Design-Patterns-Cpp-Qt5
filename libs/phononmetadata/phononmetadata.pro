include (../libs.pri)
TEMPLATE = lib

win32 {
    DEFINES += PHONONMETADATA_DLL
}
QT += phonon

LIBS += -ldataobjects -lmetadata

INCLUDEPATH += . \
    ../dataobjects ../metadata 

# Input
HEADERS +=     metadataloader.h \
    phononitem.h \
    phonon_mdexport.h
SOURCES +=    metadataloader.cpp \
    phononitem.cpp 

OTHER_FILES += README.txt
