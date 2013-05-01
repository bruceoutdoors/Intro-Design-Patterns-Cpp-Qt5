include (../../common.pri)

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += $$(CPPLIBS)/docbook

QT += xml

LIBS += -ldocbook  -L$$(CPPLIBS)
SOURCES += zenflesh.cpp
