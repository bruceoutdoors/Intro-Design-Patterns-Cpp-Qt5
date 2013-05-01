#include <QApplication>
#include "application.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    a.setApplicationName("Test Application");
    a.setOrganizationName("ics");
    a.setOrganizationDomain("com");
    ApplicationWindow mw; /* Create main window */
    mw.setWindowFilePath("Untitled Document" );
    mw.show();  /* Set to visible */
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec(); /* Enter into an event loop */
}
