#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
//start id="student"
class Student  {
 public:
    Student(QString nm, long id, QString major, int year = 1);
    virtual ~Student() {}                /* We added the keyword virtual here. */
    virtual QString getClassName() const;/* We added virtual here also. */
    QString toString() const;            /* This should also be virtual.*/
 private:
    QString m_Name;
    QString m_Major;
    long m_StudentId;
 protected:
    int m_Year;
    QString yearStr() const;
};
//end
class Undergrad: public Student {
 public:
    Undergrad(QString name, long id, QString major, int year, int sat);
    QString getClassName() const;
    QString toString() const;
 private:
    int m_SAT;                           /* Scholastic Aptitude Test score total */

};

class GradStudent : public Student {
 public:
    enum Support { ta, ra, fellowship, other };
    GradStudent(QString nm, long id, QString major,
                int yr, Support support);

    QString getClassName() const ;
    QString toString() const;
 protected:
    static QString supportStr(Support sup) ;
 private:
    Support  m_Support;
};

#endif        //  #ifndef STUDENT_H

