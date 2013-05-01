#include "activity.h"
#include <QtGui>

static QHash<QString, QIcon> icons;

QMovie* getMovie() {
    static QMovie* movie = 0;
    if (movie == 0) {
        movie = new QMovie(":/icons/activity.gif", "gif", qApp);
        movie->start();
    }
    return movie;
}

QIcon getCurrentIcon() {
    QMovie* movie = getMovie();
    int idx = movie->currentFrameNumber();
    QString key = QString("%1").arg(idx);
    if (!icons.contains(key)) {
        QPixmap pm = movie->currentPixmap();
        QIcon retval(pm);
        icons[key] = retval;
    }
    return icons[key];
}

ActivityButton::ActivityButton(QString text, QWidget* parent)
: QPushButton(text, parent), m_isActive(false) {
    setIcon(QIcon(":/icons/inactive.png"));   
}

void ActivityButton::setActive(bool isActive) {
    if (m_isActive == isActive) return;
    m_isActive = isActive;
    if (isActive) {
        connect (getMovie(), SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon()), Qt::UniqueConnection);
    }
    else {
        disconnect (getMovie(), 0, this, 0);
        setIcon(QIcon(":/icons/inactive.png"));
    }
}

void ActivityButton::updateIcon() {
    setIcon(getCurrentIcon());   
}
