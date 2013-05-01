#include "productfactory.h"
#include "product.h"
#include "testprepare.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>

//start id="addDatabase"
void testprepare::testPrepare() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("amarok");
    db.setPassword("amarok");
    db.setDatabaseName("amarok");
    QVERIFY(db.open());
//end
    QVERIFY(db.driver()->hasFeature(QSqlDriver::PreparedQueries)); /* Must check after db.open(), to see if the driver does it for you on the client side, as is the case with mysql. */
//start id="createtable"
    QSqlQuery q;
    bool r = q.exec("CREATE TABLE if not exists Products ("
            "name text, dateAdded Date, price float, description text"
            " ) DEFAULT CHARSET utf8");
    if (!r) {
        qDebug () << "create table failed: " <<  db.lastError().text();
        qDebug() << "q.lasterror.text()" << q.lastError().text();
        QFAIL(q.lastError().text().toLocal8Bit());
    }
//end
//start id="prepare"
    QSqlQuery insertPrepare;
    insertPrepare.prepare("insert into Products "
              "(name, dateAdded, price, description) values"
              "(:name, :dateAdded, :price, :description)");
    ProductFactory pf;
    QStringList props = QStringList() << "name" << "dateAdded" << "price" << "description";

    for (int i=0; i<ROWS; ++i) {
        Product* p = pf.randomProduct();
        insertPrepare.bindValue(":name", p->name() );
        insertPrepare.bindValue(":dateAdded", p->dateAdded()); /* QDate */
        insertPrepare.bindValue(":price", p->price()); /* double */
        insertPrepare.bindValue(":description", p->description());
        bool r = insertPrepare.exec();
        if (!r) qDebug() << insertPrepare.lastError().text();
        QVERIFY(r);
    }
    //end
}


QTEST_MAIN(testprepare);
