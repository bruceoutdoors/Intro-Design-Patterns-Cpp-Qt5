#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <QObject>
#include <QTextStream>

class Customer : public QObject {
  Q_OBJECT

 public:
  Customer(char* name);

  QString toString() const {
    QString retval = QString("  Customer: ") + objectName();
    return retval; 
  }        

};

QTextStream& operator<< (QTextStream& os, const Customer& c);

#endif

