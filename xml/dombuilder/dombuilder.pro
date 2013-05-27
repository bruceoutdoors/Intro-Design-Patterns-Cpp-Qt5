include (../../libs/common.pri)

TEMPLATE = app
DEPENDPATH += .
CONFIG += console
INCLUDEPATH += ../../libs/docbook

QT += xml

LIBS += -ldocbook  -L$$CPPLIBS
SOURCES += zenflesh.cpp
