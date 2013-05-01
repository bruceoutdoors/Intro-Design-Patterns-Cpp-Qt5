#include "testcustomer.h"
#include "dataobject.h"
#include <customerfactory.h>
#include <address.h>
#include <qobjectreader.h>
#include <qstring.h>
#include <qmetaobject.h>

void TestCustomer::test()  {

    // Create a CustomerFactory
    qDebug() << "Before CustomerFactory::instance" << endl;
    
    CustomerFactory &cf = *(CustomerFactory::instance());
    Customer* cust;
    qDebug() << "Before newcustomer" << endl;
    cust = qobject_cast<Customer*>(cf.newObject("Customer"));
    // Now assign values to properties of a Customer
    // that has two Address children.
    Address* home = cf.newAddress("USA");
    home->setProperty("name", "Home Address");
    home->setParent(cust);
    Address* work = cf.newAddress("Canada");
    work->setProperty("name", "Work Address");
    work->setParent(cust);
    cust->setAddress(work);
    // Set some values
    QDate testDate(2004, 9, 1);
    cust->setName("Bilbo Baggins");
    cust->setId("NEWID1234");
    cust->setDateEstablished(testDate);
    //  qDebug(cust->getTypeString());
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
    // Export to a file
    QString filename("testCust.xml");
    QFile outf(filename);
    outf.open(QIODevice::WriteOnly);
    QTextStream outstr;
    outstr.setDevice(&outf);
    qDebug() << cust->toString();
    outstr << cust->toString() << endl;
    // Close the file
    outf.close();
    // Create another Customer
    QObjectReader xmlimp(filename, CustomerFactory::instance());
    //  xmlimp.parse();
    DataObject* doptr = qobject_cast<DataObject*>(xmlimp.getRoot());
    QVERIFY(doptr != NULL);
    QVERIFY(*cust == *doptr); /* DataObject::equals() */

}
QTEST_MAIN(TestCustomer)

