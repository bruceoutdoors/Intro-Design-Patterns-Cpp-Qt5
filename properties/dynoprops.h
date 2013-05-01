#ifndef DYNOPROPS_H
#define DYNOPROPS_H

#include <QObject>
#include <QString>
class QDataStream;

/** A class for demonstrating dynamic properties. */
//start
class DynoProps : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString someString READ someString WRITE setSomeString);
 public:
    friend QDataStream& operator<<(QDataStream& os, const DynoProps& dp);
    friend QDataStream& operator>>(QDataStream& is, DynoProps& dp);
    QString someString() { return m_someString; }
    void setSomeString(QString ss) { m_someString = ss; }
    QString propsInventory();
 private:
    QString m_someString;
};
//end

#endif        //  #ifndef DYNOPROPS_H
