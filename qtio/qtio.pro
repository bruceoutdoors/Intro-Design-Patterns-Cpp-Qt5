
CONFIG += debug console
DEFINES += QT_NOTHREAD_DEBUG

CONFIG -= moc
INCLUDEPATH += . ../qstd
DEPENDPATH += ../qstd

# Input
SOURCES += qtio-demo.cpp qstd.cpp 
HEADERS += qstd.h


