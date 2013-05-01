#ifndef METADATALOADER_H
#define METADATALOADER_H
#include "phonon_mdexport.h"
#include "phononitem.h"
#include <QSharedPointer>
#include <QSemaphore>
#include <QTimer>
#include <QTime>
#include <QEvent>
#include "metadatavalue.h"
#include "abstractmetadataloader.h"

namespace Phonon {

/** class that loads metadata tags via the PhononItem class.
    For mp3s, this only works on non-windows platforms due to phonon limitations.
    
    It is suggested you try some of the drop-in replacements for MetaDataLoader
    found in the ../filetagger and ../mobilitymetadata
    
*/
//start
class PHONON_MDEXPORT MetaDataLoader : public Abstract::MetaDataLoader {
	Q_OBJECT
public:
    /** @return a singleton instance */
    static MetaDataLoader* instance();
    explicit MetaDataLoader(QObject* parent=0);
    virtual ~MetaDataLoader();
    MetaDataLoader* clone(QObject* parent = 0);
    /** @returns immediately and signals later when the metadata is actually ready. */
    void get(QString path);
    bool isRunning() const ;
    void get(QStringList paths);
    /** @return list of supported file extensions for this program */
    const QStringList &supportedExtensions() ;
public slots:
    /** Call this is you want to stop fetching metadata */
    void cancel();

private slots:
    void failed();
    void grabFirst();
    void checkForWork();
    void copyData(bool success=true);

private:
    QTimer m_timeOut;
    bool m_isBusy;
    PhononItem m_item;
    QStringList m_queuedPaths;
    int totalFetched;
};
//end
}
#endif // METADATALOADER_H
