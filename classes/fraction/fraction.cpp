#include <QString>
#include "fraction.h"


void Fraction::set(int nn, int nd) {
    m_Numerator = nn;
    m_Denominator = nd;
}

double Fraction::toDouble() const {
    return 1.0 * m_Numerator / m_Denominator;
}

QString Fraction::toString() const {
  return QString("%1 / %2").arg(m_Numerator).arg(m_Denominator);
}

