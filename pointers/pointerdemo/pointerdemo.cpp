#include <QTextStream>

int main() {
    QTextStream cout(stdout);
    int x = 4;
    int* px = 0 ;            /* Type modifier */
    px = &x;
    cout << "x = " << x
         << " *px = " << *px /* Unary dereference operator */
         << " px = " << px
         << " &px = " << &px << endl;
    x = x + 1;
    cout << "x = " << x
         << " *px = " << *px
         << " px = " << px << endl;
    *px = *px + 1;
    cout << "x = " << x
         << " *px = " << *px
         << " px = " << px << endl;
    return 0;
}


/*out
OOP> ./pointerdemo
x = 4 *px = 4 px = 0xbffff514 &px = 0xbffff510
x = 5 *px = 5 px = 0xbffff514
x = 6 *px = 6 px = 0xbffff514
OOP>
*/
