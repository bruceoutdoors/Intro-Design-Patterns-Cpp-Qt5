#include "textbookmap.h"
#include <QDebug>

//start id=impl
TextbookMap::~TextbookMap() {
    qDebug() << "Destroying TextbookMap ..." << endl;
    qDeleteAll(values());
    clear();
}

void TextbookMap::add(Textbook* text) {
    insert(text->getIsbn(), text);
}

QString TextbookMap::toString() const {
    QString retval;
    QTextStream os(&retval);
    ConstIterator itr = constBegin();
    for ( ; itr != constEnd(); ++itr)
        os << '[' << itr.key() << ']' << ": "
        << itr.value()->toString() << endl;
    return retval;
}
//end
