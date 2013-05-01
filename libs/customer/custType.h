
#ifndef  _CUST_TYPE_H_
#define  _CUST_TYPE_H_

#include <enum.h>
#include "cexport.h"

class CUSTOMER_EXPORT CustomerType : public Enum {
public:
    CustomerType(int value=0): Enum(value) {}
    CustomerType(QString ctyp);
    const NameMap& nameMap() const;

};
#endif
