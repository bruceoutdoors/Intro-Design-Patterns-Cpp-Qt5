#include "dbconnectionsettings.h"
#include <QSettings>
#include <QMessageBox>

void DbConnectionSettings::save(QSqlDatabase db) {
    QSettings s;
    s.setValue("dbname", db.databaseName());
    s.setValue("dbhost", db.hostName());
    s.setValue("dbuser", db.userName());
    s.setValue("dbpw", db.password());
    s.setValue("dbtype", db.driverName());

}

QSqlDatabase DbConnectionSettings::lastSaved(QString connectionName) {
    QSqlDatabase db;
    if (!QSqlDatabase::contains(connectionName)) {
        QSettings s;
        QString dbname = s.value("dbname").toString();
        QString dbhost = s.value("dbhost").toString();
        QString dbuser = s.value("dbuser").toString();
        QString dbpw = s.value("dbpw").toString();
        QString dbtype = s.value("dbtype").toString();
        db = QSqlDatabase::addDatabase(dbtype, connectionName);
        db.setDatabaseName(dbname);
        db.setHostName(dbhost);
        db.setUserName(dbuser);
        db.setPassword(dbpw);

    }
    else {
        db = QSqlDatabase::database(connectionName);

    }
    return db;
}

