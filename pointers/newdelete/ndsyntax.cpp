#include <iostream>
using namespace std;

int main() {
 int* ip = 0;               /* null pointer */
 delete ip;                 /* has no effect at all - ip is still null. */
 if(ip) cout << "non-null" << endl;
 else cout << "null" << endl;
 ip = new int;              /* allocate space for an int */
 int* jp = new int(13);     /* allocate and initialize */
 //[...]      
 delete ip;                 /* Without this, we have a memory leak. */
 delete jp;
}
