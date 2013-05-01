#include <QTextStream>
#include "fraction.h"

int main() {
    const int DASHES = 30;
    QTextStream cout(stdout);
    
    {                                   /* Nested scope, inner block. */
        int i;
        for (i = 0; i < DASHES; ++i)
            cout << "=";
        cout << endl;
    }   

    cout << "i = " << i << endl;        /* Error: i no longer exists, so it is not visible in this scope. */
    Fraction f1, f2;
    f1.set(3, 4);
    f2.set(11,12);                      /* Set through a member function. */
    f2.m_Numerator = 12;                /* Error, m_Numerator is visible but not accessible. */
    cout << "The first fraction is: " << f1.toString() << endl;
    cout << "\nThe second fraction, expressed as a double is: "
         << f2.toDouble() << endl;
    return 0;
}
