/** File fac2.cpp
    factorial function computes n! for non-negative n.
    Uses standard IO library. 
*/

#include <iostream> 

long factorial(long n) {
    long ans = 1;
    for (long i = 2; i <= n; ++i) {
        ans = ans * i;
        if (ans < 0) {
            return -1;
        }
    }
    return ans;
}

int main() {
    using namespace std;
    cout << "Please enter n: " << flush;
    long n;        /* long int  */
    cin >> n;      /* read from stdin, 
                      try to convert to long */ 

    if (n >= 0) { 
        long nfact = factorial(n);
        if (nfact < 0) {
            cerr << "overflow error: " 
                 << n << " is too big." << endl;
        }
        else {
            cout << "factorial(" << n << ") = "
                 << nfact << endl;
        }
    }
    else {
        cerr << "Undefined:  "
             << "factorial of a negative number: " << n << endl;
    }
    return 0;
}

