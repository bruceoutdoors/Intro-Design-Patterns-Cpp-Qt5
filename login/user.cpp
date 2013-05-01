#include "user.h"

User::User(QObject* parent) {
    setParent(parent);
}

void User::setName(const QString &name){
    m_Name = name;
}

QString User::getName() const {
    return m_Name;
}

