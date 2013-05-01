#include <QtGui>
#include "card.h"
#include "cardpics.h"


Card::Card(QString name, QWidget* parent) : QLabel(parent) {
    setObjectName(name);
    qDebug() << "new card: " << name ;
    m_pixmap = QPixmap::fromImage(CardPics::instance()->get(name));
    setPixmap(m_pixmap);
}

bool Card::isAce() const {
    return objectName().startsWith('a', Qt::CaseInsensitive);
}

