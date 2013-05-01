include (../../common.pri)

INCLUDEPATH += $$(CPPLIBS)/dataobjects \
    $$(CPPLIBS)/objectbrowser \
#    $$(CPPLIBS)/filetagger \
    $$(CPPLIBS)/phononmetadata \
    $$(CPPLIBS)/sqlmetadata \
    $$(CPPLIBS)/metadata 


QT += xml sql phonon


DEPENDPATH += ../testmetadata
INCLUDEPATH += ../testmetadata

CONFIG += qtestlib

SOURCES += testsqlmetadata.cpp testtracks.cpp
HEADERS += testsqlmetadata.h testtracks.h

CONFIG += debug
LIBS += -lmetadata -lsqlmetadata \
	-lobjectbrowser \
	-ldataobjects 


USE_TAGLIB=$$(USE_TAGLIB)
isEmpty(USE_TAGLIB) {
    # Phonon Version: 
    QT += phonon
    LIBS += -lphononmetadata
    INCLUDEPATH += $$(CPPLIBS)/phononmetadata
} else {
    # Optional taglib based metadataloader.
    DEFINES += USE_TAGLIB
    LIBS += -lfiletagger -ltag
    INCLUDEPATH += $$(CPPLIBS)/filetagger
}


	