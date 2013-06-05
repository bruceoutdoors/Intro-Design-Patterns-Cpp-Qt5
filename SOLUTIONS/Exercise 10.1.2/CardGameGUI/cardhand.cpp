#include "cardhand.h"

int CardHand::getValue()
{
    int value = 0;
    for(Card *card : *this) {
        if(card->getFace() == "a") {
            gotAce = true;
        }
        value += card->getValue();
    }
    // value of Ace is either 1 or 11:
    if((value <= 11) && (gotAce == true)) {
        value += 10;
    }
    return value;
}

QString CardHand::toString()
{
    QString cards;
    for(Card *card : *this) {
        cards.append(card->toString() + ", ");
    }
    return cards;
}

CardHand::~CardHand()
{
    qDeleteAll(*this);
    clear();
}
