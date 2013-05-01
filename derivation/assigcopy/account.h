#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>
#include <QDebug>


//start id=account
class Account {
 public:
    Account(unsigned acctNum, double balance, QString owner);
    virtual ~Account(){
      qDebug() << "Closing Acct - sending e-mail " 
               << "to primary acctholder:" << m_Owner; }
    virtual QString getName() const {return m_Owner;}
    // other virtual functions
 private:
    unsigned  m_AcctNum;
    double    m_Balance;
    QString    m_Owner;
};
//end
//start id=jointaccount
class JointAccount : public Account {
 public:
  JointAccount (unsigned acctNum, double balance, 
                QString owner, QString jowner);
  JointAccount(const Account & acct, QString jowner);
  ~JointAccount() {
     qDebug() << "Closing Joint Acct - sending e-mail "
              << "to joint acctholder:" << m_JointOwner; }
  QString getName() const { 
    return QString("%1 and %2").arg(Account::getName())
                   .arg(m_JointOwner);
  }
  // other overrides
 private:
  QString m_JointOwner;
};
//end
#endif        //  #ifndef ACCOUNT_H

