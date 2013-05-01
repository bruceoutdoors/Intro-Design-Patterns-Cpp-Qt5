#ifndef CONSTRAINTMAP_H
#define CONSTRAINTMAP_H

#include <QHash>
#include <QString>

class Constraint;                                           /* Forward declaration. */

class ConstraintMap : public QHash<QString, Constraint*> {  /* Needs
      definitions of QHash and QString, but only the
      declaration of Constraint, because it's a pointer. */

private:
    Constraint* m_Constraintptr;                            /* No problem, it's just a pointer. */
    Constraint m_ConstraintObj;                             /* Error: incomplete type. */
    void addConstraint(Constraint& c);                      /* Using forward declaration. */
};
#endif        //  #ifndef CONSTRAINTMAP_H

