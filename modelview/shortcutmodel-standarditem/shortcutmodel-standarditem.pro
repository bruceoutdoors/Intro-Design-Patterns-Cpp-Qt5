include (../../common.pri)
DEPENDPATH += ../sampleapp

HEADERS = actiontableeditor.h \
    actioneditordialog.h \
    application.h
SOURCES = actiontableeditor.cpp \
    actioneditordialog.cpp \
    application.cpp \
    main.cpp

FORMS += actioneditordialog.ui \
    actiontableeditor.ui
RESOURCES += $$(CPPLIBS)/icons/icons.qrc

