#ifndef METADATAOBJECT_H
#define METADATAOBJECT_H

#include "metadatavalue.h"
#include "dataobject.h"
#include <QImage>
/** A MetaDataValue with QObject properties,
    allowing for reflection.
*/
class METADATAEXPORT MetaDataObject :
        public DataObject, public MetaDataValue {
    Q_OBJECT
    Q_PROPERTY( QString Artist READ
                artist WRITE setArtist );
    Q_PROPERTY( QString TrackTitle
                READ trackTitle WRITE setTrackTitle );
    Q_PROPERTY( QString AlbumTitle READ
                albumTitle WRITE setAlbumTitle );
    Q_PROPERTY( QString TrackNumber
               READ trackNumber WRITE setTrackNumber );
    Q_PROPERTY( QString Genre READ
                genre WRITE setGenre);
    Q_PROPERTY( QTime TrackTime
                READ trackTime WRITE setTrackTime);
    Q_PROPERTY( QString Comment READ
                comment WRITE setComment);
    Q_PROPERTY( Preference Preference READ preference WRITE setPreference);
    Q_PROPERTY( QString FileName READ
                fileName WRITE setFileName );
    Q_PROPERTY( QImage Image READ image WRITE setImage);
    
    Q_PROPERTY(QUrl Url READ url WRITE setUrl);

public:
    typedef MetaDataValue SUPER;
    explicit MetaDataObject(QObject* parent=0) : DataObject(parent)
        { m_isNull = true; }
//end

public:
    virtual void setUrl(QUrl url);

    MetaDataObject& operator=(const MetaDataValue& other); 

    MetaDataObject& operator=(const MetaDataObject& other);   

};


#endif // METADATAOBJECT_H
