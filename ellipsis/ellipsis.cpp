#include <cstdarg>
#include <iostream>
using namespace std;

double mean(int n ...) {    /* First parameter is number of args.*/
    va_list ap;             /* Sequentially points to each unnamed arg. */
    double sum(0);
    int count(n);
    va_start(ap, n);        /* Now, ap points to first unnamed arg. */
    for (int i = 0; i < count; ++i) {
        sum += va_arg(ap, double);
    }
    va_end(ap);             /* Clean up before returning. */
    return sum / count;
}

int main() {
    cout << mean(4, 11.3, 22.5, 33.7, 44.9) << endl;
    cout << mean (5, 13.4, 22.5, 123.45, 421.33, 2525.353) << endl;
}

