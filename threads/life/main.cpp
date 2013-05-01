#include <QtGui>

#include "lifemainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Conway's Game of Life (QtConcurrent Version)");
    a.setOrganizationDomain("objectlearning.net");
    LifeMainWindow w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
