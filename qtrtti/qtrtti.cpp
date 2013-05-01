#include <QApplication>
#include <QScrollBar>
#include <QWidget>
#include <QAbstractSlider>
#include <QListView>
#include <QString>
#include <QTextStream>

//start id=qobjectcast
int main( int argc, char ** argv ) {
    QApplication a(argc, argv);
    QTextStream cout(stdout);
    QScrollBar s;    /* an object derived from QWidget and QAbstractSlider. */
    QWidget* w = &s; /* No typecast required to more general type. */  

    cout << "We are testing a base class pointer that has "
         << "the address of a QScrollBar\n"
         << "First, we use qobject_cast to investigate." << endl;
    QScrollBar* ptr1 = qobject_cast<QScrollBar*>(w);
    if (ptr1)  cout << "Yes, it is ";
    else  cout << "No, it is not ";
    cout << "a QScrollBar!" << endl;
    
    QAbstractSlider* ptr2 = qobject_cast<QAbstractSlider*>(w);
    if (ptr2)  cout << "Yes, it is ";
    else  cout << "No, it is not ";
    cout << "a QAbstractSlider!" << endl;
    
    QListView* ptr3 = qobject_cast<QListView*>(w);
    if (ptr3)  cout << "Yes, it is ";
    else  cout << "No is is not ";
    cout << "a QListView!" << endl;
   
    
//    QString* ptr4 = qobject_cast<QString*>(w); 
    /* qobject_cast
    only operates on QObjects which were processed by moc, so this
    would be a compiler error. */

//end
//start id=inherits
//  QWidget* w = &s;            /* A pointer to some widget */
    
    if (w->inherits("QAbstractSlider"))  cout << "Yes, it is ";
    else cout << "No, it is not";
    cout << "a QAbstractSlider" << endl;
    
    if (w->inherits("QListView")) cout << "Yes, it is ";
    else  cout << "No, it is not ";
    cout << "a QListView" << endl; 

    return 0;
}
//end

    
