#ifndef METADATALOADER_H
#define METADATALOADER_H

#include <QObject>
#include <QTimer>
#include "metadatavalue.h"
#include "filetagger_export.h"
#include "abstractmetadataloader.h"

namespace TagLib {

//start
/** Loads metadata from mp3 files using TagLib 1.6.3.
    http://developer.kde.org/~wheeler/taglib.html
*/
class FILETAGGER_EXPORT MetaDataLoader 
                          : public Abstract::MetaDataLoader {
    Q_OBJECT
public:
    typedef Abstract::MetaDataLoader SUPER;
    explicit MetaDataLoader(QObject *parent = 0);
    static MetaDataLoader* instance();
    virtual ~MetaDataLoader() {}
    const QStringList &supportedExtensions() ;
    /** non-blocking method that fetches metadata.
        A fetched() signal is emitted when metadata is ready.
    */
    MetaDataLoader* clone(QObject *parent) ;
    void get(QString path);
    void get(QStringList path);
    bool isRunning() const {return m_running;}
public slots:
    void cancel();
private slots:
    void checkForWork();

private:
    bool m_running;
    bool m_canceled;
    int m_processingMax;
    QStringList m_queue;
    QTimer m_timer;
};
}

//end

#endif // METADATALOADER_H
