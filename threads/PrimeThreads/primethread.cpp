#include "isprime.h"
#include "primethread.h"

//start
PrimeThread::PrimeThread(PrimeServer *parent) 
: QThread(parent), m_server(parent) { }

void PrimeThread::run() {
    int numToCheck = m_server->nextNumberToCheck();
    while (numToCheck != -1) {
        if (isPrime(numToCheck)) 
            m_server->foundPrime(numToCheck);
        numToCheck = m_server->nextNumberToCheck();
    }
}
//end
