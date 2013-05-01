#include "testxmlimport.h"
#include <qobjectreader.h>
#include <address.h>
#include <customerfactory.h>
#include <QDebug>
#include <customer.h>

static DataObject* testObject() {
    CustomerFactory *fac = CustomerFactory::instance();
    Customer* cust = qobject_cast<Customer*>(fac->newObject("Customer"));
    // Now assign values to a Customer that has two
    // Address children.
    Address* home = qobject_cast<Address*>(fac->newObject("UsAddress"));
    home->setParent(cust);
    home->setObjectName("Home Address");
    Address* work = qobject_cast<Address*>(fac->newObject("CanadaAddress"));
    work->setParent(cust);
    work->setObjectName("Work Address");
    // Set some values
    QDate testDate(2004, 9, 1);
    cust->setObjectName("Bilbo Baggins");
    cust->setId("NEWID1234");
    cust->setDateEstablished(testDate);
    cust->setTypeString("Educational");
    home->setLine1("123 Sunnyside Street");
    home->setLine2("Apartment 9W");
    home->setCity("Hobbitshire");
    home->setPhone("(876) 543-2109");
    home->setProperty("State", "WA");
    home->setProperty("Zip","12345");
    work->setLine1("666 Shelob's Cave");
    work->setLine2("Sticky Web 45");
    work->setCity("Mordor");
    work->setPhone("(654) 321-0987");
    work->setProperty("Province","BC");
    work->setProperty("PostalCode","A1B 2C4");
    return cust;
}


void writeToTestFile(DataObject* dobj, QString filename) {
    QFile outf(filename);
    outf.open(QIODevice::WriteOnly);
    QTextStream outstr;
    outstr.setDevice(&outf);
    //   qDebug(xmlexp.objectToXml(dobj) );
    outstr << dobj->toString() << endl;
    outf.close();
}


QObject * readFromFile(QString filename) {
    CustomerFactory *fac = CustomerFactory::instance();
    QObjectReader xmlimp(filename, fac);
    QObject* doptr = xmlimp.getRoot();
    Q_ASSERT(doptr != NULL);
    return doptr;
}


void TestXmlImport::test() {
    const QString testxmlfile = "testCust.xml";

    // set values for a Customer with two Address children
    DataObject * testobj1 = testObject();

    // write to file use XMLExport
    writeToTestFile(testobj1, testxmlfile);

    // Reading from file uses DataObjectReader
    DataObject* testobj2 = qobject_cast<DataObject*>(readFromFile(testxmlfile));
    // qDebug() << "Read Succssful" << testobj2->toString();

    // Did the data survive being written and then read?
    QVERIFY(*testobj2 == *testobj1);
    qDebug() << "Equals";
    // Now write the second Customer to file
    writeToTestFile(testobj2, "testCust2.xml");
    qDebug() << "Write";
    // Test the equals function in reverse.
    QVERIFY (*testobj1 == *testobj2);

    // Change one of the property values and see if equals notices.
    QString oldname = testobj2->objectName();
    testobj2->setObjectName("Mister Foobar");
    QVERIFY(!DataObject::equals(*testobj2, *testobj1));

    // Put back the original value and see if equals gets it right
    testobj2->setObjectName(oldname);
    QVERIFY(DataObject::equals(*testobj2, *testobj1));

    // Now we make a small change in one field of one child of testobj2.
    const QString waddr("Work Address");
    Address* work = testobj2->findChild<Address*>(waddr);
    QVERIFY(work != 0);
    QString oldphone = work->getPhone();
    work->setProperty("Phone", "(654) 321-0988");
    QCOMPARE(work->getPhone(), QString("(654) 321-0988"));
    // Let's see if equals thinks they are still equal.
    bool result = !DataObject::equals(*testobj2, *testobj1, true);
    QVERIFY(result);

    // Finally, we undo the last change and see what equals finds.
    work->setPhone(oldphone);
    result = DataObject::equals(*testobj2, *testobj1, true);
    QVERIFY(result);
}

QTEST_MAIN(TestXmlImport)
