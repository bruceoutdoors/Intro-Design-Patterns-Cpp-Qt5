#include "address.h"

/* All static methods to initialize the type-wide constraints
   of our address-derived classes. */
   QString UsAddress::getPhoneFormat() {
       return
  "(\\+?1[- ]?)?\\(?(\\d{3,3})\\)?[\\s-]?(\\d{3,3})[\\s-]?(\\d{4,4})";
   }
   

QString CanadaAddress::getPhoneFormat() {
    return
   "(\\+?1[- ]?)?\\(?(\\d{3,3})\\)?[\\s-]?(\\d{3,3})[\\s-]?(\\d{4,4})";
}

