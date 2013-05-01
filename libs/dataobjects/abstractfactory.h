#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <QString>
#include "dobjs_export.h"
class QObject;

/** An Abstract Factory interface 
    @author Alan Ezust
*/

//start
class DOBJS_EXPORT AbstractFactory 
{
  public:
    /**
       @arg className - the desired class to instantiate
       @return a QObject-derived instance which
       is "close enough" to handle the properties of className.
    */
    virtual QObject* newObject (QString className, 
                                QObject* parent=0) = 0;
    virtual ~AbstractFactory();
	
};
//end

#endif        //  #ifndef ABSTRACTFACTORY_H
