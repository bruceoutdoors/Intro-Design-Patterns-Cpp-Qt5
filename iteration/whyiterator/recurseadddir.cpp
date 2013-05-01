#include <QtCore>

void addMp3File(QString path) {
   static QTextStream cout(stdout);
   cout << path << endl;
}

//start
/** Searches for all Mp3 files in a directory
   tree and does "something" to them. 
   @param d directory to search
   @param recursive if true, drill down to subdirectories
   @param symlinks if true, follow symlinks 
*/
void recurseAddDir(QDir d, bool recursive=true, bool symlinks=false ) {
    d.setSorting( QDir::Name );
    QDir::Filters df = QDir::Files | QDir::NoDotAndDotDot;
    if (recursive) df |= QDir::Dirs;
    if (not symlinks) df |= QDir::NoSymLinks;
    QStringList qsl = d.entryList(df, QDir::Name | QDir::DirsFirst);
    foreach (const QString &entry, qsl) {
        QFileInfo finfo(d, entry);
        if ( finfo.isDir() ) {
            QDir sd(finfo.absoluteFilePath());
            recurseAddDir(sd);
        } else {
            if (finfo.completeSuffix()=="mp3")
                addMp3File(finfo.absoluteFilePath()); /* Nonreusable part */
        }
    }
}
//end

int main (int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QDir dir = QDir::current();
    if (app.arguments().size() > 1) {
        dir = app.arguments()[1];
    }
    recurseAddDir(dir); 
}
