#include <QtCore>
#include "dynoprops.h"

int main() {
   QTextStream cout(stdout);
   DynoProps d1, d2;
   d1.setObjectName("d1");
   d2.setObjectName("d2");
   d1.setSomeString("Washington");
   d1.setProperty("AcquiredProp", "StringValue");
   d2.setProperty("intProp", 42);
   d2.setProperty("realProp", 3.14159);
   d2.setProperty("dateProp", QDate(2012, 01, 04));
   cout << d1.propsInventory() << endl;
   cout << d2.propsInventory() << endl;
   cout << "\nNow we save both objects to a file, close the file,\n"
           "reopen the file, read the data from the file, and use it\n"
           "to create new DynoProps objects.\n" << endl;
   QFile file("file.dat");
   file.open(QIODevice::WriteOnly);
   QDataStream out(&file);
   out << d1 << d2;
   file.close();
   DynoProps nd1, nd2;
   file.open(QIODevice::ReadOnly);
   QDataStream in(&file);
   in >> nd1 >> nd2;
   file.close();
   cout << "Here are the property inventories for the new objects.\n";
   cout << nd1.propsInventory() << endl;
   cout << nd2.propsInventory() << endl;   
}
                                            
