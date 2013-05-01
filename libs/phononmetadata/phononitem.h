#ifndef PHONONITEM_H
#define PHONONITEM_H
#include <phonon>
#include "metadataobject.h"

namespace Phonon {
    class MetaDataLoader;
};

/** A wrapper around Phonon::MediaSource.
    Grabs metadata for media files from metadata tags,
    in a non-blocking way using the Phonon API.
    Phonon creates at least 1 thread for each metadata fetch.

    Don't create lots of instances of this directly - use MetaDataLoader.
    
    Tested on Linux, Qt 4.7.1. It seems to not work with MP3s on Windows,
    but that is also true of the Qt 4.7 phonon mediaplayer example
    (in loading metadata, that is)

    @see MetaDataLoader::get()
    @version 1.0  2010-10-05
*/
//start id="phononitem"
class PhononItem : public MetaDataObject {
    Q_OBJECT
public:
    friend class Phonon::MetaDataLoader;
    virtual ~PhononItem();
//end
    /** changes the fileName. Clears resources.
        Does not initiate fetching of metadata. */
    virtual void setFileName(QString name);
    virtual Preference preference() const ;
    virtual QString genre() const;
    virtual QString artist() const;
    virtual QString albumTitle() const;
    virtual QString trackTitle() const;
    virtual QString trackNumber() const;
    virtual QTime trackTime() const;
    virtual QString comment() const;
    Phonon::MediaSource source() {
        return m_mediaSource;
    }
//start id="phononitem"
    /** @return false if the data is not in the database.
     For valid files, it will fetch the data but in
     a non-blocking way */
    bool checkMetaData() const;

protected:
    /** @see MetaDataLoader::get() */
    explicit PhononItem(QString path=QString(), QObject* parent=0);
    void fetchMetaData();
//end
private slots:
    void setTotalTime(qint64 tt);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
//start id="phononitem"
signals:
    void fetched(bool success = true);
private:
    bool m_timeSet, m_loaded;
    QString extendedComment;
    Phonon::MediaSource m_mediaSource;
    Phonon::MediaObject *m_metaMedia;
};
//end


#endif // PHONONITEM_H
