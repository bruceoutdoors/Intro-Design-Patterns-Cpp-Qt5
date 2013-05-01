
#include "enum.h"
#include <QDebug>

Enum::Enum(int enumval) : m_Val(enumval) {
    m_Val = enumval;
}
Enum::Enum(const Enum& other) {
	m_Val = other.m_Val;
}

Enum::~Enum() {}

bool Enum::operator=(int other)  {
    if ((other >= 0) && (other <= nameMap().size())) {
        m_Val = other;
        return true;
    }
    qDebug() << "Enum::operator=() Undefined other: " << other;
    return false;
}

QStringList Enum::names() const {
    QMap<int, QString> map;
    foreach (const QString &n, nameMap().keys()) {
        int v = nameMap()[n];
        map[v]=n;
    }
    return map.values();
}

bool Enum::fromString(QString val) {
    const QRegExp numbers("\\d+");
    if (numbers.exactMatch(val)) {
        m_Val = val.toInt();
        return true;
    }

    const NameMap& nm = nameMap();
    if (nm.contains(val)) {
        m_Val = nm[val];
//        qDebug() << " fromString(" << val << ") = " << m_Val;
        return true;
    } else {
        foreach (const QString &name, nm.keys()) {
           if (name.toLower()==val.toLower()) {
                m_Val = nm[name];
//                qDebug() << " fromString(" << val << ") = " << m_Val;
                return true;
            }
        }
    }
//    qDebug() << "fromString: undefined " << val;
    return false;
}


bool Enum::operator=(QString other) {
    return fromString(other);

/*    if (nameMap()names().contains(other)) {
        m_Val = names().indexOf(other);
        return true;
    }
    qDebug() << "operator= Undefined other: " << other;
    return false;
*/
}

int Enum::intValue() const {
    return m_Val;
}

bool Enum::operator==(const QString& other) const {
    int v = nameMap()[other];
    return m_Val == v;
}

QString Enum::toString() const {
    foreach (const QString &n , nameMap().keys()) {
        if (nameMap()[n] == m_Val)
            return n;
    }
    return QString("Enum::Unknown");
}

QTextStream& operator<<(QTextStream& ts, const Enum& enumval) {
    return ts << enumval.intValue();
}

QTextStream& operator>>(QTextStream &is, Enum& enumval) {
    int i;
    is >> i;
    enumval.setIntValue(i);
    return is;
}

QDataStream& operator<<(QDataStream& ds, const Enum& e) {
    return ds << e.toString();
}

QDataStream& operator>>(QDataStream& ds, Enum& e) {
    QString str;
    ds >> str;
    bool success = e.fromString(str);
    if (!success) {
        qCritical() << "Unrecognized enumvalue: " << str;
    }
    return ds;
}

NameMap& Enum::initMap(NameMap& nameMap, QStringList nameList,
                       bool & initialized, int startIndex) {
    if (!initialized) {
        for (int i=startIndex; i < nameList.count(); ++i) {
            int value = i;
            QString key=nameList[i];
            if (key.indexOf('=') > 0) {
                QStringList kvl = key.split("=");
                key = kvl[0];
                value = kvl[1].toInt();
            }
            // qDebug() << "map: " << key << " = " << value;
            nameMap[key]=value;
        }
        initialized=true;
    }
    return nameMap;
}


