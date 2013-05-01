#include <QTextStream>
#include <QDebug>
#include "person.h"
#include <QDebug>

static QTextStream cout(stdout);
//start
void growBunch() {
    qDebug() << "First we create a bunch of objects." << endl;
    QObject bunch;
    bunch.setObjectName("A Stack Object");  /* A local stack object - not a pointer */
    /* other objects are created on the heap */
    Person* mike = new Person("Mike", &bunch);
    Person* carol = new Person("Carol", &bunch);
    new Person("Greg", mike);               /* We do not need
             to keep pointers to children, because we can
             reach them via object navigation. */
    new Person("Peter", mike);
    new Person("Bobby", mike);
    new Person("Marcia", carol);
    new Person("Jan", carol);
    new Person("Cindy", carol);
    new Person("Alice");                    /* Alice has no parent - memory leak? */
    qDebug() << "\nDisplay the list using QObject::dumpObjectTree()"
             << endl;
    bunch.dumpObjectTree();                 /* dumpObjectTree() output will appear on the
			       screen only if the Qt library has been
			       compiled with the debugging option turned on.*/
    cout << "\nReady to return from growBunch() -"
         << " Destroy all local stack objects." << endl;
}


int main(int , char**) {
   growBunch();
   cout << "We have now returned from growBunch()."
        <<  "\nWhat happened to Alice?" << endl;
   return 0;
}
//end
