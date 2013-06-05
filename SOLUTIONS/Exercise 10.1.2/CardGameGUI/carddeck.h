#ifndef CARDDECK_H
#define CARDDECK_H

#include "card.h"
#include "cardhand.h"
#include <QList>

class CardDeck : public QList <Card>
{
public:
    CardDeck();
    CardHand deal(int handSize);
    QString toString();
    int getCardsLeft() const;
    void restoreDeck();
};

#endif // CARDDECK_H
