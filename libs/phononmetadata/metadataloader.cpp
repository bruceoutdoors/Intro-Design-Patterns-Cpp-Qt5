#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include "phononitem.h"
#include "metadataloader.h"

using namespace Phonon;

void MetaDataLoader::cancel() {
    m_queuedPaths.clear();
}

MetaDataLoader* MetaDataLoader::instance() {
    static MetaDataLoader *inst = 0;
    if (inst == 0) {
        inst = new MetaDataLoader(qApp);
    }
    return inst;
}
MetaDataLoader::~MetaDataLoader() {

}

MetaDataLoader* MetaDataLoader::clone(QObject *parent) {
    return new MetaDataLoader(parent);
}
MetaDataLoader::MetaDataLoader(QObject* parent)
    : Abstract::MetaDataLoader(parent) {
    totalFetched = 0;
    setObjectName(tr("MetaDataLoader"));
    qDebug() << "New Phonon::MetaDataLoader";
    m_isBusy = false;
    m_timeOut.setSingleShot(true);
    connect (&m_timeOut, SIGNAL(timeout()), this, SLOT(failed()));
    connect (&m_item, SIGNAL(fetched(bool)),
             this, SLOT(copyData(bool)), Qt::QueuedConnection);

}


void MetaDataLoader::checkForWork() {
    if (m_queuedPaths.isEmpty() && !m_isBusy) {
        emit finished();
        totalFetched = 0;
    }
    else {
        grabFirst();
    }
}

//start id="get"
void MetaDataLoader::get(QString path ) {
    QFileInfo fi(path);
    m_queuedPaths << fi.absoluteFilePath();  /* Queue for fetching later. */
    emit progressRangeChanged(0, m_queuedPaths.size());
    checkForWork();
}
//end
//start id=grab
void MetaDataLoader::grabFirst() {
    if (m_isBusy) return;
    m_isBusy = true;
    QString path = m_queuedPaths.takeFirst();
//    qDebug() << "Fetching: " << path;
    m_item.setFileName(path);
    m_item.checkMetaData();   /* Starts 2 threads on Linux */
    m_timeOut.start(4000);


}
//end

//start id=notify
void MetaDataLoader::copyData(bool success) {
    MetaDataValue mdv = m_item;
    m_timeOut.stop();
    emit progressValueChanged(++totalFetched);
    emit fetched(mdv);      /* MetaDataValue must be registered */
    m_isBusy = false;
    checkForWork();
}
//end

const QStringList & MetaDataLoader::supportedExtensions() {
    static QStringList sl;
    // TODO: get from Phonon backend mimetypes list? 
    if (sl.isEmpty())
        sl << "*.mp3" << "*.flac" << "*.wma" << "*.ogg" << "*.aiff";
    return sl;
}

void MetaDataLoader::get(QStringList sl) {
    m_queuedPaths << sl;
    emit progressRangeChanged(0, m_queuedPaths.size());
    grabFirst();

}
bool MetaDataLoader::isRunning() const {
    return !m_isBusy && m_queuedPaths.isEmpty();
}

void MetaDataLoader::failed() {
    if (m_isBusy == false) return;
    qDebug() << "??? Failed to fetch metadata for: " << m_item.fileName();
    m_isBusy = false;
    checkForWork();
}
