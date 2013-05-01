#include <iostream>
using namespace std;

class Quux {
public:
    Quux(int initializer) :
        mData(initializer), printcounter(0) {}
    void print() const;
    void showprintcounter() const {
      cout << printcounter << endl; 
    }

private:
    int mData;
    int printcounter;
};

void Quux::print() const {
    cout << mData << endl; 
}

int main() {
    Quux a(45);
    a.print();
    a.print();
    a.print();
    a.showprintcounter();
    const Quux b(246);
    b.print();
    b.print();
    b.showprintcounter();
    return 0;
}

