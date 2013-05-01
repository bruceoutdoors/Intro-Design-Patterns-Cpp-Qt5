#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <QString>

/**
 A base class for user defined Exceptions. 
 We may replace this class with a standard exception, as soon as I
 can find one I like. For now, @ref assertequalsex.h throws exceptions
 and @ref TestCase will catch them.
 
   @author S. Alan Ezust sae@mcs.suffolk.edu
 */

class Exception : public QString {
public:

    Exception(QString message=QString()) :
    QString(message) {}

    /**
      By defining a conversion opreator to const char*,
      we can place this inside a qDebug() call
      */

    virtual ~Exception() {}

private:
};

#endif
