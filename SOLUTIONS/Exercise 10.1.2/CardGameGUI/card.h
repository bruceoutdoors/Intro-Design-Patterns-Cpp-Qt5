#ifndef CARD_H
#define CARD_H

#include <QString>
class QLabel;

class Card
{
public:
    Card(int faceNbr, int suitNbr);
    QString toString() const;
    QString getFace() const;
    QString getSuit() const;
    QString getImage() const;
    int getValue() const;
    QLabel* getLabel();

private:
    int m_FaceNbr;
    int m_SuitNbr;
    static QStringList s_Faces;
    static QStringList s_Suits;
};

#endif // CARD_H
