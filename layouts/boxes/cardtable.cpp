#include "card.h"
#include "cardtable.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

//start

CardTable::CardTable(QWidget* parent)
: QWidget(parent) {

    QHBoxLayout* row = new QHBoxLayout();       /* First row */
    row->addWidget(new Card("ah"));             /* Parents are set by layout, so we don't have to. */
    row->addWidget(new Card("qd"));
    row->addWidget(new Card("ks"));
    row->addWidget(new Card("8c"));

    QVBoxLayout* rows = new QVBoxLayout();      /* Lay out rows vertically. */
    rows->addLayout(row);                       /* Nest a row in the vertical layout. */

    row = new QHBoxLayout();                    /* Second row */
    row->addWidget(new Card("qs"));
    row->addWidget(new Card("js"));
    row->addWidget(new Card("td"));
    rows->addLayout(row);                       /* Nesting again */

    QVBoxLayout* buttons = new QVBoxLayout();   /* A column for the buttons */
    buttons->addWidget(new QPushButton("Deal"));
    buttons->addWidget(new QPushButton("Shuffle"));

    QHBoxLayout* cols = new QHBoxLayout();      /* Bring them all together. */
    setLayout(cols);                            /* The "root layout" for this widget */
    cols->addLayout(rows);                      /* Add both card rows as a column. */
    cols->addLayout(buttons);                   /* Add column of buttons as another column. */
}
//end
