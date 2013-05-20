#include (../libs.pri)
TEMPLATE = lib
#QT += phonon sql
QT += sql widgets
DEPENDPATH += .
INCLUDEPATH += ../metadata ../dataobjects
#LIBS += -ldataobjects -lmetadata
win32: LIBS += -L$$PWD/../../build-libs-Qt_5_0_2-Debug/dataobjects/debug/ -ldataobjects
win32: LIBS += -L$$PWD/../../build-libs-Qt_5_0_2-Debug/metadata/debug/ -lmetadata

# Input
HEADERS += dbconnectionform.h \
           dbconnectionsettings.h \
           dbutils.h \
           metadatatable.h \
           playlistdb.h \
           sqlmdexport.h
FORMS += DbConnectionForm.ui
SOURCES += dbconnectionform.cpp \
           dbconnectionsettings.cpp \
           dbutils.cpp \
           metadatatable.cpp \
           playlistdb.cpp


win32 {
    DEFINES += SQLMETADATA_DLL
}

OTHER_FILES += \
    readme.txt
