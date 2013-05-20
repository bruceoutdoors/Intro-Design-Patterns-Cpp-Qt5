#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{
public:
    Card(int faceNbr, int suitNbr);
    QString toString();
    QString getFace();
    QString getSuit();
    int getValue();

private:
    int m_FaceNbr;
    int m_SuitNbr;
    static QStringList s_Faces;
    static QStringList s_Suits;
};

#endif // CARD_H
