#ifndef TEXTBOOKMAP_H
#define TEXTBOOKMAP_H

#include <QString>
#include <QMap>
#include "textbook.h"

/* Managed collection of pointers */
class TextbookMap : public QMap<QString, Textbook*> {
  public:
    ~TextbookMap();
    /** Adds the TextBook to the map, keyed on the ISBN */
    void add(Textbook* text);
    QString toString() const;

};

#endif // TEXTBOOKMAP_H
