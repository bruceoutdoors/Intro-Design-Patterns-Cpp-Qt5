#include "constraintmap.h"

ConstraintMap map;              /* Okay, ConstraintMap is already included. */
#include "constraintmap.h"      /* Redundant but harmless if #ifndef wrapped. */

Constraint* constraintP;        /* Using forward declaration from constraintmap.h. */

Constraint p;                   /* Error: incomplete type. */
#include <constraint.h>
Constraint q;                   /* Now it is a complete type. */

void ConstraintMap::addConstraint(Constraint& c) {
    cout << c.name();           /* Complete type required here. */
}
