#include <QTextStream>
#include <QDebug>

QTextStream cin(stdin);
QTextStream cout(stdout);
QTextStream cerr(stderr);

int main() {
   int num1(1234), num2(2345) ;
    cout << oct << num2 << '\t'
            << hex << num2 << '\t'
             << dec << num2 
             << endl;
    double dub(1357);
    cout << dub << '\t'
            << forcesign << dub << '\t'
            << forcepoint << dub 
            << endl;
    dub = 1234.5678;
    cout << dub << '\t'
            << fixed << dub << '\t'
            << scientific << dub << '\n'
            << noforcesign << dub 
            << endl;
    qDebug() << "Here is a debug message with " << dub << "in it." ;
    qDebug("Here is one with the number %d in it.", num1 );
}
/*OUT
4451    929     2345
1357    +1357   +1357.00
+1234.57        +1234.567800    +1.234568e+03
1.234568e+03
Here is a debug message with  1234.57 in it.
Here is one with the number 1234 in it.
*/
