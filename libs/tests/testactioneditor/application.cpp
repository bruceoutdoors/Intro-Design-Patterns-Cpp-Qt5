#include <QtWidgets>
#include "actiontableeditor.h"
#include "qobjectbrowser.h"
#include "application.h"

ApplicationWindow::ApplicationWindow(QWidget* parent)
    : QMainWindow(parent)
{


    setWindowModified(false);
    setObjectName(qApp->applicationName());
    printer = new QPrinter( QPrinter::HighResolution );

    QAction * fileNewAction;
    QAction * fileOpenAction;
    QAction * fileSaveAction, * fileSaveAsAction, * filePrintAction;
    QAction * fileCloseAction, * fileQuitAction;

    fileNewAction = new QAction( qApp->style()->standardIcon(QStyle::SP_FileDialogNewFolder),
                                 "&New", this);

    fileNewAction->setStatusTip("new...");
    fileNewAction->setShortcut(tr("Ctrl+N"));
    connect( fileNewAction, SIGNAL( triggered() ) , this,
             SLOT( newDoc() ) );

    fileOpenAction = new QAction( qApp->style()->standardIcon(QStyle::SP_DirOpenIcon),
                                  "&Open...", this);
    fileOpenAction->setStatusTip("open");
    fileOpenAction->setShortcut(tr("Ctrl+O"));

    connect( fileOpenAction, SIGNAL( triggered() ) , this, SLOT( choose() ) );

    const char * fileOpenText = "<p><img source=\"fileopen\"> "
                     "Click this button to open a <em>new file</em>. <br>"
                     "You can also select the <b>Open</b> command "
                     "from the <b>File</b> menu.</p>";

    fileOpenAction->setWhatsThis( fileOpenText );

    fileSaveAction = new QAction( qApp->style()->standardIcon(QStyle::SP_DialogSaveButton),
                                  "&Save", this);
    fileSaveAction->setShortcut(tr("Ctrl+S"));
    fileSaveAction->setStatusTip(tr("save file"));


    connect( fileSaveAction, SIGNAL( triggered() ) , this, SLOT( save() ) );

    const char * fileSaveText = "<p>Click this button to save the file you "
                     "are editing. You will be prompted for a file name.\n"
                     "You can also select the <b>Save</b> command "
                     "from the <b>File</b> menu.</p>";
    fileSaveAction->setWhatsThis( fileSaveText );

    fileSaveAsAction = new QAction( qApp->style()->standardIcon(QStyle::SP_DialogSaveButton),
                                    "Save &As...", this);
    fileSaveAsAction->setStatusTip("Save File As");

    connect( fileSaveAsAction, SIGNAL( triggered() ) , this,
             SLOT( saveAs() ) );
    fileSaveAsAction->setWhatsThis( fileSaveText );

    filePrintAction = new QAction( QIcon(":/fileprint.xpm"), "&Print...", this);
    filePrintAction->setShortcut(tr("Ctrl+p"));

    connect( filePrintAction, SIGNAL( triggered() ) , this,
             SLOT( print() ) );

    const char * filePrintText = "Click this button to print the file you "
                     "are editing.\n You can also select the Print "
                     "command from the File menu.";
    filePrintAction->setWhatsThis( filePrintText );

    fileCloseAction = new QAction( qApp->style()->standardIcon(QStyle::SP_DirClosedIcon), "&Close", this);
    fileCloseAction->setShortcut(tr("Ctrl+W"));
    fileCloseAction->setStatusTip("Close");
    fileCloseAction->setWhatsThis("Close File");

    connect( fileCloseAction, SIGNAL( triggered() ) , this,
             SLOT( close() ) );

    fileQuitAction = new QAction( qApp->style()->standardIcon(QStyle::SP_DialogCloseButton),"&Quit", this);
    fileQuitAction->setShortcut(tr("Ctrl+Q"));
    fileQuitAction->setWhatsThis("quit");
    fileQuitAction->setStatusTip("quit");
    fileQuitAction->setStatusTip(tr("Ctrl+Q"));
    connect( fileQuitAction, SIGNAL( triggered() ) , qApp,
             SLOT( closeAllWindows() ) );

    // populate a tool bar with some actions

    QToolBar * fileTools = new QToolBar("file operations" , this);
    fileTools->setWindowTitle("File Operations" );
    fileTools->addAction(fileOpenAction);
    fileTools->addAction(fileSaveAction);
    fileTools->addAction(filePrintAction);
    fileTools->addAction(QWhatsThis::createAction(this));

    // populate a menu with all actions

    QMenu* fileMenu = new QMenu("&File", this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(fileNewAction);
    fileMenu->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);
    fileMenu->addAction(fileSaveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(filePrintAction);
    fileMenu->addSeparator();
    fileMenu->addAction(fileCloseAction);
    fileMenu->addAction(fileQuitAction);

    menuBar()->addSeparator();

    QMenu *toolsMenu = new QMenu("&Tools", this);
    menuBar()->addMenu(toolsMenu);

    QAction *editShortcutsAction = new QAction(tr("&Edit Shortcuts"), this);
    editShortcutsAction->setShortcut(tr("Ctrl+Alt+S"));
    connect(editShortcutsAction, SIGNAL(triggered()), this, SLOT(editShortcuts()));
    toolsMenu->addAction(editShortcutsAction);

    QAction *objectBrowserAction = new QAction(tr("&Object Browser"), this);
    connect(objectBrowserAction, SIGNAL(triggered()), this, SLOT(objectBrowser()));
    toolsMenu->addAction(objectBrowserAction);

    // add a help menu

    QMenu * help = new QMenu( "&Help", this );
    menuBar()->addMenu(help);

    help->addAction( "&About", this, SLOT(about()), tr("F1"));
    help->addAction( "About &Qt", qApp, SLOT(aboutQt()) );
    help->addSeparator();
    help->addAction( "What's &This", this, SLOT(whatsThis()),
                      tr("Shift+F1"));

    // create and define the central widget

    textEdit = new QTextEdit( this);
    connect (textEdit, SIGNAL(textChanged()), this, SLOT(setWindowModified()));
    textEdit->setWindowTitle("editor" );
    textEdit->setFocus();
    setCentralWidget( textEdit );
    statusBar()->showMessage( "Ready", 2000 );
    ActionTableEditor::restoreShortcuts();

    resize( 450, 600 );
}


ApplicationWindow::~ApplicationWindow()
{
    delete printer;
}

void ApplicationWindow::whatsThis() {
    QWhatsThis::enterWhatsThisMode();
}

void ApplicationWindow::objectBrowser() {
    QObjectBrowser *browser=new QObjectBrowser();
    browser->showNormal();
}


void ApplicationWindow::newDoc()
{
    ApplicationWindow *ed = new ApplicationWindow;
    ed->show();
}

void ApplicationWindow::choose()
{
    QString fn = QFileDialog::getOpenFileName(this, "Choose File", QString::null, QString::null);
    if ( !fn.isEmpty() )
	load( fn );
    else
    statusBar()->showMessage( "Loading aborted", 2000 );
}


void ApplicationWindow::editShortcuts()
{
    ActionTableEditor aed(this);
    aed.exec();
}


void ApplicationWindow::load( const QString &fileName )
{
    QFile f( fileName );
    if ( !f.open( QIODevice::ReadOnly))	return;

    QTextStream ts( &f );
    textEdit->setText( ts.readAll() );
    setWindowFilePath(fileName );
    setWindowModified(false);
    statusBar()->showMessage( "Loaded document " + fileName, 2000 );
}


void ApplicationWindow::save()
{
    if ( filename.isEmpty() ) {
        saveAs();
        return;
    }

    QString text = textEdit->toPlainText();
    QFile f( filename );
    if ( !f.open( QIODevice::WriteOnly ) ) {
        statusBar()->showMessage( QString("Could not write to %1").arg(filename),
			      2000 );
        return;
    }

    QTextStream t( &f );
    t << text;
    f.close();

    setWindowModified( false );
    setWindowFilePath( filename );

    statusBar()->showMessage( QString( "File %1 saved" ).arg( filename ), 2000 );
}


void ApplicationWindow::saveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, "Save textfile" );
    if ( !fn.isEmpty() ) {
        filename = fn;
        save();
    } else {
        statusBar()->showMessage( "Saving aborted", 2000 );
    }
}


void ApplicationWindow::print()
{
    // TODO
}

void ApplicationWindow::closeEvent( QCloseEvent* ce )
{
    if ( !isWindowModified() ) {
        ce->accept();
        return;
    }

    switch( QMessageBox::information( this, qApp->applicationName(),
				      "The document has been changed since "
				      "the last save.",
				      "Save Now", "Cancel", "Leave Anyway",
				      0, 1 ) ) {
    case 0:
        save();
        ce->accept();
        break;
    case 1:
    default: // just for sanity
        ce->ignore();
        break;
    case 2:
        ce->accept();
        break;
    }
}


void ApplicationWindow::about()
{
    QMessageBox::about( this, qApp->applicationName(),
			"This example demonstrates simple use of "
			"QMainWindow,\nQMenuBar and QToolBar.");
}


