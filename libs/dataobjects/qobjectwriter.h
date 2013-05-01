#ifndef QOBJECTWRITER_H
#define QOBJECTWRITER_H

#include "dobjs_export.h"
#include <QString>
#include <QStringList>
#include <QObject>
#include <QMap>
#include <QVariant>

/** An easy way to provide additional writers for specific user types */

class DOBJS_EXPORT VariantWriter {
 public:
    /** @return QString() if you do not know how to handle this type */
    virtual QString toString(const QVariant& variant, const QMetaProperty& meta) const = 0;
};

/** Writes out QObject properties and child objects in
    an XML format that can be read in later. */
//start
class DOBJS_EXPORT QObjectWriter : public VariantWriter {
 public:
    /** @param vw an alternate VariantWriter for handling custom types */
    QObjectWriter(const VariantWriter* vw = 0, bool children=true);
    void mapType(QVariant::Type t, VariantWriter* vw);
    virtual QString toString(const QVariant& variant, const QMetaProperty& meta) const;
    virtual QStringList propertyNames(const QObject* obj) const ;
    virtual QString toString(const QObject* obj, int indentLevel = 0) const;
 private:
    const VariantWriter* m_vwriter;
    bool m_children;
    QMap<QVariant::Type, VariantWriter*> m_map;
};
//end
#endif        //  #ifndef QOBJECTWRITER_H
