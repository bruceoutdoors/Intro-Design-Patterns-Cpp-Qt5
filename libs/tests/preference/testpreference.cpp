#include <QVariant>
#include "testpreference.h"
#include "preference.h"

void TestPreference::testPreference() {
    QTextStream cout(stdout);
    Preference verygood("Very Good");
    Preference verygood2("Very Good");
    Preference excellent("Excellent");
    Preference fair("Fair");
    Preference good("Good");
    Preference good2("good");
    Preference none("None");
    Preference poor("Poor");
    Preference badtaste("Bad Taste");
    Preference undefined("undefined");
    QCOMPARE(verygood, verygood2);
    qDebug() << "verygood is " << verygood.toString();
    qDebug() << "fair is " << fair.toString();
    QVERIFY(verygood != fair);

    QCOMPARE(undefined.intValue(), 0);
    QVERIFY(none > undefined);
    QVERIFY(poor < none);
    QVERIFY(badtaste  < poor);
    QVERIFY(verygood > good);
    QVERIFY(good > fair);
    QVERIFY(fair > none);
    QVERIFY(fair < verygood);
    QVERIFY(verygood < excellent);

    // test QVariant conversion to/from
    QVariant propertyVariant;
    propertyVariant.setValue<Preference>(verygood);
    qDebug() << "propertyVariant: " <<  propertyVariant.toString() << endl;
    Preference fromVariant = propertyVariant.value<Preference>();
    qDebug() << "FV: " << fromVariant.toString() << " vg: " << verygood.toString();
    QCOMPARE(fromVariant, verygood);
    
    QCOMPARE(verygood.toString(), QString("Very Good"));
    QCOMPARE(good.toString(), QString("Good"));
    QCOMPARE(good2, good);
    qDebug() << verygood.toString();
    Preference q("notsogood");
    QCOMPARE(0, q.intValue());
    qDebug() << q.names().join(", ");

    /* Optional - Case Ignore conversions? */

    // Does this print "fair is fair" or "fair is 4"?
    cout << "Fair is " << fair;

    Preference verygoodlc("very good");
    QCOMPARE(verygood.intValue(), verygoodlc.intValue());
    QCOMPARE(verygood, verygoodlc);

}
QTEST_MAIN(TestPreference)
