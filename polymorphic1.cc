
#include <iostream>
using namespace std;

class A {
public:
    virtual ~A() { }
    virtual void foo() {
        cout << "A's foo()" << endl;
        bar();
    }
    virtual void bar() {
        cout << "A's bar()" << endl;
    }
};

class B: public A {
public:
    void foo() {
        cout << "B's foo()" << endl;
        A::foo();
    }
    void bar() {
        cout << "B's bar()" << endl;
    }
};

int main() {
    B bobj;
    A *aptr = &bobj;
    aptr->foo();
    cout << "-------------" << endl;
    A aobj = *aptr;
    aobj.foo();
    cout << "-------------" << endl;
    aobj = bobj;
    aobj.foo();
    cout << "-------------"<< endl;
    bobj.foo();
}

