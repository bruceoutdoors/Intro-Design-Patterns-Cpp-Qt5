#ifndef TESTDBI_H
#define TESTDBI_H
#include "dbunit.h"

/**
  This class tests that the Dbi Interface works, that through cursors,
  one can access the default database and get a list of all the tables.
  We should add other tests here too.
    @author S. Alan Ezust sae@mcs.suffolk.edu
 */
class TestDbi : public DbUnit {
    Q_OBJECT
 public:
    explicit TestDbi(QObject* parent=0, char* name="testdbi"):
    DbUnit(parent, name) {}

    /** We override this method instead of @ref execute()
       because we want these operations done inside a transaction context
    */
    bool persistentOps();
};

#endif