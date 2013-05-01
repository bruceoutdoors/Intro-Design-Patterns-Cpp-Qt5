#include "metadatavalue.h"
#include <QDebug>
#include <QTextStream>

QString MetaDataValue::fileName() const {
    return m_Url.toLocalFile();
}

MetaDataValue::MetaDataValue(const MetaDataValue &other) {
    *this = other;

}

MetaDataValue& MetaDataValue::operator=(const MetaDataValue& other) {
    if (this == &other) return *this;
    m_isNull = other.isNull();
    if (m_isNull) return *this;
    setImage(other.image());
    setUrl(other.url());
    setTrackTitle(other.trackTitle());
    setArtist(other.artist());
    setAlbumTitle(other.albumTitle());
    setTrackNumber(other.trackNumber());
    setTrackTime(other.trackTime());
    setComment(other.comment());
    setGenre(other.genre());
    setPreference(other.preference());
    return *this;
}
const QImage& MetaDataValue::image() const {
    return m_Image;
}

void MetaDataValue::setFileName(QString newFileName) {
    m_Url = QUrl::fromLocalFile(newFileName);
    m_isNull=false;
}

QString MetaDataValue::genre() const {
    return m_Genre;
}
QString MetaDataValue::artist() const {
    return m_Artist;
}
QString MetaDataValue::albumTitle() const {
    return m_AlbumTitle;
}
QString MetaDataValue::trackTitle() const {
    if (m_TrackTitle == QString()) {
        return fileName();
    }
    return m_TrackTitle;
}
QString MetaDataValue::trackNumber() const {
    return m_TrackNumber;
}
QTime MetaDataValue::trackTime() const {
    return m_TrackTime;
}
QString MetaDataValue::trackTimeString() const {
    QTime t=m_TrackTime;
    if (t.hour() > 0) {
        return t.toString("hh:mm:ss");
    }
    else {
        return t.toString("m:ss");
    }
}

QString MetaDataValue::comment() const {
    return m_Comment;
}

Preference MetaDataValue::preference() const {
    return m_Preference;
}

void MetaDataValue::setPreference(const Preference & newPref) {
    m_Preference = newPref;
}

void MetaDataValue::setGenre(const QString & newGenre) {
    m_Genre=newGenre;
}

void MetaDataValue::setArtist(const QString & newArtist) {
    m_Artist = newArtist;
}

void MetaDataValue::setTrackNumber(
    const QString& newTrackNumber) {
    m_TrackNumber = newTrackNumber;
}

void MetaDataValue::setTrackTitle(const QString &newTitle) {
    m_isNull = false;
    m_TrackTitle = newTitle;
}
void MetaDataValue::setAlbumTitle(const QString &newAlbumTitle) {
    m_AlbumTitle = newAlbumTitle;
}
void MetaDataValue::setComment(const QString &newComment) {
    m_Comment = newComment;
    if (m_Comment.contains("\n")) m_Comment.replace("\n", " ");
}
bool operator==(const MetaDataValue& l, const MetaDataValue& other) {
    if (l.url() != other.url()) return false;
    if (l.trackTitle() != other.trackTitle()) return false;
    if (l.trackTimeString() != other.trackTimeString()) return false;
    if (l.albumTitle() != other.albumTitle()) return false;
    if (l.preference() != other.preference()) return false;
    if (l.comment() != other.comment()) return false;
    if (l.trackNumber() != other.trackNumber()) return false;
    if (l.artist() != other.artist()) return false;
    if (l.genre() != other.genre()) return false;
    if (l.isNull() != other.isNull()) return false;
    return true;
}

//start id="textstream"

QTextStream& operator<< (QTextStream& os, const MetaDataValue& mdv) {
    QStringList sl;
    sl << mdv.url().toString() << mdv.trackTitle() << mdv.artist() 
       << mdv.albumTitle() << mdv.trackNumber() 
       << mdv.trackTime().toString("m:ss") << mdv.genre() 
       << mdv.preference().toString() << mdv.comment();

    os << sl.join("\t") << "\n";           /* Output to TSV (tab-separated-values) */
    return os;
}

QTextStream& operator>> (QTextStream& is, MetaDataValue& mdv) {
    QString line = is.readLine();
    QStringList fields = line.split("\t"); /* Read as TSV */
    while (fields.size() < 9) {
        fields << "";
    }
    mdv.m_isNull = false;
    mdv.setUrl(QUrl::fromUserInput(fields[0]));
    mdv.setTrackTitle(fields[1]);
    mdv.setArtist(fields[2]);
    mdv.setAlbumTitle(fields[3]);
    mdv.setTrackNumber(fields[4]);
    QTime t = QTime::fromString(fields[5], "m:ss");
    mdv.setTrackTime(t);
    mdv.setGenre(fields[6]);
    Preference p(fields[7]);
    mdv.setPreference(p);
    mdv.setComment(fields[8]);
    return is;
}
//end
//start id="datastream"
QDataStream& operator<< (QDataStream& os, const MetaDataValue& mdv) {
    os << mdv.m_Url << mdv.trackTitle() << mdv.artist() 
       << mdv.albumTitle() << mdv.trackNumber() << mdv.trackTime() 
       << mdv.genre() << mdv.preference() << mdv.comment() 
       << mdv.image();
    return os;
}

QDataStream& operator>> (QDataStream& is, MetaDataValue& mdv) {
    is >> mdv.m_Url >> mdv.m_TrackTitle >> mdv.m_Artist 
       >> mdv.m_AlbumTitle >> mdv.m_TrackNumber >> mdv.m_TrackTime 
       >> mdv.m_Genre >> mdv.m_Preference >> mdv.m_Comment 
       >> mdv.m_Image;
    mdv.m_isNull= false;
    return is;
}
//end

bool MetaDataValue::isNull() const {
    return m_isNull;
}
void MetaDataValue::setNull(bool n) {
    m_isNull = n;
}
QUrl MetaDataValue::url() const {
    return m_Url;
}
void MetaDataValue::setUrl(QUrl url) {
    m_Url = url;
}
