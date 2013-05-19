#include <qglobal.h>
#include <QTextDocument>
#include <QTime>
#include <QMetaObject>
#include <QMetaProperty>
#include <QList>
#include <QDebug>
#include "qobjectwriter.h"

QObjectWriter::
QObjectWriter(const VariantWriter* vwriter, bool children)
   : m_vwriter (vwriter), m_children(children) 
{ }

QStringList QObjectWriter::
propertyNames(const QObject* obj) const {
    const QMetaObject* meta = obj->metaObject();
    QStringList retval;

    QList<QByteArray> dynamicProps = obj->dynamicPropertyNames();

    foreach (const QByteArray& qba, dynamicProps)
        retval << QString(qba);

    for (int i=0; i<meta->propertyCount(); ++i)
        retval << meta->property(i).name();

    return retval;
}

void QObjectWriter::
mapType(QVariant::Type t, VariantWriter* vw) {
    m_map.insert(t, vw);
}

QString QObjectWriter::
toString(const QVariant& val, const QMetaProperty& mprop) const {
    QString result;
    QVariant::Type t = mprop.type();
    if (t == QVariant::Time) {
//        QTime t = qVariantValue<QTime>(val);
        QTime t = val.value<QTime>();
        if (t.hour() > 0) {
            return t.toString("hh:mm:ss");
        }
        else {
            return t.toString("m:ss");
        }
    }
    if (mprop.isEnumType()) {
        int value = val.toInt();
        QMetaEnum menum = mprop.enumerator();
        if (mprop.isFlagType()) {
            QStringList selectedFlags;
            int kc = menum.keyCount();
            for (int j=0; j<kc; ++j) {
                if (menum.value(j) == 0) continue;
                if ((value & menum.value(j)) == menum.value(j)) {
                    selectedFlags << menum.key(j);
                }
            }
            result = selectedFlags.join("|") + QString(" (%1)").arg(val.toInt());
        }
        else result = QString("%1 (%2)").arg(menum.valueToKey(value)).arg(val.toInt());
        return result;
    }
    if (m_map.contains(t)) {
        VariantWriter* vw = m_map[t];
        result = vw->toString(val, mprop);
    }
    else if (m_vwriter != 0 && result == QString())
        result = m_vwriter->toString(val, mprop);
    if (result == QString())
//        result = Qt::escape(val.toString());
        result = QString(val.toString()).toHtmlEscaped();
    else
//        result = Qt::escape(result);
        result = QString(result).toHtmlEscaped();
    return result;
}
//start
QString QObjectWriter::
toString(const QObject* obj, int indentLevel) const {
    QStringList result;
    QString indentspace;
    indentspace.fill(' ', indentLevel * 3 );
    QString className = obj->metaObject()->className();
    QString objectName = obj->objectName();
    QStringList propnames = propertyNames(obj);
    foreach (const QString &propName, propnames) {
        if (propName == "objectName") continue;
        QVariant qv = obj->property(propName.toLatin1());

        if (propName == "className") {
               className = qv.toString();
               continue;
        }
        const QMetaObject* meta = obj->metaObject();
        int idx = meta->indexOfProperty(propName.toLatin1());
        QMetaProperty mprop = meta->property(idx);

        result <<
        QString("%1  <property name=\"%2\" type=\"%3\" value=\"%4\" />")
            .arg(indentspace).arg(propName).
            arg(qv.typeName()).arg(toString(qv, mprop));
    }
    /* Query over QObjects */
    if (m_children) {
//        QList<QObject*> childlist =
//               qFindChildren<QObject*>(obj, QString());
        QList<QObject*> childlist =
               obj->findChildren<QObject*>(QString());

        foreach (const QObject* child, childlist) {
            if (child->parent() != obj) {
      //          qDebug() << "This is not my child!!";
                continue;
            }
            if (child != 0) {
                result << toString(child, indentLevel+1);
            }
        }
    }

    result.insert(0, QString("\n%1<object class=\"%2\" name=\"%3\" >")
        .arg(indentspace).arg(className).arg(objectName));
    result << QString("%1</object>\n").arg(indentspace);
    return result.join("\n");
}
//end
