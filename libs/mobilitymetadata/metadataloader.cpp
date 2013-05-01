#include <QApplication>
#include <QMediaPlayer>
#include "metadataloader.h"
#include <QDebug>

using namespace Mobility;

MetaDataLoader::MetaDataLoader(QObject* parent) :
    Abstract::MetaDataLoader(parent) {
    setObjectName("MetaDataLoader");
    m_player = new QMediaPlayer(this);
    m_fetched = false;
    m_isRunning = false;
    m_timeOut.setSingleShot(true);
    connect (m_player, SIGNAL(metaDataChanged()), this, SLOT(fetch()));
    connect (&m_timeOut, SIGNAL(timeout()), this, SLOT(failed()));
}

MetaDataLoader* MetaDataLoader::clone(QObject *parent) {
    return new MetaDataLoader(parent);
}

MetaDataLoader* MetaDataLoader::instance() {
    static MetaDataLoader* retval = 0;
    if (retval == 0) {
        qDebug() << "Mobility::MetaDataLoader";
        retval = new MetaDataLoader(qApp);
    }
    return retval;
}

void MetaDataLoader::get(QString fn) {
    m_queue << fn;
    if (!m_isRunning) {
         m_timer.singleShot(20, this, SLOT(checkForWork()));
    }
    else {
        m_timer.singleShot(2000, this, SLOT(checkForWork()));
    }
}


void MetaDataLoader::fetch() {
    if (m_fetched) return;
    if (m_player->error() != QMediaPlayer::NoError) {
        qDebug() << "fetch error: " << m_player->errorString() << m_player->error();
        failed();
    }
    if (!m_player->metaData(QtMultimediaKit::AlbumArtist).isNull())
    m_current.setArtist(m_player->metaData(QtMultimediaKit::AlbumArtist).toString());
    m_current.setAlbumTitle(m_player->metaData(QtMultimediaKit::AlbumTitle).toString());
    m_current.setTrackNumber(m_player->metaData(QtMultimediaKit::TrackNumber).toString());

    m_current.setComment(m_player->metaData(QtMultimediaKit::Comment).toString());
    m_current.setTrackTitle(m_player->metaData(QtMultimediaKit::Title).toString());
    m_current.setGenre(m_player->metaData(QtMultimediaKit::Genre).toString());
    QVariant imgvar = m_player->metaData(QtMultimediaKit::CoverArtImage);
    QList<QtMultimediaKit::MetaData> metadata = m_player->availableMetaData ();
    QStringList sl = m_player->availableExtendedMetaData();
    if (!imgvar.isNull())
        m_current.setImage(qVariantValue<QImage>(imgvar));

    // Musicmatch rating:
    QString rating = m_player->extendedMetaData("extended-comment").toString();
    if (!rating.isEmpty()) {
        int equalsPos = rating.indexOf("=");
        if (equalsPos != -1)
            rating = rating.mid(equalsPos+1);
        else m_current.setComment(rating);
        Preference p(rating);
        m_current.setPreference(p);
    }

    if (m_player->duration() > 0) {
        m_timeOut.stop();
        QTime t;
        t = t.addMSecs(m_player->duration());
        m_current.setTrackTime(t);
        emit fetched(m_current);
        m_isRunning = false;
        m_fetched = true;
        m_player->stop();
        // Give a short delay so we don't thrash the player
        m_timer.singleShot(400, this, SLOT(checkForWork()));
    }

}

void MetaDataLoader::checkForWork() {
    if (m_isRunning || m_queue.isEmpty()) return;
    m_isRunning = true;

    QString fn = m_queue.first();
    m_queue.pop_front();
    m_current = MetaDataValue();
    m_current.setFileName(fn);
    QMediaContent mc(QUrl::fromLocalFile(fn));
    m_fetched = false;
    m_player->setMedia(mc);
    if (m_player->error() == QMediaPlayer::ServiceMissingError ||m_player->error() == QMediaPlayer::ResourceError ) {
//        qDebug() << "media player error: " << m_player->errorString() << m_player->error();
        m_player->deleteLater();
        qDebug() << "MetaDataLoader starting new Media Player.";
        m_player = new QMediaPlayer(this);
        connect (m_player, SIGNAL(metaDataChanged()), this, SLOT(fetch()));
        m_player->setMedia(mc);
    }
    if (m_player->error() != QMediaPlayer::NoError) {
        qDebug() << "2nd media player error (fatal): " << m_player->errorString() << m_player->error();
        failed();
        return;
    }
    if (m_player->availableMetaData().length() > 4) {
        fetch();
    }
    else m_timeOut.singleShot(3000, this, SLOT(failed()));
}

void MetaDataLoader::cancel() {
    m_cancelled = true;
    m_queue.clear();

}

void MetaDataLoader::get(QStringList fns) {
    m_queue << fns;
    checkForWork();
}
const QStringList& MetaDataLoader::supportedExtensions() {
    // TODO: get from QMediaServiceProvider::supportedMimeTypes ()
    static QStringList sl;
    if (sl.isEmpty()) {
        sl << "*.mp3" << "*.flac" << "*.wma" << "*.ogg" << "*.aiff";
    }
    return sl;
}

bool MetaDataLoader::isRunning() const {
    return m_isRunning;
}

void MetaDataLoader::setPlayer(QMediaPlayer *p) {
    m_player = p;
}

void MetaDataLoader::failed() {
    if (!m_isRunning) return;
    m_isRunning = false;
    qDebug() << "Failed to fetch: " << m_current.url();
    m_timer.singleShot(100, this, SLOT(checkForWork()));
}

