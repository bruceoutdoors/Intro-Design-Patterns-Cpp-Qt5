#include <QDebug>
#include <QString>
#include "vtable.h"

Base::Base() {
    m_X = 4;
    m_Y = 12;
    qDebug() << " Base::Base: " ;
    virtualFun();
}

Derived::Derived() {
    m_X = 5;
    m_Y = 13;
    m_Z = 22;
}

void Base::virtualFun() const {
    QString val=QString("[%1,%2]").arg(m_X).arg(m_Y);
    qDebug() << " VF: the opposite of Acid: " << val;
}

void Derived::virtualFun() const {
    QString val=QString("[%1,%2,%3]")
        .arg(m_X).arg(m_Y).arg(m_Z);
    qDebug() << " VF: add some treble: " ;
}

Base::~Base() {
    qDebug() << " ~Base() " ;
    virtualFun();
}

Derived::~Derived() {
    qDebug() << " ~Derived() " ;
}


int main() {
    Base *b = new Derived;  /* Base::virtualFun() is called */ 
    b->virtualFun();        /* calls Derived::virtualFun() using the vtable and runtime binding */
    delete b;               /* Base::virtualFun() is called */
}

