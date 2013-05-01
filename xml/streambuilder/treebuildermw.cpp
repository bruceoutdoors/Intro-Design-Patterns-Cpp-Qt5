#include <QtGui>
#include "treebuildermw.h"
#include "ui_treebuildermw.h"
#include "xmltreemodel.h"

TreeBuilderMW::TreeBuilderMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TreeBuilderMW),
    m_treeModel(0) {
    ui->setupUi(this);
    m_treeModel = new XmlTreeModel(this);

    ui->treeView->setModel(m_treeModel);
    connect (ui->treeView, SIGNAL(clicked(QModelIndex)),
             this, SLOT(clicked(QModelIndex)));
    open(":/samplefile.xml");
    statusBar();
}

TreeBuilderMW::~TreeBuilderMW() {
    delete ui;
}

void TreeBuilderMW::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TreeBuilderMW::on_actionOpen_File_triggered() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open XML file"), QDir::currentPath(), tr("*.xml"));
    if (!fn.isNull()) {
        open(fn);
    }
}
void TreeBuilderMW::open(QString fn) {
    if (m_treeModel != 0) {
        ui->treeView->setModel(0);
        delete m_treeModel;
    }
    m_treeModel = new XmlTreeModel(this);
    m_treeModel->open(fn);
    ui->treeView->setModel(m_treeModel);
    QFile f(fn);
    f.open(QIODevice::ReadOnly);
    QString content = f.readAll();
    ui->textEdit->setText(content);
}

void TreeBuilderMW::on_actionQuit_triggered() {
    qApp->quit();
}
//startid=gotoline
void TreeBuilderMW::gotoLine(unsigned int lineNumber) {
    const QTextBlock &block = ui->textEdit->document()->findBlockByNumber(lineNumber);
    QTextCursor cursor(block);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 0);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void TreeBuilderMW::clicked(QModelIndex idx) {   
    int lineNumber = idx.data(XmlTreeModel::LineStartRole).toInt();
    // maybe also highlight region from linestart to lineend?
    gotoLine(lineNumber);
}
//end
