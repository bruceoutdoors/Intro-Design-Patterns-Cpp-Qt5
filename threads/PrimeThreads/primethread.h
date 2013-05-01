#ifndef PRIMETHREAD_H
#define PRIMETHREAD_H

#include <QThread>
#include "primeserver.h"

/** A consumer thread for the Prime Number solution. */

class PrimeThread : public QThread
{
    Q_OBJECT
public:
    explicit PrimeThread(PrimeServer *parent);
    void run();                         /* Required override. */
private:
    PrimeServer *m_server;

};

#endif // PRIMETHREAD_H
