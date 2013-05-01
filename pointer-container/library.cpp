#include <QStringList>
#include <QDebug>
#include "library.h"

//Note: RefItem constructor is protected.
RefItem::RefItem(QString type, QString isbn, QString title, 
                 int numCopies) : m_ItemType(type), m_ISBN(isbn),
                 m_Title(title), m_NumberOfCopies(numCopies)
{ }

//start id=refctor
RefItem::RefItem(QStringList& plst) : m_ItemType(plst.takeFirst()), 
         m_ISBN(plst.takeFirst()), m_Title(plst.takeFirst()),
         m_NumberOfCopies(plst.takeFirst().toInt()) 
{ }
//end

RefItem::~RefItem() 
{ }

QString RefItem::getItemType() const {
   return m_ItemType;
}

QString RefItem::getISBN() const {
   return m_ISBN;
}

QString RefItem::getTitle() const {
   return m_Title;
}

int RefItem::getNumberOfCopies() const {
   return m_NumberOfCopies;
}

//start id=reftostring
QString RefItem::toString(QString sep) const {
   return
   QString("%1%2%3%4%5%6%7").arg(m_ItemType).arg(sep).arg(m_ISBN)
                            .arg(sep).arg(m_Title).arg(sep)
                            .arg(m_NumberOfCopies);
}
//end
void RefItem::setNumberOfCopies(int newValue) {
   m_NumberOfCopies = newValue;
}

Book::Book(QString type, QString isbn, QString title, 
   QString author, QString pub, int year, int numCopies) :
      RefItem(type, isbn, title,  numCopies), m_Author(author),
      m_Publisher(pub), m_CopyrightYear(year) 
{ }

//start id=refctor
Book::Book(QStringList& plst) : RefItem(plst), 
      m_Author(plst.takeFirst()), m_Publisher(plst.takeFirst()),
      m_CopyrightYear(plst.takeFirst().toInt())
{ }
//end

//start id=reftostring
QString Book::toString(QString sep) const {
   return QString("%1%2%3%4%5%6%7").arg(RefItem::toString(sep))
               .arg(sep).arg(m_Author).arg(sep).arg(m_Publisher)
               .arg(sep).arg(m_CopyrightYear);
}
//end

QString Book::getAuthor() const {
   return m_Author;
}

QString Book::getPublisher() const {
   return m_Publisher;
}

int Book::getCopyrightYear() const {
   return m_CopyrightYear;
}

ReferenceBook::ReferenceBook(QString type, QString isbn, 
               QString title, QString author, QString pub, 
               int year, RefCategory refcat, int numCopies) :
              Book(type, isbn, title, author,pub,year,numCopies), 
              m_Category(refcat)
{ }

//start id=refctor
ReferenceBook::ReferenceBook(QStringList& plst) : Book(plst), 
     m_Category(static_cast<RefCategory>(plst.takeFirst().toInt()))
{ }
//end

//start id=reftostring
QString ReferenceBook::toString(QString sep) const {
   return QString("%1%2%3").arg(Book::toString(sep)).arg(sep)
                          .arg(categoryString());
}
//end

ReferenceBook::RefCategory ReferenceBook::getCategory() const {
   return m_Category;
}

//start id=reftostring
QString ReferenceBook::categoryString() const {
   switch(m_Category) {
     case Art: return "Art";
     case Architecture: return "Architecture";
     case ComputerScience: return "ComputerScience";
     case Literature: return "Literature";
     case Math: return "Math";
     case Music: return "Music";
     case Science: return "Science";
   default: return "None";
   }
}
//end

QStringList ReferenceBook::getRefCategories() {
   QStringList cats;
   cats << "Art" << "Architecture" << "ComputerScience" 
   << "Literature" << "Math" << "Music" << "Science";
   return cats;
}

TextBook::TextBook(QString type, QString isbn, QString title, 
   QString author, QString pub, int year, QString course, 
   int numCopies) : 
   Book(type, isbn, title,  author,pub,year,numCopies), 
   m_Course(course)
{ }

TextBook::TextBook(QStringList& plst) : Book(plst),
          m_Course(plst.takeFirst())
{ }

QString TextBook::toString(QString sep) const {
   return QString("%1%2%3").arg(Book::toString(sep))
                           .arg(sep).arg(m_Course);
}

QString TextBook::getCourse() const {
   return m_Course;
}

      
Dvd::Dvd(QString type, QString isbn, QString title, int disks, 
         bool twoSided, int numCopies) : 
       RefItem(type, isbn, title,  numCopies), 
       m_NumberOfDisks(disks), m_TwoSided(twoSided)
{ }


Dvd::Dvd(QStringList& plst) : RefItem(plst), 
        m_NumberOfDisks(plst.takeFirst().toInt()), 
        m_TwoSided(plst.takeFirst().toInt())
{ }

QString Dvd::toString(QString sep) const {
   return QString("%1%2%3%4%5").arg(RefItem::toString(sep))
              .arg(sep).arg(m_NumberOfDisks).arg(sep)
              .arg(m_TwoSided);
}

int Dvd::getNumberOfDisks() const {
   return m_NumberOfDisks;
}

bool Dvd::isTwoSided() const {
   return m_TwoSided;
}

Film::Film(QString type, QString isbn, QString title,int disks, 
      bool twoSided, QString star, QString director, int minutes, 
      bool blueray, int numCopies) :
   Dvd(type, isbn, title,  disks,twoSided,numCopies), m_Star(star), 
   m_Director(director), m_Minutes(minutes), m_BlueRay(blueray)
{ }


Film::Film(QStringList& plst) : Dvd(plst), m_Star(plst.takeFirst()), 
   m_Director(plst.takeFirst()), m_Minutes(plst.takeFirst().toInt()), 
   m_BlueRay(plst.takeFirst().toInt())
{ }

QString Film::toString(QString sep) const {
   return QString("%1%2%3%4%5%6%7%8%9").arg(Dvd::toString(sep))
         .arg(sep).arg(m_Star).arg(sep).arg(m_Director)
         .arg(sep).arg(m_Minutes).arg(sep).arg(m_BlueRay);
}

QString Film::getStar() const {
   return m_Star;
}

QString Film::getDirector() const {
   return m_Director;
}

int Film::getMinutes() const {
   return m_Minutes;
}

bool Film::isBlueray() const {
   return m_BlueRay;
}

DataDvd::DataDvd(QString type, QString isbn, QString title, 
   int disks, bool twoSided, QString protocol, int numCopies) : 
   Dvd(type, isbn, title,  disks,twoSided,numCopies), 
   m_DBProtocol(protocol)
{ }


DataDvd::DataDvd(QStringList& plst) : Dvd(plst),
       m_DBProtocol(plst.takeFirst())
{ }

QString DataDvd::toString(QString sep) const {
   return QString("%1%2%3").arg(Dvd::toString(sep)).arg(sep)
           .arg(m_DBProtocol);
}

QString DataDvd::getDBProtocol() const {
   return m_DBProtocol;
}

//start id=libimpl
Library::~Library() {
   qDeleteAll(*this);
   clear();
}

Library::Library(const Library&) : QList<RefItem*>() {}

Library& Library::operator=(const Library&) {
   return *this;
}

void Library::addRefItem(RefItem*& refitem) { /* Parameter is a pointer reference so that null assignment after delete is possible. */
   QString isbn(refitem->getISBN());
   RefItem* oldItem(findRefItem(isbn));
   if(oldItem==0)
      append(refitem);
   else {
      qDebug() << isbn << " Already in list:\n"
               << oldItem->toString()
               << "\nIncreasing number of copies " 
               << "and deleting new pointer." ;
      int newNum(oldItem->getNumberOfCopies() + refitem->getNumberOfCopies());
      oldItem->setNumberOfCopies(newNum);
      delete refitem;                         /* Not in a managed container. */
      refitem = 0;                            /* Reference parameter! */ 
   }
}

int Library::removeRefItem(QString isbn) {
   RefItem* ref(findRefItem(isbn));
   int numCopies(-1);
   if(ref) {
      numCopies = ref->getNumberOfCopies() - 1;
      if(numCopies== 0) {
         removeAll(ref);
         delete ref;
      }
      else
         ref->setNumberOfCopies(numCopies);
   }
   return numCopies;
}
//end

//start id=libfind

RefItem* Library::findRefItem(QString isbn) {
   for(int i = 0; i < size(); ++i) {
      if(at(i)->getISBN().trimmed() == isbn.trimmed())
         return at(i);
   }
   return 0;
}


bool Library::isInList(QString isbn) {
   return findRefItem(isbn);
}

QString Library::toString(QString sep) const {
   QStringList reflst;
   for(int i = 0; i < size(); ++i)
      reflst << at(i)->toString();
   return reflst.join(sep);
}

QString Library::getItemString(QString isbn) {
   RefItem* ref(findRefItem(isbn));
   if(ref)
      return ref->toString();
   else
      return QString();
}
//end

