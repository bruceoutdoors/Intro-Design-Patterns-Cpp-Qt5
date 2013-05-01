#include <iostream>
#include "demostruct.h"

//start
void printFraction(Fraction f) {        /* Passing a struct by value
    could be expensive if it has large components. */
    cout << f.numer << "/" << f.denom << endl;
    cout << "  =? " << f.description << endl; 
}
int main() {  
    Fraction f1;
    f1.numer = 4;
    f1.denom = 5;
    f1.description = "four fifths";   
    Fraction f2 = {2, 3, "two thirds"}; /* Member
       Initialization. */
    
    f1.numer = f1.numer + 2;            /* Client code can change individual data members. */
    printFraction(f1);
    printFraction(f2);
    return 0;
}
/*OUT
  6/5
  =? four fifths
  2/3  
  =? two thirds
*/

