#include <QApplication>
#include "mainwindow.h"
#include "starrating.h"


int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("playlists");
    app.setOrganizationName("ics.com");
    qRegisterMetaType<StarRating>("StarRating");

    MainWindow mw;
    mw.show();
    return app.exec();
}
