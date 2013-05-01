#ifndef SSTRING_H
#define SSTRING_H

#include "stringdata.h"
#include <QSharedDataPointer>
#include <iostream>
//start
/** Shared String demo of QSharedDataPointer */
class SString {
public:
    SString();
    explicit SString(int len);
    SString(const char* ptr);
    SString& operator+= (const SString& other);
    int length() const;
    int refcount() const {return m_d->ref;}
    friend SString operator+(SString, SString);
    friend std::ostream& operator<< (std::ostream&, const SString&);
//end    
    /** for debugging purposes only */
    qlonglong sharedDataAddress() const;

 /* Compiler-generated versions do what we want: 
    SString(const SString& other);
    SString& operator= (const SString& other); */
//start    
private:
    // Private Implementation Pattern
    QSharedDataPointer<StringData> m_d;
    
};
//end

#endif        //  #ifndef SSTRING_H
