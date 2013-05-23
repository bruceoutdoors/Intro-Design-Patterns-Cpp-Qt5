include (../../libs/modeltest/modeltest.pri)

QT += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
TEMPLATE = app

# Input
HEADERS += metadata.h \
    objtostring.h \
    metadatafactory.h \
    metadatatablemodel.h \
    playlistview.h \
    mainwindow.h \
    stardelegate.h \
    stareditor.h \
    starrating.h \
    timedisplay.h \
    sourcelistmodel.h \
    playlistsview.h
SOURCES += metadata.cpp \
    main.cpp \
    objtostring.cpp \
    metadatafactory.cpp \
    metadatatablemodel.cpp \
    playlistview.cpp \
    mainwindow.cpp \
    stardelegate.cpp \
    stareditor.cpp \
    starrating.cpp \
    timedisplay.cpp \
    sourcelistmodel.cpp \
    playlistsview.cpp
RESOURCES += ../../libs/icons/icons.qrc
FORMS += mainwindow.ui
