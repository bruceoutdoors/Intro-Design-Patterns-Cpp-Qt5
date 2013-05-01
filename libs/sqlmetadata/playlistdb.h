#ifndef PLAYLISTDB_H
#define PLAYLISTDB_H

#include <QObject>
#include "sqlmdexport.h"
class MetaDataTable;


/**
   Provides/manages tables of playlists stored in SQL database.
   Tested on MySQL and SQLite.
*/
class SQLMDEXPORT PlayListDb : public QObject
{
    Q_OBJECT
public:
    static const QString TABLEPREFIX;

    /** @return list of fileNames in a named playlist */
    QStringList playList(QString playListName);

    /** @return list of playlists */
    QStringList playLists() const;

    /** Returns and removes the first item from the playlist.
      Used for handling the play queue */
    QString takeFirst(QString playListName);

    /** Returns the last track added to this playlist */
    QString last(QString playListName);

    /** Loads a playlist from an m3u file, and stores it in the
      database */
    void loadAndStore(QString fileName, QString playListName);

    /** Renames a playlist / table */
    void rename (QString oldName, QString newName);

    /** @return the SQL table name corresponding to this playlist */
    static QString tableName(QString playListName);

    /** Clear a playlist */
    bool clear(QString playListName);

    void shuffle(QString playListName);


public slots:
    /** Creates the table if necessary.
        Adds metadata to Mp3FileDb if necessary.
    @param playList name of playlist.
    @param replace if true, will remove previous entries with same path, enforcing an exclusive add. Useful for
    history.
    */
    bool addFile(QString playList, QString path, bool replace=false);
    /** Removes a song from a playlist */
    bool removeFile(QString playList, QString path);

    /** Remove an entry by pid instead of fileName) */
    bool removeEntry(QString playList, int pid);

};

#endif // PLAYLISTDB_H
