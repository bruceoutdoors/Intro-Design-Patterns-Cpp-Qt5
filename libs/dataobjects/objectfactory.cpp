#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QMetaObject>

#include "objectfactory.h"
#include "address.h"
#include "country.h"

//start id=newobject
ObjectFactory::ObjectFactory() {
    m_knownClasses["UsAddress"] = UsAddress::staticMetaObject;
    m_knownClasses["CanadaAddress"] = CanadaAddress::staticMetaObject;
}

QObject* ObjectFactory::newObject(QString className, QObject* parent) {
    QObject* retval = 0;
    if (m_knownClasses.contains(className)) {
        const QMetaObject& mo = m_knownClasses[className];
        retval = mo.newInstance();      /* Requires Qt 4.5 or later. */
        if (retval == 0) {
            qDebug() << "Error creating " << className;
            abort();
        }
    } else {
        qDebug() << QString("Generic QObject created for new %1")
                    .arg(className);
        retval = new QObject();
        retval->setProperty("className", className);
    }
    if (parent != 0) retval->setParent(parent);
    return retval;
}
//end


