#include "carddeck.h"
#include <QDebug>
#include <cstdlib>
#include <chrono>
#include <memory>
#include <algorithm>
#include <QtAlgorithms>

static int const SUIT_NUM = 4;
static int const FACE_NUM = 13;

CardDeck::CardDeck()
{
    shuffleDeck();
}

// random takes out card and returns a hand
CardHand *CardDeck::deal(int handSize)
{
    CardHand *hand = new CardHand();

    // if we ran out of cards:
    if(handSize > count()) {
        qDebug() << "\n*~ We're out of cards, restoring deck... ~*\n";
        shuffleDeck();
    }

    for(int i = 0; i < handSize; i++) {
        // take and remove last item
        hand->append(last());
        removeLast();
    }
    return hand;
}

QString CardDeck::toString()
{
    QString str;
    for(Card *card : *this) {
        str.append(card->toString() + ", ");
    }
    return str;
}

void CardDeck::shuffleDeck()
{
    // clear deck if it's empty
    if(!isEmpty()) {
        // REMEMBER to delete pointers!!! >_<
        qDeleteAll(*this);
        clear();
    }
    for(int suit = 0; suit < SUIT_NUM; suit++) {
        for(int face = 0; face < FACE_NUM; face++) {
            append(new Card(face, suit));
        }
    }
    // shuffle deck
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(begin(), end(), std::default_random_engine(seed));
}

int CardDeck::getCardsLeft() const { return count(); }

CardDeck::~CardDeck()
{
    qDeleteAll(*this);
    clear();
}
