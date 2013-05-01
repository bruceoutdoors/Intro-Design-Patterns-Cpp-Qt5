#include "static.h"

int main() {
    Thing::showCount();     /* At this point, no objects exist, but all class statics have been initialized. */
    Thing t1(3,4), t2(5,6);
    t1.showCount();         /* Access through object. */
    {                       /* An inner block of code is entered. */
        Thing t3(7,8), t4(9,10);
        Thing::showCount(); /* Access through class scope resolution operator.
        */ 
    }                       /* End inner block. */

    Thing::showCount(); 
    return 0;
}

