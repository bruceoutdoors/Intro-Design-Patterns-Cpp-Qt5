#include <iostream>
using namespace std;

void messAround(int* ptr) {
    *ptr = 34;       /* Change the value that is pointed to. */
    ptr = 0;         /* Change the address stored by ptr. Better not dereference this! */
}


int main() {
    int n(12);       /* Initialize an int. */
    int* pn(&n);     /* Initialize a pointer that points to n. */
    cout << "n = " << n << "\tpn = " << pn << endl;
    messAround(pn);  /* See what is changed by messAround(). */
    cout << "n = " << n << "\tpn = " << pn << endl;
    return 0;
}
/*out
n = 12  pn = 0xbffff524
n = 34  pn = 0xbffff524
*/
