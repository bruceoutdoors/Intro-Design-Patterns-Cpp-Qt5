#include <iostream>
#include "sstring.h"
using namespace std;

void passByValue(SString v) {
    cout << v << v.refcount() << endl; /* refcount=2 */
    v = "somethingelse";
    cout << v << v.refcount() << endl; /* refcount=1 */
}

int main (int argc, char* argv[]) {
    SString s = "Hello";
    passByValue(s);
    cout << s << s.refcount() << endl; /* refcount=1 */
}
