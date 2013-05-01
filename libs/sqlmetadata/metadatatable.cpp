
#include "abstractmetadataloader.h"
#include "dbutils.h"
#include "dbconnectionsettings.h"
#include "metadatatable.h"
#include "audiometadata.h"
#include <QFileInfo>
#include <QDirIterator>
#include <QModelIndex>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlIndex>
#include <QSqlError>
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>


MetaDataTable* MetaDataTable::instance() {
    static MetaDataTable* retval = 0;
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    if (!db.isValid()) {
        qDebug() << "Unable to create db connection.";
        abort();
    }
    if (retval == 0) {
        retval = new MetaDataTable(qApp);
    }
    return retval;
}
//start id=prepare
MetaDataTable::MetaDataTable(QObject* parent)
    : QObject(parent), m_tableName("MetaData") {
    setObjectName(m_tableName);
    m_mdl = Abstract::MetaDataLoader::instance();
    m_driver = DbConnectionSettings::lastSaved().driverName();
    Q_ASSERT(createMetadataTable());
    QString preparedQuery = "INSERT into MetaData" /* Tested with MySQL5. */
         "(Artist, TrackTitle, AlbumTitle, TrackNumber, TrackTime, Genre,"
         "Preference, FileName, Comment) VALUES (:artist, :title, :album,"
         ":track, :time, :genre, :preference, :filename, :comment) "
         "ON DUPLICATE KEY UPDATE Preference=VALUES(Preference),"
         "Genre=VALUES(Genre), AlbumTitle=VALUES(AlbumTitle),"
         "TrackTitle=VALUES(TrackTitle), TrackNumber=VALUES(TrackNumber),"
         "Artist=VALUES(Artist), COMMENT=VALUES(Comment)"; 
    if (m_driver == "QSQLITE") {
        preparedQuery = "INSERT or REPLACE into MetaData"
            "(Artist, TrackTitle, AlbumTitle, TrackNumber, TrackTime, "
            "Genre, Preference, FileName, Comment)"
            "VALUES (:artist, :title, :album, :track, :time, :genre, "
            ":preference, :filename, :comment)";
    }
    bool prepSuccess = m_insertQuery.prepare(preparedQuery);
    if (!prepSuccess) {
        qDebug() << "Prepare fail: " << m_insertQuery.lastError().text() 
                 << m_insertQuery.lastQuery();
        abort();
    }
//end
    m_deleteQuery = 
       QString("delete from MetaData where FileName = \"%1\"");
    connect (m_mdl, SIGNAL(fetched(MetaDataValue)),
             this, SLOT(insert(MetaDataValue)), Qt::QueuedConnection);
}


MetaDataTable::~MetaDataTable()
{
    DbConnectionSettings::lastSaved().close();
}

//start id=create
bool MetaDataTable::createMetadataTable() {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    if (m_driver == "QMYSQL")
       m_createTableQStr = QString("CREATE TABLE if not exists %1 ("
         "TrackTitle  text, Artist text, "
         "AlbumTitle  text, TrackTime integer, TrackNumber integer, "
         "Genre varchar(30),  Preference integer, Comment  text, "
         "FileName  varchar(255) PRIMARY KEY, INDEX(Genre) ) "
         "DEFAULT CHARSET utf8").arg(m_tableName);
    else m_createTableQStr = QString("CREATE TABLE IF NOT EXISTS %1 ("    /* 
            Tested with SQLite3. */
         "TrackTitle  text, Artist text, AlbumTitle  text, "
         "TrackTime integer, TrackNumber integer, Genre varchar(30), "
         "Preference integer, Comment  text, FileName  varchar(255) "
         "PRIMARY KEY)").arg(m_tableName);
    QSqlQuery q(m_createTableQStr);
    if (!q.isActive()) {
       qDebug() << "Create Table Fail: " << q.lastError().text() 
                << q.lastQuery();
       return false;
    }
    db.commit();
    return true;
}
//end

bool MetaDataTable::clearTable() {
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery q("delete from MetaData");
    return q.isActive();
}
//start id=select
QStringList MetaDataTable::genres() const {
    QStringList sl;
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery q("SELECT DISTINCT Genre from MetaData");
    if (!q.isActive()) {
        qDebug() << "Query Failed: " << q.lastQuery() 
                 << q.lastError().text();
    } else while (q.next()) {
        sl << q.value(0).toString();
    }
    return sl;
}
//end

//start id="insert"
bool MetaDataTable::insert(const MetaDataValue &ft) {
    using namespace DbUtils;

    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlRecord record = db.record(m_tableName);
    if (record.isEmpty() && !createMetadataTable()) {
        qDebug() << "unable to create metadata: " 
                 << db.lastError().text();
        return false;
    }

    m_insertQuery.bindValue(":artist", ft.artist());
    m_insertQuery.bindValue(":title", ft.trackTitle());
    m_insertQuery.bindValue(":album", ft.albumTitle());
    m_insertQuery.bindValue(":track", ft.trackNumber());
    QTime t = ft.trackTime();
    int secs = QTime().secsTo(t);
    m_insertQuery.bindValue(":time", secs);
    m_insertQuery.bindValue(":genre", ft.genre());
    m_insertQuery.bindValue(":filename", ft.fileName());
    int pref = ft.preference().intValue();
    m_insertQuery.bindValue(":preference", pref);
    m_insertQuery.bindValue(":comment", ft.comment());

    bool retval = m_insertQuery.exec();

    if (!retval) {
        qDebug() << m_insertQuery.lastError().text() 
                 << m_insertQuery.lastQuery();
        abort();
    }
    emit inserted(ft);
    return retval;
}
//end

bool MetaDataTable::
hasMetaData(QString fileName, bool fetch, bool refresh) {
    MetaDataValue mdv = findRecord(fileName);
    if (refresh || (fetch && mdv.isNull())) {
        m_mdl->get(fileName);
    }
    return !mdv.isNull(); 
}
//start id="findrecord"
MetaDataValue MetaDataTable::findRecord(QString fileName) {
    using namespace DbUtils;
    QFileInfo fi(fileName);
    MetaDataObject f;
    if (!fi.exists()) return f;                  /* Return a QObject by value? Don't forget, MetaDataValue is the base class of this particular QObject. */
    QString abs = fi.absoluteFilePath();

    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QString qs = QString("select * from %1 where FileName = \"%2\"")
                  .arg(m_tableName).arg(escape(abs));
    QSqlQuery findQuery(qs);
    if (!findQuery.isActive()) {
        qDebug() << "Query Failed: " << findQuery.lastQuery() 
                 << findQuery.lastError().text();
        return f;
    }
    if (!findQuery.first()) return f;
    QSqlRecord rec = findQuery.record();
    for (int i=rec.count() -1; i >= 0; --i) {    /* Properties in QObject map to column names / field values in the table! */
        QSqlField field = rec.field(i);
        QString key = field.name();
        QVariant value = field.value();
        if (key == "Preference") {
            int v = value.toInt();
            Preference p(v);
            f.setPreference(p);
        }
        else if (key == "TrackTime") {           /* SQLite has no time type, so we must store as int. */
            QTime trackTime;
            trackTime = trackTime.addSecs(value.toInt());
            f.setTrackTime(trackTime);
        }
        else {
            f.setProperty(key, value);           /* Using QObject setProperty for other columns. */
        }

    }
    return f;                                    /* Create a value type from this local stack QObject about to be destroyed. */
}
//end
QSet<QString> MetaDataTable::allSongs() {
    QSet<QString> retval;
    QSqlDatabase db = DbConnectionSettings::lastSaved();
    QSqlQuery q = db.exec("select FileName from MetaData");
    while (q.next()) {
        retval << q.value(0).toString();
    }
    return retval;
}

int MetaDataTable::visit(QString directory) {
//    QSet<QString> loaded = allSongs();
    int i=0;
    QDirIterator itr(directory, m_mdl->supportedExtensions(),
                     QDir::Files, QDirIterator::Subdirectories);
    while (itr.hasNext()) {
        QString fn = itr.next();
        if (!hasMetaData(fn, true)) {
            ++i;
            qApp->processEvents();
        }
    }
    return i;
}


bool MetaDataTable::dropMetaData(QString fileName) {
    QString q = m_deleteQuery.arg(DbUtils::escape(fileName));
    QSqlQuery query(q);

//    qDebug() << "drop: " << fileName;
    bool retval = query.isActive();
    qDebug() << query.lastQuery();
    return retval;
}

