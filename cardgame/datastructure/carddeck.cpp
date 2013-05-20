#include "carddeck.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <memory>

static int const SUIT_NUM = 4;
static int const FACE_NUM = 13;

CardDeck::CardDeck()
{
    restoreDeck();
}

// random takes out card and returns a hand
CardHand CardDeck::deal(int handSize)
{
    // set seed:
    srand(time(0));

    std::shared_ptr<CardHand> hand(new CardHand);
    int randInt;

    // if we ran out of cards:
    if(handSize > this->count()) {
        qDebug() << "\n*~ We're out of cards, restoring deck... ~*\n";
        restoreDeck();
    }

    for(int i = 0; i < handSize; i++) {
        // select an index from deck:
        randInt = rand() % this->count();
        // take and remove
        hand->append((*this)[randInt]);
        this->removeAt(randInt);
    }
    return *hand;
}

QString CardDeck::toString()
{
    QString str;
    for(Card& card : *this) {
        str.append(card.toString() + ", ");
    }
    return str;
}

void CardDeck::restoreDeck()
{
    // clear deck if it's empty
    if(!this->isEmpty()) {
        this->clear();
    }
    for(int suit = 0; suit < SUIT_NUM; suit++) {
        for(int face = 0; face < FACE_NUM; face++) {
            Card *card = new Card(face, suit);
            this->append(*card);
        }
    }
}

int CardDeck::getCardsLeft() const { return this->count(); }
