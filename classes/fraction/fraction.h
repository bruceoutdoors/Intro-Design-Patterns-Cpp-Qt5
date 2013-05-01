#ifndef _FRACTION_H_ 
#define _FRACTION_H_  

#include <QString>


class Fraction {
public:
    void set(int numerator, int denominator);
    double toDouble() const;
    QString toString() const;
private:
    int m_Numerator;
    int m_Denominator;
};

#endif

