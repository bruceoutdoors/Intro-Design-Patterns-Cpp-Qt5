#ifndef VARIANT_H
#define VARIANT_H
#include <QVariant>

/** @short extra user-defined values for QVariant::Type
*/   

namespace Variant {
  const QVariant::Type File = static_cast<QVariant::Type>(128);
  const QVariant::Type Dir = static_cast<QVariant::Type>(129);
}

#endif

