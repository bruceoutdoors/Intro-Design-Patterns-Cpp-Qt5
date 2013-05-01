#include "customer.h"
#include "address.h"

Customer::Customer(QString name, QString id, CustomerType type) {
    setName(name);
    setId(id);
    setType(type);
}

/** We are storing addresses as QObject children.
 * @return the address, or 0 if no default address is set. 
 */

Address* Customer::getAddress(QString name) const {
       Address* retval = findChild<Address*>(name);
       return retval;
}

void Customer::setAddress(Address* address, QString name) {
    address->setParent(this);
    address->setObjectName(name);
}

void Customer::setName(const QString &newName) {
    //  m_Name=newName;
    DataObject::setObjectName(newName);
}

void Customer::setId(const QString &newId) {
    m_Id=newId;
}

void Customer::setDateEstablished(const QDate & newDate) {
    m_DateEstablished = newDate;
}

void Customer::setType(CustomerType newType) {
    m_Type = newType;
}

void Customer::setTypeString(QString newType) {
    m_Type.fromString(newType);
}

