
#include "person.h"
#include <QList>
#include <QDebug>

//start id=showtree
void showTree(QObject* theparent) {

    QObjectList kids = theparent->children();

    QListIterator<QObject*> itr (kids); /* read-only java-style iteration */
    while (itr.hasNext()) {  /* Java-Style iterators point between elements.
                 The first call to next() returns the first element 
                 and advances the iterator */
        QObject* ptr = itr.next();
        qDebug() << QString("Brady member: %1 - Parent: %2")
               .arg(ptr->objectName())
               .arg(ptr->parent()->objectName());
        showTree(ptr);
    }
}
//end

//start id=main
int main(int , char**) {
    qDebug() << "First we create a bunch of objects.";
    
    
    Person bunch(0, "A Stack Object"); /* not a pointer */ 
    
    /* other objects are created on the heap */        
    Person* mike = new Person(&bunch, "Mike"); 
    Person* carol = new Person(&bunch, "Carol");


    new Person(mike, "Greg"); /* The children - we do not need 
             to remember pointers to them, since we can
             reach them via object navigation. */
    new Person(mike, "Peter");
    new Person(mike, "Bobby");

    new Person(carol, "Marcia");
    new Person(carol, "Jan");
    new Person(carol, "Cindy");
    new Person(0, "Alice");  /* Alice has no parent - memory leak? */
    
    qDebug() << "\ndisplay the list using QObject::dumpObjectTree()";
    bunch.dumpObjectTree();
    qDebug() << "\nProgram finished - destroy all objects.";
    return 0;
}
//end

