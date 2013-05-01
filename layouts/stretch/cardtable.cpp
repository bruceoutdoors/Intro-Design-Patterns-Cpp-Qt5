#include "cardtable.h"
#include "card.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


CardTable::CardTable() {

    QVBoxLayout* rows = new QVBoxLayout();

    QHBoxLayout* row = new QHBoxLayout();
    row->addWidget(new Card("as"));
    row->addWidget(new Card("ah"));
    row->addWidget(new Card("ac"));
    row->addWidget(new Card("ad"));
    rows->addLayout(row);

    //start
    row = new QHBoxLayout();
    row->addWidget(new Card("td"));
    row->addWidget(new Card("js"));
    row->addWidget(new Card("kc"));
    rows->addLayout(row);
    rows->addStretch(1);                    /* Stretchable space for rows. */
    QVBoxLayout* buttons = new QVBoxLayout();
    buttons->addStretch(1);                 /* Stretchable space before buttons in column. */
    buttons->addWidget(new QPushButton("Deal"));
    buttons->addWidget(new QPushButton("Shuffle"));
    buttons->addSpacing(20);                /* Fixed spacing after buttons. */
    QHBoxLayout* cols = new QHBoxLayout();
    setLayout(cols);
    cols->addLayout(rows);
    cols->addLayout(buttons);
    cols->addStretch(0);                    /* How does this affect the size of the buttons? */
}
//end
