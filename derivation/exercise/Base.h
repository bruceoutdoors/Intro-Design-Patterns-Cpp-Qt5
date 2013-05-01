#ifndef _BASE_H_
#define _BASE_H_
//start
class Base {
public:
    Base();
    void a();
    virtual void b() ;
    virtual void c(bool condition=true);
    virtual ~Base() {}
};


class Derived : public Base {
public:
    Derived();
    virtual void a();
    void b();
    void c();
};
//end
#endif 
