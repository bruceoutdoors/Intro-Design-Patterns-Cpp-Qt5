#include "qdatetime.h"

class Person {
public:
    Person(QString name, QDate birthdate)
    QObject(name.ascii()),
    m_Birthdate(birthdate) {}

    Person(const Person& p) : QObject(p),
    m_Birthdate(p.m_Birthdate) {}

private:
    QDate m_Birthdate;
};

class Student : virtual public Person {       /* Note keyword virtual
    here. */
    // other class members
//end
//start
};

class Teacher : virtual public Person {       /* virtual inheritance. */
    // other class members
//end
//start
}


class GraduateTeachingFellow :
    public Student, public Teacher {          /* virtual not needed here. */
public:
    GraduateTeachingFellow(const Person& p,
                           const Student& s, const Teacher& t):
    Person(p), Students(s), Teacher(t) {}     /* It is necessary to initialize all virtual base classes explicitly in multiply-derived classes, to resolve ambiguity about how they should be initialized. */
}