#include <QTextStream>

int main() {
    QTextStream cout(stdout);
    const char tab = '\t';
    int n = 13;
    int* ip = new int(n + 3);
    double d = 3.14;
    double* dp = new double(d + 2.3);
    char c = 'K';
    char* cp = new char(c + 5);
    cout << *ip << tab << *dp << tab << *cp << endl;
    int* ip2 = ip;
    cout << ip << tab << ip2 << endl;
    *ip2 += 6;
    cout << *ip << endl;
    delete ip;
    cout << *ip2 << endl;
    cout << ip << tab << ip2 << endl;
    return 0;
}

