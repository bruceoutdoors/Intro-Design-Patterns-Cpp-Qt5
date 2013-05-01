#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include "testcustomerprops.h"

/** A function which converts any QObject with
    properties into a QString, using metaproperties.
*/
//start id=objToString
QString objToString(const QObject* obj) {
    QStringList result;
    const QMetaObject* meta = obj->metaObject();            /* Introspect
        into the object via the QMetaObject. */
    result += QString("class %1 : public %2 {")
        .arg(meta->className())
        .arg(meta->superClass()->className());
    for (int i=0; i < meta->propertyCount(); ++i) {
        const QMetaProperty qmp = meta->property(i);        /* Each property has a QMetaProperty. */
        QVariant value = obj->property(qmp.name());
        if (value.canConvert(QVariant::String))
            result += QString("  %1 %2 = %3;")
            .arg(qmp.typeName())  
            .arg(qmp.name())
            .arg(value.toString());
    }
    result += "};";
    return result.join("\n");
}
//end
//start id=main
#include "customer-props.h"
void TestCustomerProps::test() {
    Customer cust;
    cust.setObjectName("Customer");                         /* QObject function call. */
    cust.setName("Falafal Pita");                           /* Setting some simple properties. */
    cust.setAddress("41 Temple Street; Boston, MA; 02114");
    cust.setPhone("617-555-1212");
    cust.setType("Government");                             /* Setting enum property as a string. */
    QCOMPARE(cust.getType(), Customer::Government);         /* Comparing to enum value. */
    QString originalid = "834";                             /* Setting a string property. */
    cust.setId(originalid);
    QVariant v = cust.property("id");                       /* Getting it back as a QVariant through the QObject base class method. */
    QString str = v.toString();
    QCOMPARE(originalid, str);
    QDate date(2003, 7, 15);
    cust.setProperty("dateEstablished", QVariant(date));    /* Setting
        date properties, wrapped in QVariants. */
    QDate anotherDate = cust.getDateEstablished();          /* The date comes
        back through the type-specific getter. */
    QEXPECT_FAIL("", "These are different dates", Continue);
    QCOMPARE(date, anotherDate);
    cust.setId(QString("anotherId"));
    qDebug() << objToString(&cust);
    cust.setType(Customer::Educational);
    qDebug() << " Educational=" << cust.getType();
    cust.setType("BogusType");
    qDebug() << " Bogus= " << cust.getType();
    return;
}

QTEST_MAIN(TestCustomerProps)
//end
