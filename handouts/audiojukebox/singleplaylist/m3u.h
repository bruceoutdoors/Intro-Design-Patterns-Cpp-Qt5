#ifndef M3UREADER_H
#define M3UREADER_H

#include <QStringList>
#include <QString>
class QAbstractItemModel;
class PlayListModel;
#include "metadatavalue.h"
#include <QItemSelectionModel>

/** Class for reading and writing playlist files of .m3u extension */

class M3u {
public:
    /** @return number of items in the playlist
    */
    int readFrom(QString fileName, PlayListModel* destination);
    static QMap<QString, int> headerIndexes(const QAbstractItemModel* m);

    /** @return an m3u representation of f, with #extinf */
    static QString m3u(const MetaDataValue& f, QString playListDir = QString());

    void writeTo(const QModelIndexList &qmil, QString fileName) const;

    void writeTo(const QAbstractItemModel* source, QString fileName) const ;
    /** @param source - a model containing a playlist to save
        @param playListDir - if provided, writes relative paths to playlist dir
    */
    static QStringList toStringList(const QAbstractItemModel* source, QString playListDir = QString());

    static QString toString(const QModelIndex& idx, QMap<QString, int> idxes, QString playListDir) ;

    int readFrom(QStringList lines, PlayListModel* destination, QString playListDir = QString());
};


#endif        //  #ifndef M3UREADER_H

