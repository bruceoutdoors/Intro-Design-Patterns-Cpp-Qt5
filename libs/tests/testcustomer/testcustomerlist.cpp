#include "testcustomerlist.h"
#include "customerfactory.h"
#include <QDebug>
#include <qobjectreader.h>
#include "customerlist.h"

void TestCustomerList::test() {
    CustomerList cl;
    QString filename="test2.xml";
    QObjectReader xmlimp(filename, CustomerFactory::instance());
    DataObject* imported = qobject_cast<DataObject*>(xmlimp.getRoot());
    QVERIFY(imported != 0);
    //  qDebug(QString("Imported") + imported->toString());
    cl.adoptChildren(imported);
    qDebug() << QString("CustomerList") + cl.toString();

}
