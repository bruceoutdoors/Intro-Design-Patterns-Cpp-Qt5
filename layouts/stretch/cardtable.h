#ifndef CARDTABLE_H
#define CARDTABLE_H
#include <QWidget>
#include "cardpics.h"

class CardTable : public QWidget {
    public:
    CardTable();
private:
    CardPics m_deck;
};

#endif        //  #ifndef CARDTABLE_H
