#ifndef METADATAVALUE_H
#define METADATAVALUE_H


#include <QTime>
#include <QUrl>
#include <QString>
#include <QImage>
#include "preference.h"
#include "metadataexport.h"
//start
/** Simple Value type for audio metadata.
    Can be used in streams, QVariant, Collections and QFuture.
    Defines common interface for programs that need audio metadata.

*/
class METADATAEXPORT MetaDataValue {
public:

    friend METADATAEXPORT QTextStream& operator<< (QTextStream& os, 
                                         const MetaDataValue& mdv);
    friend METADATAEXPORT QTextStream& operator>> (QTextStream& is,
                                         MetaDataValue& mdv);
    friend METADATAEXPORT QDataStream& operator<< (QDataStream& os,
                                         const MetaDataValue& mdv);
    friend METADATAEXPORT QDataStream& operator>> (QDataStream& is,
                                         MetaDataValue& mdv);
    friend METADATAEXPORT bool operator==(const MetaDataValue&,
                                          const MetaDataValue&);
//end
    MetaDataValue(): m_isNull(true) {}
    MetaDataValue(const MetaDataValue& other);
    virtual ~MetaDataValue() {}

    virtual MetaDataValue& operator=(const MetaDataValue& other) ;

    virtual QUrl url() const;
//start    
    virtual QString fileName() const ;
    virtual Preference preference() const ;
    virtual QString genre() const;
    virtual QString artist() const;
    virtual QString albumTitle() const;
    virtual QString trackTitle() const;
    virtual QString trackNumber() const;
    virtual const QImage &image() const;

    /**
     @return duration of track
     */
    virtual QTime trackTime() const;
    virtual QString trackTimeString() const;
    virtual QString comment() const;
//end    
    virtual bool isNull() const;
    virtual void setNull(bool n);

    // Setters
    /** May cause a metadata fetch in some implementations.
        changes the URL as a side-effect. */
    virtual void setFileName(QString fileName);
    virtual void setUrl(QUrl url);
    virtual void setPreference(const Preference & newPref);
    virtual void setGenre(const QString & newGenre);
    virtual void setArtist(const QString & newArtist);
    virtual void setTrackNumber(const QString& newTrackNumber);
    virtual void setTrackTitle(const QString &newTitle);
    virtual void setImage(const QImage& img) {
        m_Image = img;
    }
    virtual void setTrackTime(const QTime &time) {
        m_TrackTime = time;
    }
    virtual void setAlbumTitle(const QString &newAlbumTitle);
    virtual void setComment(const QString &newComment);
//start
protected:
    bool m_isNull;
    QUrl m_Url;
    QString m_TrackNumber;
    QString m_TrackTitle;
    QString m_Comment;
    Preference m_Preference;
    QString m_Genre;
    QString m_Artist;
    QTime m_TrackTime;
    QString m_AlbumTitle;
    QImage m_Image;
};
Q_DECLARE_METATYPE(MetaDataValue);  /* Add to QVariant type system. */
//end

METADATAEXPORT bool operator==(const MetaDataValue&, 
                               const MetaDataValue&);
METADATAEXPORT QTextStream& operator<< (QTextStream& os, 
                                        const MetaDataValue& mdv);
METADATAEXPORT QTextStream& operator>> (QTextStream& is, 
                                        MetaDataValue& mdv);
METADATAEXPORT QDataStream& operator<< (QDataStream& os,
                                        const MetaDataValue& mdv);
METADATAEXPORT QDataStream& operator>> (QDataStream& is, 
                                        MetaDataValue& mdv);


#endif        //  #ifndef METADATAVALUE_H
