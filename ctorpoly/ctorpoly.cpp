#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "in A ctor" << endl;
        foo();
    }
    virtual void foo() {
        cout << "A's foo()" << endl;
    }
};

class B: public A {
public:
    B() {
        cout << "in B ctor" << endl;
    }
    void foo() {
        cout << "B's foo()" << endl;
    }
};

class C: public B {
public:
    C() {
        cout << "in C ctor" << endl;
    }

    void foo() {
        cout << "C's foo()" << endl;
    }
};

int main() {
    C* cptr = new C;
    cout << "After construction is complete:" << endl;
    cptr->foo();
    return 0;
}

