#include "primeserver.h"
#include "primethread.h"
#include "isprime.h"
#include <QtGui>

PrimeServer::PrimeServer(QObject* parent)
: QObject(parent), m_concurrent(false) {
    m_isRunning = false;
}

//start id=create
void PrimeServer::
doCalc(int numThreads, int highestPrime, bool concurrent) {
    m_isRunning = true;
    m_numThreads = numThreads;
    m_concurrent = concurrent;
    m_highestPrime = highestPrime;
    m_primes.clear();
    m_primes << 2 << 3;
    m_threads.clear();
    m_nextNumber = 3;
    m_timer.start();
    if (!concurrent) {
         for (int i=0; i<m_numThreads; ++i) {
            PrimeThread *pt = new PrimeThread(this);    /* Child thread is not started yet. */
            connect (pt, SIGNAL(finished()), this,
                     SLOT(handleThreadFinished()));
            m_threads << pt;
            pt->start();                                /* Child thread executes run(). */
         }
    }
    else doConcurrent();
}
//end
//start id=handleFinished
void PrimeServer::handleThreadFinished() {
    QObject* pt = sender();                         /* The QThread is our sender. */
    m_threads.remove(pt); 
    pt->deleteLater();
    if (!m_threads.isEmpty()) return;               /* Others are still running. */
    int numPrimes = m_primes.length();
    QString result = QString("%1 mutex'd threads %2 primes in %3"
                             "miliseconds. ").arg(m_numThreads)
                             .arg(numPrimes).arg( m_timer.elapsed());
    QString r2 = QString(" %1 kp/s")
                  .arg(numPrimes / m_timer.elapsed());
    qDebug() << result << r2;
    emit results(result + r2);
    m_isRunning = false;
}
//end

//start id=doConcurrent
void PrimeServer::doConcurrent() {
    QThreadPool::globalInstance()->setMaxThreadCount(m_numThreads);
    m_primes.clear();
    m_primes << 2;
    for (m_nextNumber=3; m_nextNumber<=m_highestPrime; 
         m_nextNumber += 2) {
       m_primes << m_nextNumber;
    } 
    m_generateTime = m_timer.elapsed();
    qDebug() << m_generateTime << "Generated " 
             << m_primes.length() << " numbers";
    connect (&m_watcher, SIGNAL(finished()), this,
             SLOT(handleWatcherFinished()));
    m_watcher.setFuture(                            /* QFutureWatcher for 
                monitoring progress. */
        QtConcurrent::filter(m_primes, isPrime));   /* Non-blocking, in-place filter() returns a QFuture. */
}

void PrimeServer::handleWatcherFinished() {
    int numPrimes = m_primes.length();
    int msecs = m_timer.elapsed();
    QString result = 
      QString("%1 thread pool %2 primes in %4/%3 milliseconds"
              "(%5% in QtConcurrent).") .arg(m_numThreads)
              .arg(numPrimes).arg(msecs).arg(msecs-m_generateTime)
              .arg((100.0 * (msecs-m_generateTime)) / msecs);
    QString r2 = QString(" %1 kp/s").arg(numPrimes / msecs);
    qDebug() << result << r2;
    m_watcher.disconnect(this);
    emit results(result + r2);
    m_isRunning = false;
}
//end
//start id=mutex
int PrimeServer::nextNumberToCheck() {
    QMutexLocker locker(&m_nextMutex);              /* Scope-based mutex works from multiple return points. */
    if (m_nextNumber >= m_highestPrime) {
        return -1;
    }
    else {
        m_nextNumber+= 2;
        return m_nextNumber;
    }
}

void PrimeServer::foundPrime(int pn) {
    QMutexLocker locker(&m_listMutex);              /* This method also must be made thread-safe. */
    m_primes << pn;
}
//end
bool PrimeServer::isRunning() const {
    return m_isRunning;
}
//start id="cancel"
void PrimeServer::cancel() {
    QMutexLocker locker(&m_nextMutex);
    m_nextNumber = m_highestPrime+1;
//end
    m_isRunning = false;
    if (m_concurrent) {
        if (m_watcher.isRunning()) { 
            m_watcher.cancel();
            m_watcher.waitForFinished();
        }
    }
}
//end
