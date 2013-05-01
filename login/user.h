#ifndef USER_H
#define USER_H

#include <dataobject.h>

/** Contains the extra state information about a user. */
class User : public DataObject {
    Q_OBJECT
    Q_PROPERTY( QString Name READ getName WRITE setName );
 public:
    User(QObject* parent=0);

 public slots:
    void setName(const QString& name);
    QString getName() const;
 private:
    QString m_Name;
    // TODO: add quest, favorite color
};

#endif

