

#include <QtGui>
#include "primeserver.h"
#include "primegui.h"

int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    PrimeGUI gui;
    while (gui.exec() != QDialog::Rejected) {}
    return 0;


}
