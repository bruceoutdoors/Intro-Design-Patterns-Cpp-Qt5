#ifndef BANK_H
#define BANK_H
#include <QList>
#include <QString>
//start
class Account;

class Bank {
 public:
    Bank& operator<< (Account* acct); /* This is how 
         to add object pointers to m_Accounts. */
    ~Bank();
    QString getAcctListing() const;
 private:
    QList<Account*> m_Accounts;
};
//end
#endif

