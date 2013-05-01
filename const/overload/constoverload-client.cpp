#include "constoverload.h"
#include <iostream>

int main( ) {
    using namespace std;
    Point3 pt1(1.2, 3.4, 5.6);
    const Point3 pt2(7.8, 9.1, 6.4);
    double d ;
    d = pt2[2];    /* __________ */
    cout << d << endl;
    d = pt1[0];    /* __________ */
    cout << d << endl;
    d = pt1[3];    /* __________ */
    cout << d << endl;
    pt1[2] = 8.7;  /* __________ */
    cout << pt1 << endl;
    //  pt2[2] = 'd';
    cout << pt2 << endl;
    return 0;
}

