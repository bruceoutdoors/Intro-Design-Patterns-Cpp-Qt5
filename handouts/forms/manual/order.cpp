#include "order.h"
#include <QString>

QString Order::toString() const {
    return QString("%1 %2 (%3)@ $ %4   total: %5").arg(m_name)
    .arg(m_added.toString("yyyyMMdd")).arg(m_quantity)
    .arg(m_price).arg(m_quantity*m_price);
}
