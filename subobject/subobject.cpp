#include "subobject.h"

int main() {
    Square sq1(3,4,5,6);
    Point p1(2,3), p2(8, 9);
    Square sq2(p1, p2);
}
