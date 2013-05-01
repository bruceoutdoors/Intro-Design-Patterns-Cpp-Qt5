#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QVariant>
//start
class Customer : public QObject {
    Q_OBJECT                                                        /* Macro required for moc to preprocess class. */

    /* Each property declaration has the following syntax:
            
    Q_PROPERTY( type name READ getFunction [WRITE setFunction]
    [RESET resetFunction] [NOTIFY notifySignal] [DESIGNABLE bool]
    [SCRIPTABLE bool] [STORED bool] )
    */

    Q_PROPERTY( QString id READ getId WRITE setId NOTIFY valueChanged);
    Q_PROPERTY( QString name READ getName WRITE setName 
                NOTIFY valueChanged);
    Q_PROPERTY( QString address READ getAddress WRITE setAddress 
                NOTIFY addressChanged);
    Q_PROPERTY( QString phone READ getPhone WRITE setPhone 
                NOTIFY phoneChanged);
    Q_PROPERTY( QDate dateEstablished READ getDateEstablished );    /* Read-only property */
    Q_PROPERTY( CustomerType type READ getType WRITE setType 
                NOTIFY valueChanged);

  public:
    enum CustomerType
    { Corporate, Individual, Educational, Government };             /* The enum type
        definition must be in the same class definition as the Q_ENUMS macro. */
    Q_ENUMS( CustomerType ) ;                                       /* Special macro to generate string-to-enum conversion functions; must be in same class. */

    explicit Customer(const QString name = QString(),               /* Declared explicit because we do not want accidental conversions from QString to Customer. */ 
        QObject* parent = 0);                                       
                                                                  
    QString getId() const {
        return m_id;
    }
//end
    QString getName() const {
        return m_name;
    }
    QString getAddress() const {
        return m_address;
    }
    QString getPhone() const {
        return m_phone;
    }
    QDate getDateEstablished() const {
        return m_date;
    }
    CustomerType getType() const {
        return m_type;
    }
    QString getTypeString() const;
    void setId(const QString& newId);

    void setName(const QString& newName);
    void setAddress(const QString& newAddress);
    void setPhone(const QString& newPhone);
    void setDateEstablished(const QDate&  newDate);
//start
    // Overloaded, so we can set the type 2 different ways:
    void setType(CustomerType newType);
    void setType(QString newType);
signals:
    void addressChanged(QString newAddress);
    void phoneChanged(QString newPhone);
    void typeChanged(CustomerType type);
    void valueChanged(QString propertyName,
        QVariant newValue, QVariant oldValue = QVariant());
private:
    QString m_id, m_name, m_address, m_phone;
    QDate m_date;
    CustomerType m_type;
};
//end
#endif

