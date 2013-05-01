#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

class Address;
#include <QHash>
#include <QMetaObject>

#include "dobjs_export.h"
#include "abstractfactory.h"

/**
   ObjectFactory - a default AbstractFactory.
   It knows how to create instances of
   some QObject-derived classes:
   @ref Address and also can "spoof" classes
   it does not know about by setting dynamic
   properties.

   It initializes constraints of the
   various Address-types before it creates the
   first instance.

   @author Alan Ezust
   @short Factory for creating Addresses

   @see QMetaObject::newInstance() - and Q_INVOKABLE.

*/

//start
class DOBJS_EXPORT  ObjectFactory : public AbstractFactory {
  public:
    ObjectFactory();
    /**
       @return a QObject-derived instance which
       can handle the properties of className.
       If the className is not a known type, it will return
       an instance of @ref PropsMap, serving as a
       catch-all. By default, the new object is a child of "this",
       which means its lifetime expires when this object is
       destroyed.
       Overridden versions of this class may return more specific types.
       @param className - the name of the class to create
       @param parent the parent of the object.
    */
    virtual QObject* newObject (QString className, QObject* parent=0);
 protected:
    QHash<QString, QMetaObject> m_knownClasses;
};
//end

#endif
