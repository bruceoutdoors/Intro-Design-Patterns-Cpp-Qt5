#ifndef CUSTOMERFACTORY_H
#define CUSTOMERFACTORY_H

#include <objectfactory.h>
#include <country.h>
#include "customer.h"
#include "address.h"
//start
class CUSTOMER_EXPORT CustomerFactory : 
                             public QObject, public ObjectFactory {
  public:
    static CustomerFactory* instance();                      /* Singleton factory method. */
    Customer* newCustomer(QString name, QObject* parent=0);  /* Regular factory method, does not require a typecast. */
    Address* newAddress(QString countryType = "USA", QObject* parent=0);
  private:
    CustomerFactory(QObject* parent=0);
};
//end
#endif
