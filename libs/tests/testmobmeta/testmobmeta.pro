
include (../../common.pri)

LIBS += -ldataobjects -lmetadata -lmobilitymetadata -L$$(CPPLIBS)
INCLUDEPATH += $$(CPPLIBS)/dataobjects $$(CPPLIBS)/metadata $$(CPPLIBS)/mobilitymetadata $$(CPPLIBS)/tests/testmetadata
DEPENDPATH += $$(CPPLIBS)/tests/testmetadata

# libmultimediakit, from mobility:
CONFIG += mobility
MOBILITY = multimedia

HEADERS += \
    testmetadata.h testtracks.h

SOURCES += \
    testmetadata.cpp testtracks.cpp

FORMS += \
    testmetadata.ui
