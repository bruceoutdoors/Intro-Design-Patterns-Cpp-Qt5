#ifndef OOENUM_H
#define OOENUM_H

#include <QStringList>
#include <QTextStream>
#include <QMap>
#include "dobjs_export.h"

typedef QMap<QString, int> NameMap;

//start
/** @short An object-oriented enumerator class.
  This enum uses QStrings instead of compiler symbols,
  and provides bidirectional mapping between
  QStrings and int values. No compiler symbols
  are introduced.

  Does not have the same limitation as QMetaEnum, which must be
  attached to a particular Q_OBJECT class.

  This is an abstract class, and derived types can be used as
  custom QVariant property types provided they are declared
  and registered also.
*/

class DOBJS_EXPORT Enum {
public:
    /**
      You must override this method for your specific enumerator type.
      @return a QMap<QString, int>
    */
    virtual const NameMap&  nameMap() const = 0;

    friend DOBJS_EXPORT QTextStream& operator>>(QTextStream& ts,  Enum& pref);
    friend DOBJS_EXPORT QDataStream& operator>>(QDataStream& ds,  Enum& pref);

    Enum(int enumval = 0);
	Enum(const Enum& other);
    virtual ~Enum();

    /** Converts from the int value to a String */
    virtual QString toString() const;

    /** Converts from a string to the internal enum value.
          returns false if an invalid string is passed in. */
    virtual bool fromString(QString str);

    /** @return integer equivalent of this enumerated value */
    virtual int intValue() const ;

    bool operator=(int other);
    bool operator=(QString other);

    bool operator==(const Enum& other) const {
        return m_Val == other.m_Val;
    }
    bool operator==(const QString& other) const;
    bool operator!=(const Enum& other) const {
        return m_Val != other.m_Val;
    }
    bool operator<(const Enum& other) const {
        return m_Val < other.m_Val;
    }
    bool operator>(const Enum& other) const {
        return m_Val > other.m_Val;
    }
    /**
    @return an ordered list of symbols */
    QStringList names() const;


protected:
    //end
    void setIntValue(int v) {m_Val = v;}
    /** Adds symbols to the map with enum values starting
           at 0
         @param nameMap - the destination map to contain strings to numbers
         @param nameList - a string list of names to add to the map, with optional =value suffixes
         @param initialized - if true, do nothing (to avoid repeat-redundant calls
                  - if false, set to true after initializing.
    */
    static NameMap& initMap(NameMap& nameMap, QStringList nameList, 
                            bool&  initialized, int startIndex = 0);
    //start
    int m_Val;

};

DOBJS_EXPORT QTextStream& operator<<(QTextStream& ts, const Enum& pref);
DOBJS_EXPORT QTextStream& operator>>(QTextStream& ts, Enum& pref);

DOBJS_EXPORT QDataStream& operator<<(QDataStream& ds, const Enum& pref);
DOBJS_EXPORT QDataStream& operator>>(QDataStream& ds, Enum& pref);

//end
#endif

