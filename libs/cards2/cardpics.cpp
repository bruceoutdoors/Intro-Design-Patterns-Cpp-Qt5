#include <QtGui>

#include "cardpics.h"

CardPics* CardPics::instance() {
    static CardPics* inst = 0;
    if (inst == 0)
        inst = new CardPics(qApp);
    return inst;
}
//start
const QString CardPics::values="23456789tjqka";
const QString CardPics::suits="cdhs";

CardPics::CardPics(QObject* parent) : QObject(parent) {
    foreach (QChar suit, suits) {
        foreach (QChar value, values) {
            QString card = QString("%1%2").arg(value).arg(suit);
            QImage image(fileName(card));
            m_images[card]= image;
        }
    }
}

QString CardPics::fileName(QString card) {
    return QString(":/images/%1.png").arg(card);   /* From resource */
}

/** If the card string is not a key, get() returns a null image. */
QImage CardPics::get(QString card) const {
   return m_images.value(card.toLower(), QImage());
}
//end

CardPics::~CardPics() {

}
