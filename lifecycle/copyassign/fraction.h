#ifndef FRACTION_H
#define FRACTION_H
#include <QString>

//start
class Fraction {
 public:
    Fraction(int n, int d) ;                        /* Regular constructor */
    Fraction(const Fraction& other) ;               /* Copy constructor */
    Fraction& operator=(const Fraction& other) ;    /* Copy assignment operator */
    Fraction multiply(Fraction f2) ;
    static QString report() ;
 private:
    int m_Numer, m_Denom;
    static int s_assigns;
    static int s_copies;
    static int s_ctors;
};
//end
#endif
