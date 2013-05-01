#include "imagefunctor.h"
#include <QtGui>
#include "functors.h"

ImageFunctor::ImageFunctor(QObject* parent)
    : QObject(parent)
{

    m_imageLoader = new ImageLoader(this);
    connect (m_imageLoader, SIGNAL(imageLoaded(QImage)),
             this, SLOT(grabImage(QImage)));
    connect (m_imageLoader, SIGNAL(finished()), this, SLOT(transformQueue()));
    m_futureWatcher = 0;
    newFutureWatcher();
}
void ImageFunctor::newFutureWatcher() {
    if (m_futureWatcher!= 0)
        m_futureWatcher->deleteLater();

    m_futureWatcher = new QFutureWatcher<QImage>(this);
    connect(m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(grabImage(int)));
    connect(m_futureWatcher, SIGNAL(finished()), this, SLOT(transformQueue()));
/*    connect(m_futureWatcher, SIGNAL(progressRangeChanged(int,int)),
            this, SIGNAL(progressRangeChanged(int, int))); */
}

void ImageFunctor::cancel() {
    m_futureWatcher->cancel();
    m_futureWatcher->waitForFinished();
}

void ImageFunctor::pause(bool p) {
    m_futureWatcher->setPaused(p);
}


void ImageFunctor::grabImage(QImage img) {
    emit progressCurrent(m_current);
    m_imageQueue << img;
    transformQueue();
}
void ImageFunctor::transformQueue() {
    if (m_futureWatcher->isRunning()) return;
    int count = m_imageQueue.size();
    if (count == 0) {
        if (!m_imageLoader->isRunning())
            emit finished();
        return;
    }
    emit statusMessage("Transforming in Parallel...");

    QList<QImage> images = m_imageQueue;
    m_imageQueue.clear();
    m_current += images.count();
    newFutureWatcher();
    m_futureWatcher->setFuture(QtConcurrent::mapped(images, Scale()));
    Q_ASSERT(m_futureWatcher->isStarted());
    Q_ASSERT(m_futureWatcher->isRunning());
}

void ImageFunctor::grabImage(int num) {
    QImage img = m_futureWatcher->resultAt(num);
    emit transformedImage(img);
}

bool ImageFunctor::isRunning() const {
    return m_futureWatcher->isRunning();
}

ImageFunctor::~ImageFunctor() {
    m_futureWatcher->cancel();
    m_futureWatcher->waitForFinished();
}

void ImageFunctor::processImages(QStringList files) {
    QSettings s;
    s.setValue("files", files);
    bool loadFirst = s.value("loadFirst", false).toBool();
    m_max = files.count();
    emit progressRangeChanged(0, m_max);
    if (loadFirst) {
        emit statusMessage("Loading Files in a single thread...");
        m_imageLoader->loadImages(files);
    }
    else {
//start id=useFunctor
        connect(m_futureWatcher, SIGNAL(progressValueChanged(int)),
                this, SIGNAL(progressCurrent(int)));
        emit statusMessage("Loading and Transforming in parallel");
        m_futureWatcher->setFuture(QtConcurrent::mapped(files,
                                                  LoadAndScale()));
//end
    }
}
