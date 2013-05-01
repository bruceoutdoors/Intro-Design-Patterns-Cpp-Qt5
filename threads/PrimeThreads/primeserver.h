#ifndef PRIMESERVER_H
#define PRIMESERVER_H

#include <QObject>
#include <QMutex>
#include <QTime>
#include <QSet>
#include <QFuture>
#include <QFutureWatcher>
//start
/** A multithreaded example for calculating prime numbers. 
    Creates multiple QThread workers for distributing 
    the calculation across multiple cores, and lets you compare that
    to the QtConcurrent solution using filter().  
*/
class PrimeServer : public QObject
{
    Q_OBJECT
public:
    explicit PrimeServer(QObject* parent =0);
    /** Start calculating prime numbers
        @param highestPrime highest number to check. 
        @param numThreads number of threads to use. 
        @param concurrent if true, use QtConcurrent::filter intead of mutexed threads. 
    */
    void doCalc(int numThreads, int highestPrime, bool concurrent = false);
    /** This method is thread-safe */
    int nextNumberToCheck();
    /** This method is thread-safe */
    void foundPrime(int );   
    bool isRunning() const;
public slots:
    void cancel();
private slots:
    void handleThreadFinished();
signals:
    void results(QString);
private:
    int m_numThreads;
    bool m_isRunning;    
    QList<int> m_primes;
    int m_nextNumber;
    int m_highestPrime;
    QTime m_timer;
    QMutex m_nextMutex;
    QMutex m_listMutex;
    QSet<QObject*> m_threads;
//end
//start id=concurrent 
private slots:
    void handleWatcherFinished();
    void doConcurrent();
private:
    bool m_concurrent;
    int m_generateTime;             /* Time spent generating input data. */    
    QFutureWatcher<void> m_watcher;
};
//end
#endif // PRIMESERVER_H
