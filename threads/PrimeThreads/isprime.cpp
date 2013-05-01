#include "isprime.h"
//start
#include "math.h"
bool isPrime(int toCheck) {
    if (toCheck < 4) return true;
    if (toCheck % 2 == 0) return false;
    int sqtocheck = sqrt(toCheck) + 1;
    for (int i=3; i<= sqtocheck; i += 2)
        if (toCheck % i == 0) return false;
    return true;
}
