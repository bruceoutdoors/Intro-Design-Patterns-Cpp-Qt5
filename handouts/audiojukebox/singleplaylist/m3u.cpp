#include <QObject>
#include <QFile>
#include "m3u.h"
#include <QDebug>
#include <QModelIndexList>
#include "metadataobject.h"
#include "playlistmodel.h"
#include "metadataloader.h"


void M3u::writeTo(const QAbstractItemModel* source, QString fileName) const {
    QFile f(fileName);
    QFileInfo fi(fileName);
    QString basePath = fi.absolutePath();
    if (f.open(QIODevice::WriteOnly)) {
        QTextStream os(&f);
        QStringList sl = toStringList(source, basePath);
        os << sl.join("\n") << "\n";
        f.close();
    }
    else {
        qDebug() << "Can't open: " << fileName << " for writing. " ;
    }
}

void M3u::writeTo(const QModelIndexList& qmil, QString fileName ) const {

    QMap<QString, int> idxes = headerIndexes(qmil.at(0).model());
    QStringList retval;
    QFileInfo fi(fileName);
    QString basePath = fi.absolutePath();

    retval << "#EXTM3U";
    foreach (const QModelIndex& idx, qmil) {
        retval << toString(idx, idxes, basePath);
    }
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly)) {
        QTextStream os(&f);
        os << retval.join("\n") << "\n";
        f.close();
    }
    else {
        qDebug() << "Can't open " << fileName << "for writing.";
    }
}

int M3u::readFrom(QString fileName, PlayListModel* destination) {
    QFileInfo fi(fileName);
    QString basePath = fi.absolutePath();
    if (!basePath.endsWith("/")) basePath += "/";
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream is(&f);
        QStringList sl;
        while (!is.atEnd()) {
           sl << is.readLine();
        }

        return readFrom(sl, destination, basePath);
    }
    return 0;
}

int M3u::readFrom(QStringList lines, PlayListModel* destination, QString basePath) {
    static QRegExp extm3upattern("#EXTINF:\\s*(\\d+),\\s* - (.*)$");
    MetaDataValue currentSong;
    int count=0;
    MetaDataLoader *mdl = new MetaDataLoader(destination);
    mdl->connect (mdl, SIGNAL(fetched(MetaDataValue)),
             destination, SLOT(insertRecord(MetaDataValue)));

    foreach (QString current, lines) {
        if (current.startsWith("#")) {
            continue;
        }
        /* if it doesn't begin with a #, then it's a filename, and
                we're done reading after we get it
            */
        else {
            QFileInfo fi(current);
            if (!fi.exists()) {
                fi = QFileInfo(QDir(basePath), current);
            }
            if (!fi.exists()) {
                qDebug() << "m3u2p: Can not open: " << current;
                continue;
            }
            mdl->get(fi.absoluteFilePath());
            ++count;
        }
    }
//    qDebug() << "readFrom M3u Finished";
    return count;
}

QMap<QString, int> M3u::headerIndexes(const QAbstractItemModel* m) {
    QMap<QString, int> retval;
    int cc = m->columnCount();
    for (int i=0; i<cc; ++i) {
        QVariant hd = m->headerData(i, Qt::Horizontal, Qt::DisplayRole);
        if (hd.toString() == QString()) {
            hd = m->headerData(i, Qt::Horizontal, Qt::ToolTipRole);
        }
        retval[hd.toString()] = i;
    }
    return retval;
}

QString M3u::m3u(const MetaDataValue& song, QString playListDir) {

    QString extinf = QString ("#EXTINF: %1, %2 - %3")
        .arg(song.trackTime().toString("mm:ss"))
        .arg(song.artist())
        .arg(song.trackTitle());
    QString path = song.fileName();
    // create a relative path to the playlist
    if (playListDir != QString() && path.startsWith(playListDir)) {
        path = path.mid(playListDir.length());
        if (path.startsWith("/")) path = path.mid(1);
    }
    QString retval =  extinf + "\n" + path;
    return retval;
}




QStringList M3u::toStringList(const QAbstractItemModel* source, QString playListDir) {
	QStringList retval;
    QMap<QString, int> idxes = headerIndexes(source);
    retval << "#EXTM3U";
	int rows = source->rowCount();
    if (playListDir != QString() && !playListDir.endsWith('/'))
        playListDir += '/';
    for (int i=0; i<rows; ++i) {
        retval << toString(source->index(i, 0, QModelIndex()), idxes, playListDir);
    }
    return retval;
}

QString M3u::toString(const QModelIndex& idx, QMap<QString, int> idxes, QString playListDir) {

    QStringList retval;
    const QAbstractItemModel* model = idx.model();
    QString path = idx.data(Qt::UserRole).toString();
    if (playListDir != QString() && path.startsWith(playListDir)) {
        path = path.mid(playListDir.length());
        if (path.startsWith("/")) path = path.mid(1);
    }
    int i = idx.row();
    QString trackTime = model->data(model->index(i, idxes["TrackTime"])).toString();
    QString artist = model->data(model->index(i, idxes["Artist"])).toString();
    QString title = model->data(model->index(i, idxes["TrackTitle"])).toString();
    QString extinf = QString ("#EXTINF: %1, %2 - %3")
            .arg(trackTime).arg(title).arg(artist);
    retval << extinf;
    retval << path;
    return retval.join("\n");
}


