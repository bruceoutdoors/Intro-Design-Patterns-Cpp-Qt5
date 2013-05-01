#include <QtGui>
#include "testtracks.h"
#include "metadatavalue.h"
//start id=testtracks
QString testTracksDir()
{
    QSettings s;
    QString path = s.value("test.tracks.dir", QDesktopServices::storageLocation(QDesktopServices::MusicLocation ) ).toString();
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    path = env.value("TESTTRACKS", path );
    qDebug() << "Using " << path << "As a source for test tracks. ";
    return path;
}
//end

// Debugging code for testing the low-level operators
bool equal(const MetaDataValue& left, const MetaDataValue& right) {
    if (::operator==(left, right)) return true;
    QTextStream cout(stdout);
    if (left.fileName() != right.fileName()) {
        cout << "l.filename=" << left.fileName()
             << "r.filename=" << right.fileName() << endl;
        return false;

    }
    if (left.artist() != right.artist()) {
        cout << "l.artist=" << left.artist()
             << "r.artist=" << right.artist() << endl;
        return false;
    }
    if (left.trackTitle() != right.trackTitle()) {
        cout << "l.trackTitle=" << left.trackTitle()
                << " r.trackTitle=" << right.trackTitle() << endl;
        return false;
    }
    if (left.albumTitle() != right.albumTitle()) {
        cout << "l.albumTitle=" << left.albumTitle()
                << " r =" << right.albumTitle() << endl;
        return false;
    }
    if (left.trackTimeString() != right.trackTimeString()) {
        cout << "TrackTime l:" << left.trackTimeString() << " r: "
             << right.trackTimeString() << endl;
        return false;
    }
    if (left.trackNumber() != right.trackNumber()) {
        cout << "Tracknumber: " << left.trackNumber() << " r: " << right.trackNumber();
        return false;
    }
    if (left.genre() != right.genre()) {
        cout << "Genre: " << left.genre() << " r: " << right.genre();
        return false;
    }
    if (left.preference() != right.preference()) {
        cout << "Preference: " << left.preference() << " r:" << right.preference() << endl;
        return false;
    }
    if (!left.comment().startsWith(right.comment()) &&
        !right.comment().startsWith(left.comment())) {
        cout << "Comment: " << left.comment() << " r: " << right.comment() << endl;
        return false;
    }
    return true;
}
