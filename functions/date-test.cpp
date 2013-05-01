#include "date.h"
#include <iostream>

int main() {
    using namespace std;
    Date d1;
    Date d2(15);
    Date d3(23, 8);
    Date d4(19, 11, 2003);

    d1.display(false);
    cout << '\t';
    d2.display();
    d3.display(false);
    cout << '\t';
    d4.display();
    return 0;
}
