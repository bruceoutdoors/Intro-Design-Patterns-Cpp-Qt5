/* Computes and prints n! for a given n.
   Uses several basic elements of C++. */

#include <iostream>                         /* Standard C++ library -
       In older versions of C++, you might find <iostream.h>
       instead, but that version is regarded as "deprecated"; i.e.
       its use is discouraged.*/
int main() {                                /* Start of function "main" which returns an int */
    using namespace std;                    /* Permits us to use the
                            symbols cin, cout, and endl without prefixing each name with std:: */
    // Declarations of variables
    int factArg = 0 ;                       /* C style initialization syntax */
    int fact(1) ;                           /* C++ style initialization syntax */
    do {                                    /* Start of "do..while" loop */
        cout << "Factorial of: ";           /* Write to standard output */
        cin >> factArg;                     /* Read from standard input and convert to int */
        if ( factArg < 0 ) {
            cout << "No negative values, please!" << endl;
        }                                   /* End of if block */
    } while (factArg < 0) ;                 /* if false, break out of do loop */
    int i = 2;
    while ( i <= factArg ) {                /* Start of while loop  */
        fact = fact * i;
        i = i + 1;
    }                                       /* End of while block */
    cout << "The Factorial of " << factArg << " is: " << fact << endl;
    return 0;                               /* When main returns 0, that normally means "no errors"  */
}                                           /* End of main block */
