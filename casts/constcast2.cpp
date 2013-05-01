#include <iostream>

void f2(int& n) {
    ++n;
}

void f1(const int& n, int m) {
    if (n < m) 
        f2(const_cast<int&>(n));
}

int main() {
    using namespace std;
    int num1(10), num2(20);
    f1(num1, num2);
    cout << num1 << endl;
}
