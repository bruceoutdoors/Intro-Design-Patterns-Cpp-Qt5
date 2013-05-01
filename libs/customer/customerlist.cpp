
#include "customerlist.h"

#include <QVector>
#include <QListIterator>
#include <QDebug>

void CustomerList::addCustomer(Customer* cust) {
    cust->setParent(this); // now it is managed by this object
}

//start id=qobjectcast
/* The Qt3 version of this method demonstrates the use of
   QObject_cast. Qt4 makes it much easier to get all
   customers in a childlist. */
QList<Customer*> CustomerList::getCustomers_old() {
    QList<Customer*> retval;
    QListIterator<QObject*> itr(children());
    while (itr.hasNext()) {
        Customer* cust = qobject_cast<Customer*>(itr.next());
        if (cust != 0)
            retval.append(cust);
    }
    return retval;
}

QList<Customer*> CustomerList::getCustomers() {
   qDebug() << "getCustomers()";
   return findChildren<Customer*>("Customer");
}
//end

//start id=inherits

/* A totally silly example that uses inherits,
   static_cast and iterators. */
QStringList CustomerList::getDateListVerbose() {
    QStringList retval;
    QListIterator<QObject*> itr(children());
    while (itr.hasNext()) {
        QObject* qptr = itr.next();
        if (qptr->inherits("Customer")) {
            Customer* cust = static_cast<Customer*> (qptr);
            retval.append(QString("ID: %1 - StartDate: %2")
            .arg(cust->getId())
            .arg(cust->getDateEstablished().toString()));
        }
    }
    return retval;
}

/* This is the same example using foreach */
QStringList CustomerList::getDateList() {
    QStringList retval;
    foreach (const Customer* cust, getCustomers()) {
        retval.append(QString("ID: %1 - StartDate: %2")
        .arg(cust->getId())
        .arg(cust->getDateEstablished().toString()));
    }
    return retval;
}

//end
