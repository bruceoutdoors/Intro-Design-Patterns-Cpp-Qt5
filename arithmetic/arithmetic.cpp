//start id=double
#include <QTextStream>

int main() {
    QTextStream cout(stdout);
    double x(1.23), y(4.56), z(7.89) ;
    int i(2), j(5), k(7);
    x += y ;
    z *= x ;
    cout << "x = " << x << "\tz = " << z
            << "\nx - z = " << x - z << endl ;
    //end
    //start id=ints
    cout << "k / i = " << k / i 
            << "\tk % j = " << k % j << endl ;
    cout << "i = " << i << "\tj = " << j << "\tk = " << k << endl;
    cout << "++k / i = " << ++k / i << endl;
    cout << "i = " << i << "\tj = " << j << "\tk = " << k << endl;
    cout << "i * j-- = " << i * j-- << endl;
    cout << "i = " << i << "\tj = " << j << "\tk = " << k << endl;
    //end
    //start id=mixed
    cout << "z / j = " << z / j << endl ;
    //end
    //start id=bools
    /*   if () ... else   approach */
    if (x * j <= z)
        cout << x * j << " <= " << z << endl ;
    else
        cout << x * j << " > " << z << endl;
//end
//start id=cond-op
    /* conditional operator approach */
    cout << x * k
            <<( (x * k < y * j) ? " < " : " >= ")
            << y * j << endl;
    return 0;
}
//end
//start id=output
/*OUT
x = 5.79        z = 45.6831
x - z = -39.8931
k / i = 3       k % j = 2
i = 2   j = 5   k = 7
++k / i = 4
i = 2   j = 5   k = 8
i * j-- = 10
i = 2   j = 4   k = 8
z / j = 11.4208
23.16 <= 45.6831
46.32 >= 18.24
*/
//end

