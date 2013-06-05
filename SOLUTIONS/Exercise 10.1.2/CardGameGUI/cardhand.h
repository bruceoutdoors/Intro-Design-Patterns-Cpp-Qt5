#ifndef CARDHAND_H
#define CARDHAND_H

#include <QString>
#include <QList>
#include <card.h>

class CardHand : public QList <Card>
{
public:
    int getValue();
    QString toString();

private:
    bool gotAce;
};

#endif // CARDHAND_H
