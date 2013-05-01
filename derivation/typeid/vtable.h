#ifndef VTABLE_H
#define VTABLE_H
//start
class Base {
 protected:
    int m_X, m_Y;
 public:
    Base();
    virtual ~Base();
    virtual void virtualFun() const;
};

class Derived : public Base {
    int m_Z;
 public:
    Derived();
    ~Derived();
    void virtualFun() const ;
};
//end
#endif        //  #ifndef VTABLE_H

