#include <QString>
#include <QTextStream>

QTextStream cout(stdout);

class Fraction {
public:
    Fraction(int n, int d = 1)          /* Conversion constructor. */ 
        : m_Numerator(n), m_Denominator(d) {}

    operator double() const {           /* Conversion operator. */
        return (double) m_Numerator / m_Denominator;
    }  
    
    operator QString () const {
        return  QString("%1/%2").arg(m_Numerator).arg(m_Denominator);
    }
private:
    int m_Numerator, m_Denominator;
};

QTextStream& operator<< (QTextStream& os, const Fraction& f) {
    os << static_cast<QString> (f);     /* Explicit cast calls conversion operator. */
    return os;
}

int main() {
    
    Fraction frac(1,3);
    Fraction frac2(4);                  /* Conversion constructor call. */
    double d = frac;                    /* Calls conversion operator. */
    QString fs = frac;                  /* Another conversion operator call. */
    cout << "fs= " << fs << "  d=" << d << endl;
    cout << frac << endl;               /* Operator<<()  called directly. */
    cout << frac2 << endl;
    return 0;
}
