
#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>

QString objToString(const QObject* obj) {
    QStringList result;
    const QMetaObject* meta = obj->metaObject();
    result += QString("class %1 : public %2 {")
              .arg(meta->className()).arg(meta->superClass()->className());
    for (int i=0; i < meta->propertyCount(); ++i) {
        const QMetaProperty qmp = meta->property(i);
        QVariant value = obj->property(qmp.name());
        result += QString("  %1 %2 = %3;")
            .arg(qmp.typeName()).arg(qmp.name())
            .arg(value.toString()); }
    result += "};";
    return result.join("\n");
}

