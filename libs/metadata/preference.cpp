#include "preference.h"
#include <qmap.h>

/*  This is an instantiation of an ooEnum class.
  We implement the bidirectional int-string mapping through
  the use of static variables. */

/** A comma separated list of all allowable values */

static const QString NAMESSTR = "Undefined=0,Bad Taste=1,Poor=2,Lousy=3,Fair=4,None=5,Good=6,Better=7,Very Good=8,Perfect=9,Excellent=10";
static const QStringList NAMELIST(NAMESSTR.split(","));

static NameMap s_nameMap;
static bool initialized = false;

const NameMap& Preference::nameMap() const {
    return Enum::initMap(s_nameMap, NAMELIST, initialized);
}

/* Normally it is not ok to call a virtual function from a
    ctor, but we are calling this one non-virtually -
    the compiler can resolve the call */

Preference::Preference(QString prefstr) {
    fromString(prefstr);
}


Preference::Preference(int value) : Enum(value) {    
}


