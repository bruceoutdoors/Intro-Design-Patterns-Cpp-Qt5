#include <iostream>
using namespace std;
//start
int main() {
    int myint = 5;
    int* ptr1 = &myint;
    cout << "*ptr1 = " << *ptr1 << endl;
    int anotherint = 6;
//  *ptr1 = &anotherint;   /* Error, invalid conversion from int* to int.  */
    
    int* ptr2;             /* Uninitialized pointer. */
    cout << "*ptr2 = " << *ptr2 << endl;
    *ptr2 = anotherint;    /* Unpredictable results. */

    int yetanotherint = 7;
    int* ptr3;
    ptr3 = &yetanotherint; /* Regular assignment. */
    cout << "*ptr3 = " << *ptr3 << endl;
    *ptr1 = *ptr2;         /* Dangerous assignment! */
    cout << "*ptr1 = " << *ptr1 << endl;

    return 0;
}
//end
/*OUT
*ptr1 = 5
*ptr2 = 1256764
*ptr3 = 7
*ptr1 = 6
*/

