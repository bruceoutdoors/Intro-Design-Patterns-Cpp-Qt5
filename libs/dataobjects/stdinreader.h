
#ifndef STDINREADER_H
#define STDINREADER_H

#include "dobjs_export.h"
#include "dataobject.h"


/**
  @short A simple I/O interface for reading properties
  of DataObjects from standard input.
  Will use input constraints if any were set.
  @author Alan Ezust
  */

class DOBJS_EXPORT StdinReader {
public:
    /**
     Prompt to cout 
     read each property from stdin,
     check against constraints, reprompt if invalid.
     @param ptr address of object to set properties read from user.
     @return true if successful (should always be true since
     current version infinitely retries.)
    */
    static bool readProperties(DataObject* ptr);
};

#endif
