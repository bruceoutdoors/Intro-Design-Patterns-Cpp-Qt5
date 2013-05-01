#include <QApplication>
#include "undomainwin.h"

int main(int argc, char** argv) {
    QApplication qapp(argc, argv);
    UndoMainWin um;
    um.show();
    return qapp.exec();
}
