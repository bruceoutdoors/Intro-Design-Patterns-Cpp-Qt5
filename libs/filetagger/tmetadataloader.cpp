#include <QtCore>
#include <taglib/mpegfile.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include "tmetadataloader.h"
#include "preference.h"

using namespace TagLib;

/** Given a filename, fetches metadata.
    A functor for using TagLib in a with functional algorithm.
    Unfortunately, it is not thread-safe so we don't use it with QtConcurrent. 
*/
class MetaDataFunctor : public std::unary_function<QString, MetaDataValue> {
public:
    MetaDataValue operator()(QString path);
};


QString toQString(const TagLib::String &s) {
#ifdef Q_OS_WIN
    return QString::fromAscii(s.toCString());
#else
    return QString::fromStdWString(s.toWString());
#endif
}

const QString FMPSPREFIX="[FMPS_Rating] FMPS_Rating ";
QRegExp fmpsRx("FMPS_Rating ([\\d\\.]+)");
//start id="functor"
MetaDataValue MetaDataFunctor::operator ()(QString path) {
    using namespace TagLib;
    MetaDataValue retval;
    FileRef f(path.toLocal8Bit().constData());
    const Tag* t = f.tag();
    Q_ASSERT( t != NULL ) ;
    retval.setFileName(path);
    retval.setTrackTitle(toQString(t->title()));
    retval.setArtist(toQString(t->artist()));
    retval.setAlbumTitle(toQString(t->album()));
//end
    QString trackNumber = QString("%1").arg(t->track());
    retval.setTrackNumber(trackNumber);
    retval.setGenre(toQString(t->genre()));
    retval.setComment(toQString(t->comment()));
#ifdef FMPS_RATING
    // http://www.freedesktop.org/wiki/Specifications/free-media-player-specs
    MPEG::File mpegFile(path.toLocal8Bit());
    const ID3v2::Tag *id3v2 = mpegFile.ID3v2Tag();
    if (id3v2 != 0) {
        ID3v2::FrameListMap map = id3v2->frameListMap();
        ID3v2::FrameList fl = map["TXXX"];
        if (!fl.isEmpty()) {
            QString v = toQString(fl.front()->toString());
            if (v.contains(fmpsRx)) {
                QString ratingStr = fmpsRx.cap(1);
                double dr = ratingStr.toDouble() * 10.0;
                int rating = (int)dr;
                Preference p(rating);
                retval.setPreference(p);
            }
        }
        //ID3v2::FrameList::ConstIterator litr = fl.begin();
//        while (litr != fl.end()) {
//            ++litr;
//        }
    }
#else
    // musicmatch style preference
    retval.setPreference(retval.comment());
#endif

//start id="functor"
    QTime time(0,0,0,0);
    const AudioProperties* ap = f.audioProperties();
    time = time.addSecs(ap->length());
    retval.setTrackTime(time);
    return retval;
}
//end

const QStringList & TagLib::MetaDataLoader::supportedExtensions() {
    static QStringList sl;
    // TODO: get from Phonon backend mimetypes list?
    if (sl.isEmpty())
        sl << "*.mp3" << "*.flac" << "*.wma" << "*.ogg" << "*.aiff";
    return sl;
}

TagLib::MetaDataLoader* TagLib::MetaDataLoader::instance() {
    static TagLib::MetaDataLoader* inst = 0;
    if (inst == 0) {
        inst = new TagLib::MetaDataLoader(qApp);
    }
    return inst;
}

//start id="metadataloader"
TagLib::MetaDataLoader::MetaDataLoader(QObject *parent) :
    SUPER(parent) {
    m_processingMax = 0;
    m_running = false;
    qDebug() << "TagLib::MetaDataLoader created.";
    connect (this, SIGNAL(finished()), this, SLOT(checkForWork()),
             Qt::QueuedConnection);
}

void TagLib::MetaDataLoader::get(QString path) {
    m_queue << path;
    m_timer.singleShot(2000, this, SLOT(checkForWork()));
}

void TagLib::MetaDataLoader::checkForWork() {
    MetaDataFunctor functor;
    if (m_queue.isEmpty() && !m_running) {
        m_processingMax = 0;
        return;
    }
    if (m_running ) return;
    m_running = true;
    m_canceled = false;
    while (!m_queue.isEmpty()) {
        QStringList sl = m_queue;
        m_queue = QStringList();
        m_processingMax = sl.length();
        emit progressRangeChanged(0, m_processingMax);
        for (int i=0; i<m_processingMax;++i) {
            if (m_canceled) break;
            emit fetched(functor(sl[i]));
            emit progressValueChanged(i);
            qApp->processEvents();          /* Allow the GUI to process events
                (and our signals to be delivered). */
        }
        m_running = false;
    }
    emit finished();
}
//end

void TagLib::MetaDataLoader::cancel() {
    m_canceled = true;
}

void TagLib::MetaDataLoader::get(QStringList paths) {
    m_queue.append(paths);
    checkForWork();
}

MetaDataLoader* MetaDataLoader::clone(QObject *parent) {
    return new MetaDataLoader(parent);
}

