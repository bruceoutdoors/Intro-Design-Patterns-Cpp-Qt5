#ifndef METADATALOADER_H
#define METADATALOADER_H

#include "mobmetaexport.h"
#include <QTimer>
#include "metadataobject.h"
#include <QMediaPlayer>
#include "abstractmetadataloader.h"
namespace Mobility {
/** Metadataloader using multimediakit from Qt Mobility 1.1.1 
    Known issues: Does not read id3 tags from mp3s on windows due to backend limitations.
    Tested on Linux and Symbian.
*/
class MOBMETAEXPORT MetaDataLoader : public Abstract::MetaDataLoader {
    Q_OBJECT
public:
    explicit MetaDataLoader(QObject* parent = 0);
    static MetaDataLoader* instance();
    const QStringList& supportedExtensions();
    /** non-blocking interface results in fetched() signal later */
    virtual void get(QString fileName);
    void get(QStringList fns);
    MetaDataLoader* clone(QObject *parent);
    bool isRunning() const;
public slots:
    void setPlayer(QMediaPlayer* p);
    void checkForWork();
    void cancel();
private slots:
    void fetch();
    void failed();
private:
    QTimer m_timer;
    QTimer m_timeOut;
    bool m_isRunning;
    bool m_fetched;
    bool m_cancelled;
    QMediaPlayer* m_player;
    QStringList m_queue;
    MetaDataObject m_current;
};
}
#endif // METADATALOADER_H
