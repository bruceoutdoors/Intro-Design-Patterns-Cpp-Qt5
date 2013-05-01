#include "complex.h"
#include <iostream>
#include <sstream>
using namespace std;

Complex::Complex(double realPart, double imPart)
    :   m_R(realPart), m_I(imPart)  /* Member initialization list. */
{ 
    cout << "complex(" << m_R << "," << m_I << ")" << endl;
}

Complex::Complex(double realPart) : 
    m_R(realPart), m_I(0) {
}

Complex::Complex() : m_R(0.0), m_I(0.0) {

}

string Complex::toString() const {
    ostringstream strbuf;
    strbuf << '(' << m_R << ", " << m_I << ')';
    return strbuf.str();
}

int main() {
    Complex C1;
    Complex C2(3.14);
    Complex C3(6.2, 10.23);
    cout << C1.toString() << '\t' << C2.toString() 
         << C3.toString() << endl;
}
       
