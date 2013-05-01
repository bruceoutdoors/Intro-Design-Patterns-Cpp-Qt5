#ifndef AMETADATALOADER_H
#define AMETADATALOADER_H

#include "metadatavalue.h"

//start
namespace Abstract {
/** Abstract Interface for loading metadata from files.
    Create a concrete instance and add it as a child to qApp,
    and you can retrieve it via the abstract instance() method
    here.
*/
class METADATAEXPORT MetaDataLoader : public QObject {
    Q_OBJECT
public:
    
    explicit MetaDataLoader(QObject *parent = 0) 
    	: QObject(parent) {}
    
    /** @return the first instance found of MetaDataLoader that is 
        a child of qApp */
    static MetaDataLoader* instance();
    /** Returns another instance of the same type */
    virtual MetaDataLoader* clone(QObject* parent=0) = 0;
    virtual ~MetaDataLoader();
    virtual const QStringList& supportedExtensions() = 0;
    /** non-blocking method that fetches metadata.
        A fetched() signal is emitted when metadata is ready.
    */
    virtual void get(QString path) = 0;
    virtual void get(QStringList path) = 0;
    virtual bool isRunning() const = 0;
public slots:
    virtual void cancel() = 0;
    
signals:
    /** Emitted when metadata has been fetched by this object */
    void fetched(const MetaDataValue& mdv);
    void progressValueChanged(int);
    void progressRangeChanged(int, int);
    void finished();

};
}

#endif // AMETADATALOADER_H
