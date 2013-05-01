
#include "testdbi.h"

#include <qapplication.h>
#include <qhbox.h>
#include <qcombobox.h>
#include <qmainwindow.h>
#include <qsqlcursor.h>


bool TestDbi::persistentOps () {
    qDebug("testDbi::persistentOps()");
    QSqlDatabase *db = getDbSpec().database();
    Q_ASSERT(db != NULL);
    qDebug("testDbi::got database");
    QStringList tables = db->tables();
    qDebug("Here is a list of tables:");
    qDebug() << tables.join(", ");
    QString tableName = getDbSpec().firstTable();
    qDebug("Creating a cursor on the first table %s", tableName);
    QSqlCursor cursor(tableName, true, db);
    // select all fields in database
    cursor.select();
    if ( cursor.next() ) {
        // get the first row, as a record
        QSqlRecord *record = cursor.editBuffer();
        qDebug("First record has %s fields", record->count());
        for (unsigned i=0; i<record->count(); ++i) {
            QString val = QString("%1 = %2").
                          arg(record->fieldName(i)).
                          arg(record->value(i).toString());
            qDebug() << val;
        }
    }
    return true;
}


