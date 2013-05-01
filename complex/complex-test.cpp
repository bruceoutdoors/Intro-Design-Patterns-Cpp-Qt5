#include "complex.h"
#include <iostream>

int main() {
    using namespace std;
    Complex c1(3.4, 5.6);
    Complex c2(7.8, 1.2);
    
    cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;
    cout << c1 << " - " << c2 << " = " << c1 - c2 << endl;
    Complex c3 = c1 * c2;
    cout << c1 << " * " << c2 << " = " << c3 << endl;
    cout << c3 << " / " << c2 << " = " << c3 / c2 << endl;
    cout << c3 << " / " << c1 << " = " << c3 / c1 << endl;
    
    return 0;
}

