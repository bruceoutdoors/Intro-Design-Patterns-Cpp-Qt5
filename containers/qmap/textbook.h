#ifndef _TEXTBOOK_H_
#define _TEXTBOOK_H_

#include <QObject>
#include <QString>
#include <QMap>

class Textbook : public QObject {
    Q_OBJECT
  public:
    Textbook(QString title, QString author, QString isbn, uint year);
//end
    QString getAuthor() const;
    QString getTitle() const;
    QString getIsbn() const;
    uint getYearPub() const;
    QString toString() const;
public slots:
    void setTitle(const QString& newTitle);
    void setIsbn(const QString &newIsbn);
    void setYearPub(uint newYear);
    void setAuthor(const QString& newAuthor);
//start
private:
    QString m_Title, m_Author, m_Isbn;
    uint m_YearPub;
};

/* Managed collection of pointers */
class TextbookMap : public QMap<QString, Textbook*> {
  public:
    ~TextbookMap();
    /** Adds the TextBook to the map, keyed on the ISBN */
    void add(Textbook* text);
    QString toString() const;

};
#endif
