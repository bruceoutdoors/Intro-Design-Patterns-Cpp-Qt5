
/** $Id: qstd.cpp 1108 2010-05-26 21:56:39Z sae $ */
//start id=namespace
#include "qstd.h"

/* QTextStreams look a lot like iostreams,
we just have to point them to the right place. */

//start id=streamdefs
QTextStream qstd::cout(stdout, QIODevice::WriteOnly);
QTextStream qstd::cin(stdin, QIODevice::ReadOnly);
QTextStream qstd::cerr(stderr, QIODevice::WriteOnly);

/* Namespace members are like static class members */
bool qstd::yes(QString question) {
    QString ans;
    cout << QString(" %1 [y/n]? ").arg(question);
    cout.flush();
    ans = cin.readLine();
    return (ans.startsWith("Y", Qt::CaseInsensitive));
}
//end

bool qstd::more(QString s) {
    return yes(QString("Another %1").arg(s));
}


int qstd::promptInt(int base /* =10 */) { /* Usage: int n = promptInt(); */
    QString numstr;
    int result;
    bool ok;
    cout << ": " << flush;
    while (1) {
        numstr = cin.readLine();
        result = numstr.toInt(&ok, base);
        if (!ok) {
            cout << "Invalid number. Try again: ";
            cout.flush();
        }
        else
            return result;
    }
}


double qstd::promptDouble() { /* Usage: double d = promptDouble(); */
    QString numstr;
    double result;
    bool ok;
    while (1) {
        numstr = cin.readLine();
        result = numstr.toDouble(&ok);
        if (!ok) {
            cout << "Invalid number. Try again: ";
            cout.flush();
        }
        else
            return result;
    }
}


void qstd::promptOutputFile(QFile& outfile) {
    QString filename;
    while (1) {
        cout << "Please enter the file name for saving this data: ";
        cout.flush();
        filename = cin.readLine();
        outfile.setFileName(filename);
        if (!outfile.exists()) {
            break;
        }
        if (qstd::yes("File already exists ... Ok to overwrite"))
            break;
    }
    outfile.open(QIODevice::WriteOnly);
    cout << filename << " open for writing ..." << endl;
}


void qstd::promptInputFile(QFile& infile) {
    QString filename;
    while (1) {
        cout << "Name of the file to be read:  ";
        cout.flush();
        filename = cin.readLine();
        infile.setFileName(filename);
        if (infile.exists()) {
           infile.open(QIODevice::ReadOnly);
           break;
        }
        cout << "File does not exist ... Please try again." << endl;
    }
    cout << infile.fileName() << " open for reading ...\n" << endl;
}


