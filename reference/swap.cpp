#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    cout << "Inside the swap() function:\n"
         << "address of a: " << &a
         << "\taddress of b: " << &b
         << "\naddress of temp: " << &temp << endl;
    a = b;
    b = temp;
}


int main() {
    int n1 = 25;
    int n2 = 38;
    int n3 = 71;
    int n4 = 82;
    cout << "Initial values:\n"
         << "address of n1: " << &n1
         << "\taddress of n2: " << &n2
         << "\nvalue of n1: " << n1
         << "\t\t\tvalue of n2: " << n2
         << "\naddress of n3: " << &n3
         << "\taddress of n4: " << &n4
         << "\nvalue of n3: " << n3
         << "\t\t\tvalue of n4: " << n4
         << "\nMaking the first call to swap()" << endl;
    swap(n1,n2);
    cout << "After the first call to swap():\n"
         << "address of n1: " << &n1
         << "\taddress of n2: " << &n2
         << "\nvalue of n1: " << n1
         << "\t\t\tvalue of n2: " << n2
         << "\nMaking the second call to swap()" << endl;
    swap(n3,n4);
    cout << "After the second call to swap():\n"
         << "address of n3: " << &n3
         << "\taddress of n4: " << &n4
         << "\nvalue of n3: " << n3
         << "\tvalue of n4: " << n4 << endl;
    return 0;
}

