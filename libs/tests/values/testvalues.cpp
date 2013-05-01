#include "testvalues.h"

/** testcase that shows one way to encode a QPointer into a QByteArray */
void TestValues::testPointerEncoding() {
    QObject *testObject = new QObject(this);
    QString testName = "SomeTestName";
    testObject->setObjectName(testName);
    QByteArray ba;
    QDataStream ods(&ba, QIODevice::WriteOnly);
    quint64 encodedPointer;
    encodedPointer = (quint64) testObject;
    ods << encodedPointer;

    QDataStream ids(&ba, QIODevice::ReadOnly);
    quint64 decodedPointer;
    ids >> decodedPointer;
    QObject *obj = reinterpret_cast<QObject*>(decodedPointer);

    QVERIFY(obj == testObject);

}


QTEST_MAIN(TestValues)
