#ifndef STRINGDATA_H
#define STRINGDATA_H

#include "mystring.h"
#include <QSharedData>
 
/** Example QSharedData type for SString 
    private implementation of a implicitly shared string 
    */
//start
class StringData : public QSharedData, public MyString {
public:
    friend class SString;
    StringData() {}
    StringData(const char* d) : MyString(d) {}
    explicit StringData(int len) : MyString(len) {}
    StringData(const StringData& other) 
             : QSharedData(other), MyString(other) {}    
};
//end
#endif        //  #ifndef STRINGDATA_H
