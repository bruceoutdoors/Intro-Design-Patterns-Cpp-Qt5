#include  "account.h"

//start id=ctor
Account::Account(unsigned acctNum, double balance, QString owner) :
     m_AcctNum(acctNum), m_Balance(balance), m_Owner(owner)
    { }

JointAccount::JointAccount (unsigned acctNum, double balance,
                            QString owner, QString jowner)
    :Account(acctNum, balance, owner),
     m_JointOwner(jowner)   /* Base class initialization required. */
     { }

JointAccount::JointAccount (const Account& acc, QString jowner)
    :Account(acc),          /* Compiler-generated copy constructor call. */
     m_JointOwner(jowner)
    { }
//end

