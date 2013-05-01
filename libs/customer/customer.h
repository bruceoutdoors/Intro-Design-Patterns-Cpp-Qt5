#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QVariant>

#include <dataobject.h>
#include "cexport.h"
#include "custType.h"
class Address;
//start
class CUSTOMER_EXPORT Customer : public DataObject {
    Q_OBJECT
  public:
    Q_INVOKABLE explicit Customer(QString name=QString(), QObject* parent=0)
        : DataObject(parent) {
        setObjectName(name);
    }
    Q_INVOKABLE Customer(QString name, QString id, CustomerType type);
    Q_PROPERTY( QString Name READ objectName WRITE setObjectName);
    Q_PROPERTY( QString Id READ getId WRITE setId );
    Q_PROPERTY( QDate DateEstablished READ getDateEstablished
                WRITE setDateEstablished );
    Q_PROPERTY( QString Type READ getTypeString  WRITE setTypeString );
  protected:
    /**
    @see CustomerFactory for creating Customer objects */
//end
  public:
    Address* getAddress(QString name="default") const;
    QString getName() const {
        return objectName();
    }
    QString getId() const {
        return m_Id;
    }
    QDate getDateEstablished() const {
        return m_DateEstablished;
    }
    CustomerType getType() const {
        return m_Type;
    }
    QString getTypeString() const {
        return m_Type.toString();
    }
    static void test();

  public slots:
    void setName(const QString& newName);
    void setId(const QString& newId);
    void setDateEstablished(const QDate& newDate);
    void setAddress(Address* address, QString name="default");
    void setType(CustomerType newType);
    void setTypeString(QString newType);
  private:
    QString m_Id;
    QDate m_DateEstablished;
    CustomerType m_Type;
};
#endif

