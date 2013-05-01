
#include <QtGui>
#include "testmetadata.h"

int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    TestMetaData tmd;
    tmd.show();
    return app.exec();
}
