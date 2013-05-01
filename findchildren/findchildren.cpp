#include <QList>
#include <QObject>
#include <QDebug>
#include "customer.h"

int main(int argc, char** argv) {

    QObject parent;

    Customer* cust1 = new Customer("joe");
    cust1->setParent(&parent);

    Customer* cust2 = new Customer("bill");
    cust2->setParent(&parent);

    QObject* anotherObject = new QObject();
    anotherObject->setObjectName("Junk");
    anotherObject->setParent(&parent);
//start
/* Filter on Customer* */
    QList<Customer*> custlist = parent.findChildren<Customer*>();
    foreach (const Customer* current, custlist) {
        qDebug() << current->toString();
    }
//end

    qDebug() << "Showing all children" << endl;

    QObjectList allchildren = parent.children();
    QObjectList::const_iterator citr;
    for (citr = allchildren.constBegin(); citr!= allchildren.constEnd(); ++citr)
        qDebug() << (*citr)->objectName();
    return 0;
}


