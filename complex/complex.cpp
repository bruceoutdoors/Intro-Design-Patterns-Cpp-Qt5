#include "complex.h"
#include <iostream>
using namespace std;

//start id=friends

ostream& operator<<(ostream& out, const Complex& c) {
    out << '(' << c.m_Re << ',' << c.m_Im << ')' ;
    return out;
}

Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1.m_Re - c2.m_Re, c1.m_Im - c2.m_Im);
}
//end

Complex operator/(const Complex& c1, const Complex& c2) {
    double cmsq = c2.m_Re * c2.m_Re + c2.m_Im * c2.m_Im;
    double re = (c1.m_Re * c2.m_Re + c1.m_Im * c2.m_Im)/cmsq;
    double im = (c1.m_Im * c2.m_Re - c1.m_Re * c2.m_Im)/cmsq;
    return Complex(re, im);
}

Complex operator*(const Complex& c1, const Complex& c2) {
    double re = c1.m_Re * c2.m_Re - c1.m_Im * c2.m_Im;
    double im = c1.m_Re * c2.m_Im + c1.m_Im * c2.m_Re;
    return Complex(re, im);
}


Complex::Complex(double re, double im)  /* default arguments: re = 0, im = 0 */
        : m_Re(re), m_Im(im)  { }

//start id=members
Complex& Complex::operator+=(const Complex& c) {
    m_Re += c.m_Re;
    m_Im += c.m_Im;
    return *this;
}

Complex Complex::operator+(const Complex& c2) {
    return Complex(m_Re + c2.m_Re, m_Im + c2.m_Im);
}

Complex& Complex::operator-=(const Complex& c) {
    m_Re -= c.m_Re;
    m_Im -= c.m_Im;
    return *this;
}


//end

