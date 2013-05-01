#ifndef LIBRARY_H_                                                                           
#define LIBRARY_H_                                                                           
                                                                                             
#include <QList>   
#include <QString>
#include <QStringList>

//start id=refbaseclassdef                                                                                           
class RefItem {                                                                              
public:   
   virtual ~RefItem();
   QString getItemType() const;
   QString getISBN() const;
   QString getTitle() const;
   int getNumberOfCopies() const;
   virtual QString toString(QString sep="[::]") const;
   void setNumberOfCopies(int newVal);
protected:
   RefItem(QString type, QString isbn, QString title, int numCopies=1);
   RefItem(QStringList& proplist);
private:                                                                                     
   QString m_ItemType, m_ISBN, m_Title;
   int m_NumberOfCopies;
};
//end
//start id=refderiveddefs
class Book : public RefItem {
public:
   Book(QString type, QString isbn, QString title, QString author, 
        QString pub, int year, int numCopies=1);
   Book(QStringList& proplist);
   virtual QString toString(QString sep="[::]") const;
   QString getAuthor() const;
   QString getPublisher() const;
   int getCopyrightYear() const;
private:
   QString m_Author, m_Publisher;
   int m_CopyrightYear;
};

class ReferenceBook : public Book {
public:
   enum RefCategory {NONE = -1, Art, Architecture, ComputerScience,
                     Literature, Math, Music, Science};
   ReferenceBook(QString type, QString isbn, QString title, 
                 QString author, QString pub, int year, 
                 RefCategory refcat, int numCopies=1);
   ReferenceBook(QStringList& proplist);
   QString toString(QString sep="[::]") const;
   RefCategory getCategory() const;
   QString categoryString() const;         /* Returns string version of m_Category. */
   static QStringList getRefCategories();  /* Returns a list of categories. */
private:
   RefCategory m_Category;
};
//end
class TextBook : public Book {
public:
   TextBook(QString type, QString isbn, QString title, QString author, 
        QString pub, int year, QString course, int numCopies=1);
   TextBook(QStringList& proplist);
   QString toString(QString sep="[::]") const;
   QString getCourse() const;
private:
   QString m_Course; 
};

class Dvd : public RefItem {
public:
   Dvd(QString type, QString isbn, QString title,int disks, 
       bool twoSided, int numCopies=1);
   Dvd(QStringList& proplist);
   QString toString(QString sep="[::]") const;
   int getNumberOfDisks() const;
   bool isTwoSided() const;
private:
   int m_NumberOfDisks;
   bool m_TwoSided;
};

class Film : public Dvd {
public:
   Film(QString type, QString isbn, QString title,int disks, 
        bool twoSided, QString star,QString director, int minutes, 
        bool blueray, int numCopies=1);
   Film(QStringList& proplist);
   QString toString(QString sep="[::]") const;
   QString getStar() const;
   QString getDirector() const;
   int getMinutes() const;
   bool isBlueray() const;
private:
   QString m_Star, m_Director;
   int m_Minutes;
   bool m_BlueRay;
};

class DataDvd : public Dvd {
public:
   DataDvd(QString type, QString isbn, QString title,int disks, 
           bool twoSided, QString protocol, int numCopies=1);
   DataDvd(QStringList& proplist);
   QString toString(QString sep="[::]") const;
   QString getDBProtocol() const;
private:
   QString m_DBProtocol;
};

//start id=libdef
class Library : public QList<RefItem*> {
public:
   Library() {}
   ~Library();                             /* A container of pointers must have a destructor! */
   void addRefItem(RefItem*& refitem);
   int removeRefItem(QString isbn);
   QString toString(QString sep="\n") const;
   bool isInList(QString isbn);
   QString getItemString(QString isbn);
private:
   Library(const Library&);
   Library& operator=(const Library&);
   RefItem* findRefItem(QString isbn);
};
//end

#endif

