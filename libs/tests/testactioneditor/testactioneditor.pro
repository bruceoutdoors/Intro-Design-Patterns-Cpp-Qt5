include (../../common.pri)

QT += widgets printsupport
LIBS += -L$$CPPLIBS \
    -lactioneditor -lobjectbrowser
INCLUDEPATH += ../../actioneditor
INCLUDEPATH += ../../objectbrowser

HEADERS = application.h
SOURCES = application.cpp \
    main.cpp
!win32 {
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}
win32 {
    MOC_DIR = _moc
    OBJECTS_DIR = _obj
    CONFIG += console
}

RESOURCES += \
    iconImage.qrc
