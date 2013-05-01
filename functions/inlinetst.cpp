// Inline functions vs macros

#include <iostream>
#define  BADABS(X)   (((X) < 0)? -(X) : X)
#define  BADSQR(X) (X * X)
#define  BADCUBE(X) (X) * (X) * (X)

using namespace std;

inline double square(double x) {
    return x * x ;
}

inline double cube(double x) {
    return x * x * x;
}

inline int absval(int n) {
    return (n >= 0) ? n : -n;
}

int main() {
    cout << "Comparing inline and #define\n" ;
    double  t = 30.0;
    int i = 8, j = 8, k = 8, n = 8; 
    cout << "\nBADSQR(t + 8) = " << BADSQR(t + 8) 
            << "\nsquare(t + 8) = " << square(t + 8)
            << "\nBADCUBE(++i) = " << BADCUBE(++i)
            << "\ni = " << i
            << "\ncube(++j) = " << cube(++j)
            << "\nj = " << j
            << "\nBADABS(++k) = " << BADABS(++k)
            << "\nk = " << k
            << "\nabsval(++n) = " << absval(++n)
            << "\nn = " << n << endl;
}

