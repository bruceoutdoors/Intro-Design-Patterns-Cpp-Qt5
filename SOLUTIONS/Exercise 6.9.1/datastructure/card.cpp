#include "card.h"
#include <QStringList>

// conversion constructor
Card::Card(int faceNbr, int suitNbr)
    : m_FaceNbr(faceNbr), m_SuitNbr(suitNbr){}

QString Card::toString() const
{
//    return getFace() + " " + getSuit();
    return QString("%1 %2").arg(getFace()).arg(getSuit());
}

// returns value of card based on rules of bridge
int Card::getValue() const
{
    switch(m_FaceNbr) {
        case 10: return 1; // jack
        break;
        case 11: return 2; // queen
        break;
        case 12: return 3; // king
        break;
        case 0: return 4; // ace
        break;
        default : return 0;
    }
}

QStringList Card::s_Faces = QStringList() << "A" << "2" << "3" << "4"
                                          << "5" << "6" << "7" << "8"
                                          << "9" << "T" << "J" << "Q"
                                          << "K";

QStringList Card::s_Suits = QStringList() << "Clubs" << "Diamonds"
                                          << "Hearts" << "Spades";

QString Card::getFace() const { return s_Faces[m_FaceNbr]; }
QString Card::getSuit() const { return s_Suits[m_SuitNbr]; }

