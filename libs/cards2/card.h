#ifndef CARD_H
#define CARD_H

#include "cards_export.h"
#include <QString>
#include <QLabel>

/** A QLabel that shows a card */
class CARDS_EXPORT Card : public QLabel {
    Q_OBJECT
  public:
    Card(QString name, QWidget* parent=0);
    int value();
    bool isAce() const;
private:
    QPixmap m_pixmap;

};

#endif        //  #ifndef CARD_H
