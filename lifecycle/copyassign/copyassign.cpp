#include <QTextStream>
#include "fraction.h"

int main() {
    QTextStream cout(stdout);
    Fraction twothirds(2,3);                /* Using 2-arg constructor. */
    Fraction threequarters(3,4);
    Fraction acopy(twothirds);              /* Using copy constructor. */
    Fraction f4 = threequarters;            /* Also using copy constructor. */
    cout << "after declarations - " << Fraction::report();
    f4 = twothirds;                         /* Assignment. */
    cout << "\nbefore multiply - " << Fraction::report();
    f4 = twothirds.multiply(threequarters); /* Several objects are created here. */
    cout << "\nafter multiply - " << Fraction::report() << endl;
    return 0;
}

