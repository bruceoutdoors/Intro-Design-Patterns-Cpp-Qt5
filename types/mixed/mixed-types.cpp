#include <iostream>
using namespace std;

int main() {
    int i, j = 88;
    double d = 12314.8723497;
    cout << "initially d = " << d
         << "  and j = " << j << endl;
    cout << "The sum is: " << j + d << endl;
    i = d;
    cout << "after demoting d,  i = " << i << endl;
    d = j;
    cout << "after promoting j,  d = " << d << endl;
}
