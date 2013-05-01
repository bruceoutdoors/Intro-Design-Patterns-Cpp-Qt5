#include "logtail.h"
#include <QtGui>

//start id=constructor
LogTail::LogTail(QString fn) {
    connect (this, SIGNAL(readyReadStandardOutput()), 
        this, SLOT(logOutput()));       /* When there is input ready, call this slot.*/
    QStringList argv;
     
    argv << "-f" << fn;                 /* tail -f filename */ 
    start("tail", argv);                /* Returns immediately, and now there is a child process running, "attached" 
    to this process. When this process exits, the child tail process will also terminate. */
}
LogTail::~LogTail() {
    terminate();                        /* Attempts to terminate this process. */
}
//end

//start id=logOutput
// tail sends its output to stdout.
void LogTail::logOutput() {             /* Slot called whenever there is input to read. */
    QByteArray bytes = readAllStandardOutput();
    QStringList lines = QString(bytes).split("\n");
    foreach (QString line, lines) {
        emit logString(line); 
    }
}
//end
//start id=main
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    QStringList al = app.arguments(); 
    QTextEdit textEdit;
    textEdit.setWindowTitle("Debug");
    textEdit.setWindowTitle("logtail demo");
    QString filename;
    if (al.size() > 1) filename = al[1];
    LogTail tail(filename);             /* Create object, starts process too. */
    tail.connect (&tail, SIGNAL(logString(const QString&)),
        &textEdit, SLOT(append(const QString&)));
    textEdit.show();
    return app.exec();
}
//end

