include (../libs.pri)
TEMPLATE = lib
#QT += phonon sql
QT += sql
DEPENDPATH += .
INCLUDEPATH += . ../metadata ../dataobjects
LIBS += -ldataobjects -lmetadata

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
