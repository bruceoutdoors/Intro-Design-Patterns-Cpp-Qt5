#include "dbconnectionsettings.h"
#include "playlistdb.h"
#include "metadatatable.h"
#include "dbutils.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QStringList>
#include <QSqlField>
#include <QDebug>
#include <QSqlError>
#include <QFileInfo>
#include <QDir>


const QString PlayListDb::TABLEPREFIX("dbplaylist_");




bool PlayListDb::clear(QString playListName) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery drop(QString("delete from %1").arg(tableName(playListName)));
//    QSqlQuery drop(QString("drop table %1").arg(tableName(playListName)));
    if (!drop.isActive()) {
        qDebug() << "Failed: " << drop.lastError().text();
        qDebug() << "  " << drop.lastQuery();
        return false;
    }
    return true;
}

void PlayListDb::loadAndStore(QString fileName, QString playListName) {
    QFileInfo fi(fileName);
    QString basePath = fi.absolutePath();
    if (!basePath.endsWith("/")) basePath += "/";
    QFile f(fileName);
    f.open(QIODevice::ReadOnly);
    QTextStream is(&f);
    while (!is.atEnd()) {
       QString current = is.readLine();
       if (current.startsWith("#")) continue;
       QFileInfo fi(current);
       if (!fi.isAbsolute()) {
           fi = QFileInfo(QDir(basePath), current);
       }
       addFile(playListName, fi.absoluteFilePath());
    }
}

QStringList PlayListDb::playLists() const {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QStringList sl;
    foreach (QString s, db.tables())
        if (s.startsWith(TABLEPREFIX)) {
            sl << s.mid(TABLEPREFIX.length());
        }
    return sl;
}


QStringList PlayListDb::playList(QString playListName) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QStringList sl;
    QSqlQuery findQuery(QString("select FileName from %1 order by pid").arg(tableName(playListName)));
    if (!findQuery.isActive()) {
        qDebug() << db.lastError().text();
        qDebug() << "Unable to execute: " << findQuery.lastQuery();
    }
    while (findQuery.next()) {
        sl << findQuery.value(0).toString();
    }
    return sl;
}

QString PlayListDb::takeFirst(QString playListName) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery findQuery(QString("select FileName from %1 order by pid limit 1")
             .arg(tableName(playListName)));
    if (!findQuery.isActive()) return QString();
    findQuery.next();
    QString path = findQuery.value(0).toString();
    removeFile(playListName, path);
    return path;
}

QString PlayListDb::last(QString playListName) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery findQuery(QString("select FileName from %1 order by pid DESC limit 1")
             .arg(tableName(playListName)));
    if (!findQuery.isActive()) return QString();
    findQuery.next();
    return findQuery.value(0).toString();
}

QString PlayListDb::tableName(QString playListName) {
    playListName = playListName.replace(QRegExp("[\\s\\W]+"), QString());
    return QString("dbplaylist_%1").arg(playListName);
}

bool PlayListDb::removeEntry(QString playList, int pid) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QString tn = tableName(playList);
    QSqlRecord record = db.record(tn);
    Q_ASSERT(!record.isEmpty());
    QString queryString=QString("delete from %1 where pid=%2")
          .arg(tn).arg(pid);
    QSqlQuery q(queryString);
    qDebug() << queryString;
    return q.isActive();
}

bool PlayListDb::removeFile(QString playList, QString path) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QString tn = tableName(playList);
    QSqlRecord record = db.record(tn);
    Q_ASSERT(!record.isEmpty());
    QString queryString=QString("delete from %1 where FileName=:fileName order by pid limit 1")
          .arg(tn);
    if (db.driverName() == "QSQLITE") {
        queryString=QString("delete from %1 where FileName=:fileName").arg(tn);
    }
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue("fileName", path);
    if (!q.exec()) {
        qDebug() << q.lastError().text() << q.lastQuery();
        return false;
    }
    return true;
}

void PlayListDb::shuffle(QString playListName) {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QString tn = tableName(playListName);
    QStringList sl;
    QSqlQuery findQuery(QString("select FileName from %1 order by RAND()").arg(tableName(playListName)));
    if (!findQuery.isActive()) {
        qDebug() << db.lastError().text();
        qDebug() << "Unable to execute: " << findQuery.lastQuery();
    }
    while (findQuery.next()) {
        sl << findQuery.value(0).toString();
    }
    clear(playListName);
    foreach (const QString& fn, sl) {
        addFile(playListName, fn);
    }
}

bool PlayListDb::addFile(QString playListName, QString fileName, bool replace) {
    QFileInfo fi(fileName);

    if (!fi.exists()) {
        qDebug() << "file does not exist:" << fileName;
        return false;
    }

    QSqlDatabase db = DbConnectionSettings::lastSaved();
    if (!db.isOpen()) db.open();
    QString tn = tableName(playListName);
    QSqlRecord record = db.record(tn);
    if (record.isEmpty()) {
        QString createString =QString("create table if not exists %1 "
                              "(pid INTEGER AUTO_INCREMENT PRIMARY KEY, FileName text) DEFAULT CHARSET utf8").arg(tn) ;
        if (db.driverName() == "QSQLITE")
            createString = QString("create table if not exists %1 "
                              "(pid INTEGER PRIMARY KEY, FileName text)").arg(tn) ;

        QSqlQuery createTable(createString);
        if (!createTable.isActive()) {
            qDebug() << "Failed:" << createTable.lastQuery() << createTable.lastError().text();
            abort();
        }
    }
    QString fn = fi.absoluteFilePath();

    if (replace) {
        removeFile(playListName, fn);
    }
    // Insert into the DB
    QString queryString  = QString("INSERT INTO %1 (FileName) VALUES(:fileName)").arg(tn);
    QSqlQuery q;
    if (!q.prepare(queryString)) {
        qDebug() << "prepare failed: " << q.lastError().text();
        return false;
    }
    q.bindValue("fileName", fn);

    if (!q.exec()) {
        qDebug() << "failed to insert: " << q.lastQuery() << q.lastError().text();
        return false;
    }
    // refresh metadata
    MetaDataTable::instance()->hasMetaData(fn, true);
    return true;
}

void PlayListDb::rename (QString oldName, QString newName) {
    if (tableName(oldName) == tableName(newName)) return;
    QStringList sl = playList(oldName);
    clear(newName);
    foreach (QString n, sl) {
        addFile(newName, n);
    }
    clear(oldName);
    qDebug() << "renamed " << oldName << " to " << newName;
}
