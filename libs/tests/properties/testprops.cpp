#include <QtCore>

#include "testprops.h"
/* A testcase that shows how dynamic properties work. */
void TestProps::testDynamicProps() {
    QString tv1("Test Value 1");
    QString tv2("Test value 2");
    setSomeString(tv1);                                         /* Set a property by its setter */
    QCOMPARE(property("someString"), QVariant(tv1));

    bool dynamicSet = setProperty("someOtherString", QVariant(tv2));
    QVERIFY(!dynamicSet);                                       /* setProperty() succeeded, but returned false to indicate that a dynamic property was set, instead of a regular one defined in Q_PROPERTY macro. */
    QCOMPARE(property("someOtherString"), QVariant(tv2));

    const QMetaObject* meta = metaObject();
    int idx = meta->indexOfProperty("someString");
    QVERIFY(idx > -1);                                          /* Notice the
          Q_PROPERTY can be found in the metaObject... */

    QVERIFY (meta->indexOfProperty("someOtherString") == -1);   /* while the dynamic property is not. */

    bool found = false;
    foreach (const QByteArray &ba, dynamicPropertyNames()) {
        QString str(ba);
        QVERIFY(str != "someString");                           /* expect not to find someString here */
        if (str == "someOtherString") found=true;
    }
    QVERIFY(found);                                             /* But someOtherString must be found */
}
//end
QTEST_MAIN(TestProps)
