#ifndef CARDPICS_H
#define CARDPICS_H

#include <QMap>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QObject>
#include "cards_export.h"

//start
/** A convenience class for providing QImages of cards.
*/
class CARDS_EXPORT CardPics : public QObject {
  public:
    explicit CardPics(QObject* parent=0);
    ~CardPics() ;
    static CardPics* instance();
    /** @param card can be a string of numbers or lower case
        letters. 
        ac=ace of clubs. ts=ten of spades 
        @return a QPixmap corresponding to the card number
       in the deck */
    QImage get(QString card) const;
    static const QString values;
    static const QString suits;
  protected:
    static QString fileName(QString card);    
  private:
    QMap<QString, QImage> m_images;
};
//end


#endif        //  #ifndef CARDPICS_H
