#include <qvariant.h>
#include <qmetaobject.h>
#include <QDebug>
#include "country.h"

static QStringList sCountryNames;


QStringList Country::getCountryNames() {
    if (sCountryNames.isEmpty()) {
        Country cc;
        QMetaProperty mp(cc.metaProperty("val"));
        QMetaEnum qmen = mp.enumerator();
        for (int i=0; i<qmen.keyCount(); ++i) {
            sCountryNames += qmen.valueToKey(i);
        }
    }
    return sCountryNames;
}

QString Country::toString() const {
    const QMetaProperty mp(metaProperty("val"));
    QMetaEnum qmen = mp.enumerator();
    return qmen.valueToKey(m_Val);
}

Country::Country(const QString& string) {
    const QMetaProperty mp(metaProperty("val"));
    QMetaEnum qmen = mp.enumerator();
    m_Val = static_cast<CountryType>(qmen.keyToValue(string.toAscii()));
}

/**
  You must pass a -DTESTCOUNTRY
  as a compiler argument for the below code to
  be included at compile time.
 
  To get qmake to generate a makefile
  which passes this to the compiler, 
  add this line to your .project file:
  DEFINES += DTESTCOUNTRY
*/

#ifdef TESTCOUNTRY

int main () {
    qDebug() << "TestCountry";
    qDebug() << QString(" CountryNames: %1").
           arg(Country::getCountryNames().join(", "));
    return 0;
}

#endif



