#ifndef MP3FILEDB_H
#define MP3FILEDB_H
#include "sqlmdexport.h"

#include "audiometadata.h"

#include <QObject>
#include <QHash>
#include <QStringList>
#include <QSqlQuery>
namespace Abstract {
     class MetaDataLoader;
}

/** Wrapper for Sql Table "MetaData".
    Can be used to store metadata for other media files besides MP3.
    Tested on MySQL.
    SQLite is almost working too.

*/
class SQLMDEXPORT MetaDataTable : public QObject
{
    Q_OBJECT
public:

    static MetaDataTable* instance();

    ~MetaDataTable();

    /** Recursively searches for media files to add
        metadata to the table. Ignores files that
        were already added previously.
    @param directory the path to start searching
    */
    int visit(QString directory);

    /** Drops the metadata table, in preparation for a full rescan. */
    bool clearTable();

    /** Sorted list of genres in the metadata table */
    QStringList genres() const;

    /** Check if there is metadata for this track available in the table. 
           Insert (or update) the record in the metadata table for this track.
       @return true if the metadata for that file 
                is already available in the database.
       @param fetch if true, and record was not in the table, 
              fetch the metadata and add to table.  
       @param refresh if true, fetch metadata and update table regardless
              of returned value 
    */
    bool hasMetaData(QString fileName, bool fetch=false, bool refresh=false);

    /** drops row from table */
    bool dropMetaData(QString fileName);

    /** Uses database table to find metadata value. 
            @return null value if not in the table.
    */
    MetaDataValue findRecord(QString fileName);
    
    QSet<QString> allSongs();

    virtual QString tableName() const {return m_tableName;}

protected:
    /** @see instance() */
    MetaDataTable(QObject* parent=0) ;
    bool createMetadataTable();
public slots:
    bool insert(const MetaDataValue &mdv);
signals:
    /** Emitted after a record has been inserted into the database */
    void inserted(MetaDataValue v);
protected:
    // name of table for metadata
    QString m_tableName;
    QString m_driver;
    QString m_createTableQStr;
    QHash<QString, MetaDataValue> m_previous;
    QSqlQuery m_insertQuery;
//    QSqlQuery m_deleteQuery;
    QString m_deleteQuery;
    Abstract::MetaDataLoader *m_mdl;
};


#endif // MP3FILEDB_H
