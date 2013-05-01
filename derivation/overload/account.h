#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDate>
#include <QString>
//start
class Account {
public:
    Account(unsigned acctno, double bal, QString owner);
    virtual ~Account() { }
    virtual void deposit(double amt);
    virtual QString toString() const;
    virtual QString toString(char delimiter);   /* Overloaded
       function. */
protected:
    unsigned  m_AcctNo;
    double    m_Balance;
    QString   m_Owner;
};

class InsecureAccount: public Account {
public:
    InsecureAccount(unsigned acctno, double bal, QString owner);
    QString toString() const;                   /* Overrides base method
       and hides toString(char). */
    void deposit(double amt, QDate postDate);   /* Does not
       override any method, but hides all Account::deposit()
       methods. */
};
//end
#endif        //  #ifndef ACCOUNT_H

