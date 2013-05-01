#include <iostream>
using namespace std;

int main() {
    int* jp = new int(13); /* Allocate and initialize. */
    cout << jp << '\t' << *jp << endl;
    delete jp;
    delete jp;             /* Error: pointer already deleted. */
    jp = new int(3);       /* Reassign the pointer, memory leak. */
    cout << jp << '\t' << *jp << endl;
    jp = new int(10);      /* Reassign the pointer, memory leak. */
    cout << jp << '\t' << *jp << endl;
    int* kp = new int(17);
    cout << kp << '\t' << *kp << endl;
    return 0;
}
/*OUT
OOP> g++ pathologydemo1.cpp
OOP> ./a.out
0x8049e08       13
0x8049e08       3
0x8049e08       10
Segmentation fault
OOP>
*/
