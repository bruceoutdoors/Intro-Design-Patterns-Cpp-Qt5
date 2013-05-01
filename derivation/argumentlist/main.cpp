#include <QString>
#include <QDebug>
#include "argumentlist.h" 

void processFile(QString filename, bool verbose) {
   if (verbose)
      qDebug() << QString("Do something chatty with %1.")
                         .arg(filename);
   else
      qDebug() << filename;
}

void runTestOnly(QStringList & listOfFiles, bool verbose) {
   foreach (const QString &current, listOfFiles) { 
      processFile(current, verbose);
   }
}

int main( int argc, char * argv[] ) {
   ArgumentList al(argc, argv);       /* Instantiate the ArgumentList with command line args. */
   QString appname = al.takeFirst();  /* Inherited from QStringList - first item in the list is the name of the executable. */
   qDebug() << "Running " << appname;
   bool verbose = al.getSwitch("-v");
   bool testing = al.getSwitch("-t"); /* Now all switches have been removed from the list. Only filenames remain.*/
   if (testing) {
      runTestOnly(al, verbose);       /* ArgumentList can be used in place of QStringList. */
      return 0;
   } else {
      qDebug() << "This Is Not A Test";
   }
}

