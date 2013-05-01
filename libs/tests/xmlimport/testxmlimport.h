#ifndef TESTXMLIMPORT_H
#define TESTXMLIMPORT_H

#include <QtTest/QtTest>

/**
 A test Case that verifies that DataObjectReader can import a
 saved Customer "testCust.xml" file (exported with @ref XMLExport),
 in the sourcecode directory.
 
 This is also a test of DataObjects::ObjectFactory and PropsMap,
 because XMLExport uses both of these classes.
 */

class TestXmlImport : public QObject {
    Q_OBJECT
private slots:
    void test();
};
#endif

