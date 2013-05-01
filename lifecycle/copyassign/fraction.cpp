#include "fraction.h"
#include <assert.h>

//start
int Fraction::s_assigns = 0;     /* Static member definitions. */
int Fraction::s_copies = 0;
int Fraction::s_ctors = 0;

Fraction::Fraction(const Fraction& other)
   :  m_Numer(other.m_Numer), m_Denom(other.m_Denom) {
   ++s_copies;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {        /* operator=() should always do nothing in the case of self-assignment. */
        m_Numer = other.m_Numer;
        m_Denom = other.m_Denom;
        ++s_assigns;
    }
    return *this;                /* operator=() should always return *this,
    to allow for chaining i.e. a=b=c. */
}
//end

Fraction::Fraction(int n, int d) : m_Numer(n), m_Denom(d) {
   assert(m_Denom != 0);
   ++s_ctors;
}

Fraction Fraction::multiply(Fraction f2) {
   return Fraction (m_Numer*f2.m_Numer, m_Denom*f2.m_Denom);
}

QString Fraction::report() {
   return QString(" [assigns: %1 copies: %2 ctors: %3] ")
        .arg(s_assigns).arg(s_copies).arg(s_ctors);
}

