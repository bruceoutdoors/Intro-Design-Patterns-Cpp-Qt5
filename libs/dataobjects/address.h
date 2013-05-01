#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>


#include "country.h"
class ObjectFactory;

//start id=address

/** Abstract base class - not instantiable. */
class DOBJS_EXPORT Address : public QObject {
    Q_OBJECT
  public:
  //end
    Q_PROPERTY( QString Line1 READ getLine1 WRITE setLine1 );
    Q_PROPERTY( QString Line2 READ getLine2 WRITE setLine2 );
    Q_PROPERTY( QString City READ getCity WRITE setCity );
    Q_PROPERTY( QString Phone READ getPhone WRITE setPhone);
//start id="address"

    explicit Address(QString addressName = QString(), QObject* parent=0)
        : QObject(parent) { /* protected constructor */
        setObjectName(addressName);
    }
  public:
    virtual Country::CountryType getCountry() const = 0;
//end
    QString getLine1() const {
        return m_Line1;
    }
    QString getLine2() const {
        return m_Line2;
    }
    QString getCity() const {
        return m_City;
    }
    QString getPhone() const {
        return m_Phone;
    }

  public slots:
    void setLine1(QString nl1) {
        m_Line1 = nl1;
    }
    void setLine2(QString nl2) {
        m_Line2=nl2;
    }
    void setCity(QString city) {
        m_City = city;
    }
    void setPhone(QString phone) {
        m_Phone = phone;
    }
//start id=address
private:
    QString m_Line1, m_Line2, m_City, m_Phone;
};
//end

//start id=usaddress
class DOBJS_EXPORT UsAddress : public Address {
    Q_OBJECT
  public:
    Q_PROPERTY( QString State READ getState WRITE setState );
    Q_PROPERTY( QString Zip READ getZip WRITE setZip );
    explicit Q_INVOKABLE UsAddress(QString name=QString(), QObject* parent=0) 
                                  : Address(name, parent) {}
  protected:
    static QString getPhoneFormat();
  public:
//end
    Country::CountryType getCountry() const {
        return Country::USA;
    }
    QString getState() const {
        return m_State;
    }
    QString getZip() const {
        return m_Zip;
    }
  public slots:
    void setState(QString state) {
        m_State = state;
    }
    void setZip (QString zip) {
        m_Zip = zip;
    }
//start id=usaddress
  private:
    QString m_State, m_Zip;
};
//end
class DOBJS_EXPORT CanadaAddress : public Address {
    Q_OBJECT
  public:
    explicit Q_INVOKABLE CanadaAddress(QString name=QString(), QObject* parent=0)
                                      : Address(name, parent) {}
    static QString getPhoneFormat();

    Q_PROPERTY( QString Province READ getProvince
                WRITE setProvince );
    Q_PROPERTY( QString PostalCode READ getPostalCode
                WRITE setPostalCode );
  public:
//end
    Country::CountryType getCountry() const {
        return Country::Canada;
    }
    QString getProvince() const {
        return m_Province;
    }
    QString getPostalCode() const {
        return m_PostalCode;
    }
  public slots:
    void setProvince(QString province) {
        m_Province = province;
    }
    void setPostalCode (QString postalcode) {
        m_PostalCode = postalcode;
    }
//start id=subclass
  private:
    QString m_Province, m_PostalCode;
};
//end
#endif

