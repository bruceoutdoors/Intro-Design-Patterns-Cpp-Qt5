QT       += widgets

TARGET = life
TEMPLATE = app

SOURCES += main.cpp \
   lifemainwindow.cpp \
   lifewidget.cpp 

HEADERS  += lifemainwindow.h \
   lifewidget.h \
   lifeslice.h

FORMS    += lifemainwindow.ui 

LIBS += -lQt5Concurrent
# CONFIG += mobility
# MOBILITY = 

symbian {
    TARGET.UID3 = 0xee934e55
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
