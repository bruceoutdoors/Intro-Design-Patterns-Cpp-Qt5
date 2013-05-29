include (../../common.pri)
QT += widgets

TARGET = PrimeThreads
TEMPLATE = app

CONFIG += debug

HEADERS += \
    primeserver.h \
    primethread.h \
    primegui.h \
    isprime.h

SOURCES += \
    primeserver.cpp \
    main.cpp \
    primethread.cpp \
    primegui.cpp \
    isprime.cpp

FORMS += \
    primegui.ui

LIBS += -lQt5Concurrent
