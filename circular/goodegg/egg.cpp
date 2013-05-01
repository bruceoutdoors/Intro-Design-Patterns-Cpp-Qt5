#include "chicken.h"
#include "egg.h"

Chicken* Egg::getParent() {
    return new Chicken(); /* Requires definition of Chicken. */   
}
