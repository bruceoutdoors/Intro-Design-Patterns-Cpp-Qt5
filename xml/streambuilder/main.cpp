#include <QApplication>
#include "treebuildermw.h"

int main (int argc, char* argv[]) {
    QApplication app(argc, argv);  
    TreeBuilderMW tb;
    tb.show();
    return app.exec();
}
