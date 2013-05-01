
#include "vect1.h"

int main() {
    Vect a(60), b[20];

    b[1][5] = 7;
    cout << " 1 element 5 = "<< b[1][5] << endl;
    for (int i = 0; i <= a.ub(); ++i)
        a[i] = 2 * i + 1;
    for (int i = a.ub(); i >= 0; --i)
        cout << ((a[i] < 100) ? " " : "" )
        << ((a[i] < 10) ? " " : "" )
        << a[i]
        << ((i % 10) ? "  " : "\n");
    cout << endl;
    cout << "Now try to access an out-of-range index"
    << endl;
    cout << a[62] << endl;
}


