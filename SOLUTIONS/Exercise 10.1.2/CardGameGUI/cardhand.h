#ifndef CARDHAND_H
#define CARDHAND_H

#include <QString>
#include <QList>
#include <card.h>

class CardHand : public QList <Card*>
{
public:
    int getValue();
    ~CardHand();
    QString toString();
    QList<QLabel*> getLabels();

private:
    bool gotAce;
};

#endif // CARDHAND_H
