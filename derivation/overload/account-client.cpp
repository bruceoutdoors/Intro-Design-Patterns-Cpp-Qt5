#include  "account.h"
#include  <QTextStream>

int main() {
    InsecureAccount acct(12345, 321.98, "Luke Skywalker");
    acct.deposit(6.23);             /*  Error! No matching function -
           hidden by deposit(double, int). */
    acct.m_Balance += 6.23;         /* Error! Member is protected,
         inaccessible. */
    acct.Account::deposit(6.23);    /* Hidden does not mean
        inaccessible. You can still access hidden public members
        via scope resolution. */
    // ... more client code
    return 0;
}

