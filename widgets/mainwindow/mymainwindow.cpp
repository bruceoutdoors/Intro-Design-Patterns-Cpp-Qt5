#include <QtGui>
#include <QDockWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include "mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget* parent) :QMainWindow(parent) {
    /* The main window is a stacked widget, inside a dock widget.
       This gives us the ability to dock and un-dock, resize, as well
       as change the contents (toggle, or animate) */
    m_StackedWidget = new QStackedWidget();
    m_TextEdit = new QTextEdit(m_StackedWidget);
    QDockWidget* mainDock = new QDockWidget("Text Editor");
    mainDock->setWidget(m_TextEdit);
    setCentralWidget(mainDock);
    QTextEdit* lw = new QTextEdit();
    m_DebugWindow = lw;
    QDockWidget* debugdock = new QDockWidget("Debug Window");
    debugdock->setWidget(m_DebugWindow);
    addDockWidget(Qt::BottomDockWidgetArea, debugdock);
    qDebug() << "This is a debug message" ;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();
    connect(m_TextEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
    setWindowTitle(tr("Application"));
}


void MyMainWindow::newFile() {
    if (maybeSave()) {
        m_TextEdit->clear();
        setCurrentFile("");
    }
}

void MyMainWindow::open() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MyMainWindow::save() {
    if (m_FileName.isEmpty()) {
        return saveAs();
    } else {
        saveFile(m_FileName);
        return true;
    }
}

bool MyMainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;
    if (QFile::exists(fileName)) {
	int ret = QMessageBox::warning(this, tr("Application"),
		tr("File %1 already exists.\n"
		"Do you want to overwrite it?")
		.arg(QDir::convertSeparators(fileName)),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No | QMessageBox::Escape);
        if (ret == QMessageBox::No)
            return true;
    }
    saveFile(fileName);
    return true;
}

void MyMainWindow::about() {
    QMessageBox::about(this, tr("About Application"),
           tr("The <b>Application</b> example demonstrates how to "
          "write modern GUI applications using Qt, with a menu bar, "
          "dock widgets, toolbars, and a status bar."));
}

void MyMainWindow::documentWasModified() {
    m_ModLabel->setText(tr("MOD"));
}
/* TODO - show how to get some of the standard icons from QApplication->style() */
//start id="action"
void MyMainWindow::createActions() {
    m_NewAction = new QAction(QIcon(":/icons/new.png"), tr("&New"), this);
    m_NewAction->setShortcut(tr("Ctrl+N"));
    m_NewAction->setStatusTip(tr("Create a new file"));
    connect(m_NewAction, SIGNAL(triggered()), this, SLOT(newFile()));

    m_OpenAction = new QAction(QIcon(":/icons/open.png"), tr("&Open..."), this);
    m_OpenAction->setShortcut(tr("Ctrl+O"));
    m_OpenAction->setStatusTip(tr("Open an existing file"));
    connect(m_OpenAction, SIGNAL(triggered()), this, SLOT(open()));
//end
    m_SaveAction = new QAction(QIcon(":/icons/save.png"), tr("&Save"), this);
    m_SaveAction->setShortcut(tr("Ctrl+S"));
    m_SaveAction->setStatusTip(tr("Save the document to disk"));
    connect(m_SaveAction, SIGNAL(triggered()), this, SLOT(save()));

    m_SaveAsAction = new QAction(tr("Save &As..."), this);
    m_SaveAsAction->setStatusTip(tr("Save the document under a new name"));
    connect(m_SaveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    m_ExitAction = new QAction(tr("E&xit"), this);
    m_ExitAction->setShortcut(tr("Ctrl+Q"));
    m_ExitAction->setStatusTip(tr("Exit the application"));
    connect(m_ExitAction, SIGNAL(triggered()), this, SLOT(close()));

    m_CutAction = new QAction(QIcon(":/icons/cut.png"), tr("Cu&t"), this);
    m_CutAction->setShortcut(tr("Ctrl+X"));
    m_CutAction->setStatusTip(tr("Cut the current selection's contents to the ""clipboard"));
    connect(m_CutAction, SIGNAL(triggered()), m_TextEdit, SLOT(cut()));

    m_CopyAction = new QAction(QIcon(":/icons/copy.png"), tr("&Copy"), this);
    m_CopyAction->setShortcut(tr("Ctrl+C"));
    m_CopyAction->setStatusTip(tr("Copy the current selection's contents to the ""clipboard"));
    connect(m_CopyAction, SIGNAL(triggered()), m_TextEdit, SLOT(copy()));

    m_PasteAction = new QAction(QIcon(":/icons/paste.png"), tr("&Paste"), this);
    m_PasteAction->setShortcut(tr("Ctrl+V"));
    m_PasteAction->setStatusTip(tr("Paste the clipboard's contents into the current ""selection"));
    connect(m_PasteAction, SIGNAL(triggered()), m_TextEdit, SLOT(paste()));

    m_AboutAction = new QAction(tr("&About"), this);
    m_AboutAction->setStatusTip(tr("Show the application's About box"));
    connect(m_AboutAction, SIGNAL(triggered()), this, SLOT(about()));

    m_AboutQtAction = new QAction(tr("About &Qt"), this);
    m_AboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(m_AboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
//start id="action"
void MyMainWindow::createFileMenu() {
    m_FileMenu = menuBar()->addMenu(tr("&File"));
    m_FileMenu->addAction(m_NewAction);
    m_FileMenu->addAction(m_OpenAction);
    m_FileMenu->addAction(m_SaveAction);
    m_FileMenu->addAction(m_SaveAsAction);
    m_FileMenu->addSeparator();
    m_FileMenu->addAction(m_ExitAction);
}

//end
void MyMainWindow::createMenus() {
    createFileMenu();
    createEditMenu();
    createHelpMenu();
}


void MyMainWindow::createEditMenu() {

    m_EditMenu = menuBar()->addMenu(tr("&Edit"));
    m_EditMenu->addAction(m_CutAction);
    m_EditMenu->addAction(m_CopyAction);
    m_EditMenu->addAction(m_PasteAction);
}

void MyMainWindow::createHelpMenu() {
    menuBar()->addSeparator();
    m_HelpMenu = menuBar()->addMenu(tr("&Help"));
    m_HelpMenu->addAction(m_AboutAction);
    m_HelpMenu->addAction(m_AboutQtAction);
}

void MyMainWindow::createToolBars() {
    m_FileToolBar = addToolBar(tr("File"));
    m_FileToolBar->addAction(m_NewAction);
    m_FileToolBar->addAction(m_OpenAction);
    m_FileToolBar->addAction(m_SaveAction);

    m_EditToolBar = addToolBar(tr("Edit"));
    m_EditToolBar->addAction(m_CutAction);
    m_EditToolBar->addAction(m_CopyAction);
    m_EditToolBar->addAction(m_PasteAction);
}

void MyMainWindow::createStatusBar() {
    m_ModLabel = new QLabel(tr(" MOD "));
    m_ModLabel->setAlignment(Qt::AlignHCenter);
    m_ModLabel->setMinimumSize(m_ModLabel->sizeHint());
    m_ModLabel->clear();

    statusBar()->addWidget(m_ModLabel, 0);
}

//start id="readsettings"
void MyMainWindow::readSettings() {
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    QByteArray state = settings.value("state", QByteArray())
                                                   .toByteArray();
    restoreState(state);
    resize(size);
    move(pos);
}
//end
//start id="writesettings"
void MyMainWindow::closeEvent(QCloseEvent* event) {
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


void MyMainWindow::writeSettings() {
    /* Save postion/size of main window */
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("state", saveState());
}
//end

bool MyMainWindow::maybeSave() {
    if (m_TextEdit->document()->isModified()) {
        int ret = QMessageBox::warning(this, tr("Application"),
		tr("The document has been modified.\n"
			"Do you want to save your changes?"),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MyMainWindow::loadFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
		tr("Cannot read file %1:\n%2.")
		.arg(fileName).arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    m_TextEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MyMainWindow::saveFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
		tr("Cannot write file %1:\n%2.")
		.arg(fileName)
		.arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_TextEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
}

void MyMainWindow::setCurrentFile(const QString& fileName) {
    m_FileName = fileName;
    m_ModLabel->clear();
    m_TextEdit->document()->setModified(false);

    if (m_FileName.isEmpty())
        setWindowTitle(tr("Application"));
    else
        setWindowTitle(tr("%1 - %2").arg(strippedName(m_FileName))
	.arg(tr("Application")));
}

QString MyMainWindow::strippedName(const QString& fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

QWidget* MyMainWindow::initialWidget() const {
    return m_StackedWidget->widget(0);
}

