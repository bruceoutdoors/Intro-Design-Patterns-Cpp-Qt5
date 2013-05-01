CONFIG += debug
TEMPLATE = app
TARGET = login
DEPENDPATH += .
INCLUDEPATH += . $$(CPPLIBS)/utils $$(CPPLIBS)/dataobjects
LIBS += -lutils -ldataobjects -L$$(CPPLIBS)

# Input
HEADERS += login.h user.h passwordmanager.h
SOURCES += login.cpp user.cpp passwordmanager.cpp

unix {
   UI_DIR = .ui
   MOC_DIR = .moc
   OBJECTS_DIR = .obj
}

