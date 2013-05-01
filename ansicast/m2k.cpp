// Miles are converted to kilometers.
#include <QTextStream>

QTextStream cin(stdin);
QTextStream cout(stdout);
QTextStream cerr(stderr);

const double  m2k = 1.609;    // conversion constant

inline double mi2km(int miles) {
    return (miles * m2k);
}

int main() {
    int  miles;
    double kilometers;
    cout << "Enter distance in miles: " << flush;
    cin >> miles ;  
    kilometers = mi2km(miles);
    cout << "This is approximately "
         <<  static_cast<int>(kilometers)
         << "km."<< endl;
    cout << "Without the cast, kilometers = "
         << kilometers << endl;
    double* dp = const_cast<double*>(&m2k); 
    cout << "m2k: " << m2k << endl;
    cout << "&m2k: " << &m2k << "  dp: " << dp << endl;
    cout << "*dp: " << *dp << endl;
    *dp = 1.892;  /* What are we attempting to do here?*/
    cout << "Can we reach this statement? " << endl;
    return 0;
}

/*OUT
Enter distance in miles: 23
This is approximately 37km.
Without the cast, kilometers = 37.007
m2k: 1.609
&m2k: 0x8049048  dp: 0x8049048
*dp: 1.609
Segmentation fault
*/

