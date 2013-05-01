#include <QDebug>
#include <qstd.h>
using namespace qstd;

int main (int argc, char** argv) {
    QString str;

    for (int i=0; i<3; ++i) {
        cout <<  "Here is a prompt for an input line: " << flush;
        cin.skipWhiteSpace();
        str = cin.readLine();
        cout << "you typed: " << str << endl;
    }
    return 0;
}
