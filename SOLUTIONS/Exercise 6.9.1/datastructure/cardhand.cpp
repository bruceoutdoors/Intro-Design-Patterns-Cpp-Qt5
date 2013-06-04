#include "cardhand.h"

int CardHand::getValue()
{
    int value = 0;
    for(Card& card : *this) {
        value += card.getValue();
    }
    return value;
}

QString CardHand::toString()
{
    QString cards;
    for(Card& card : *this) {
        cards.append(card.toString() + ", ");
    }
    return cards;
}
