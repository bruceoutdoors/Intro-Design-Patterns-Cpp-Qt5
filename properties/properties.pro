include (../common.pri)

CONFIG += qtestlib

TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += customer-props.h testcustomerprops.h
SOURCES += customer-props.cpp testcustomerprops.cpp
