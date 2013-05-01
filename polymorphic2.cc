#include <iostream>
using namespace std;

class A {
public:
    virtual void foo() {
        cout << "A's foo()" << endl;
    }
};

class B: public A {
public:
    void foo() {
        cout << "B's foo()" << endl;
    }
};

class C: public B {
public:
    void foo() {
        cout << "C's foo()" << endl;
    }
};


int main() {
    C cobj;
    B *bptr = &cobj;
    bptr->foo();
    A* aptr = &cobj;
    aptr->foo();
}