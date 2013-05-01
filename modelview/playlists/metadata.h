#ifndef METADATA_H
#define METADATA_H

#include <QTime>
#include <QTextStream>
#include <QString>
#include "starrating.h"

class MetaData : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString TrackTitle
                READ trackTitle WRITE setTrackTitle );
    Q_PROPERTY( QString Artist READ
                artist WRITE setArtist );
    Q_PROPERTY( QTime TrackTime
                READ trackTime WRITE setTrackTime);
    Q_PROPERTY( QString AlbumTitle READ
                albumTitle WRITE setAlbumTitle );
    Q_PROPERTY(int TrackNumber
               READ trackNumber WRITE setTrackNumber );
    Q_PROPERTY( QString Genre READ
                genre WRITE setGenre);
    Q_PROPERTY( StarRating Rating READ rating WRITE setRating );
    Q_PROPERTY( QString Comment READ
                comment WRITE setComment);
    Q_PROPERTY( QString FileName READ
                fileName WRITE setFileName );
public:
    MetaData(QObject* parent=0) : QObject(parent) {}
    virtual ~MetaData() {};
public:
    // Getters
    virtual QString fileName() const {return m_fileName;}

    virtual QString url() const {
        return QString("file://%1").arg(fileName());
    }

    virtual StarRating rating() const  {return m_rating;}
    virtual QString genre() const {return m_genre; }
    virtual QString artist() const {return m_artist; }
    virtual QString albumTitle() const {return m_albumTitle;}
    virtual QString trackTitle() const {return m_trackTitle;}
    virtual int trackNumber() const {return m_trackNumber;}
    virtual QTime trackTime() const {return m_trackTime;}
    virtual QString trackTimeString() const {
        QTime t=m_trackTime;
        if (t.hour() > 0) {
            return t.toString("hh:mm:ss");
        }
        else {
            return t.toString("m:ss");
        }
    }
    virtual QString comment() const {return m_comment;}


public slots:
    // Setters
    virtual void setFileName(const QString& fileName) {
        m_fileName = fileName;
    }
    virtual void setRating(StarRating rating) {
        m_rating = rating;
    }
    virtual void setGenre(const QString& genre) {
        m_genre = genre;
    }
    virtual void setArtist(const QString& artist) {
        m_artist = artist;
    }
    virtual void setTrackNumber(int tn) {
        m_trackNumber = tn;
    }
    virtual void setTrackTitle(const QString& title) {
        m_trackTitle = title;
    }
    virtual void setTrackTime(const QTime& time) {
    	m_trackTime = time;
    }
    virtual void setAlbumTitle(const QString& albumTitle) {
        m_albumTitle = albumTitle;
    }
    virtual void setComment(const QString& comment) {
        m_comment = comment;
    }
protected:
    QString m_fileName;
    QString m_trackTitle;
    QString m_comment;
    QString m_genre;
    QString m_artist;
    QString m_albumTitle;
    QTime m_trackTime;
    StarRating m_rating;
    int m_trackNumber;
};


#endif        //  #ifndef METADATA_H

