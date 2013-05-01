#ifndef _COUNTRY_H
#define _COUNTRY_H
#include <qstringlist.h>
#include "dataobject.h"

/** @short an example DataObject

 This is a very simple object with a single enum property, Country.
 It is an example of how one can convert from QStrings
 to enum values and back. It does no string hardcoding anywhere.

 Since Country is derived (indirectly) from QObject, which has a private copy constructor,
 the compiler-supplied copy constructor will not work here. In fact, care should
 be taken to make sure that only Country references are passed to or returned from
 functions.
 */

class DOBJS_EXPORT Country : public DataObject {
    Q_OBJECT
    Q_PROPERTY( CountryType val READ getVal WRITE setVal );
    Q_ENUMS(CountryType);
public:
    /**  For Q_ENUMS macro to work, we must have the
         enum type definition in the same class as the Q_ENUMS
    */
    enum CountryType {Undefined=0, USA, Canada};

    Country(CountryType val=USA) : m_Val(val) {}
    Country(const QString& str);

    /**
      Since country is derived from QObject, which has a private assignment operator,
      the compiler-supplied assignment operator will not work, so we
      must define our own.
    */
    Country& operator=(const Country& newCountry) {
        m_Val=newCountry.m_Val;
        return *this;
    }
    /**
      @return a list all the Country names supported
    */
    static QStringList getCountryNames() ;

    CountryType getVal() const {
        return m_Val;
    }

    void setVal(CountryType nc) {
        m_Val = nc;
    }

    QString toString() const;

private:
    //    static QStringList sm_CountryNames;
    CountryType m_Val;
};
#endif
