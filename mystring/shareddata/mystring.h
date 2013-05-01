#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>


/** Safe Copy Assign String class. 
    Has a copy constructor and an assignment operator that 
    copies the dynamic memory to the new object.
    Manages a dynamic array under the covers. 
    Exception-safe. 
    */
class MyString {
public:
    MyString(const MyString& str); 
    MyString& operator=(const MyString& a);
    MyString(); 
    MyString(const char* chptr);  
    explicit MyString(int size);
    virtual ~MyString();
    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
    int length() const;
    MyString& operator+= (const MyString& other);
    friend MyString operator+(const MyString&, const MyString&);
protected:
    int   m_Len;
    char* m_Buffer;    /* Pointer to the start of dynamic array */
    void  copy(const char* chptr);
};
#endif        //  #ifndef MYSTRING_H

