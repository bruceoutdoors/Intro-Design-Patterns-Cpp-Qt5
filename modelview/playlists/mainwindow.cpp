#include <QtGui>

#include "playlistview.h"
#include "metadata.h"
#include "mainwindow.h"
#include "stardelegate.h"
#include "sourcelistmodel.h"

static MainWindow* singleton = 0;

MainWindow* MainWindow::instance() {
    return singleton;
}

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    singleton = this;
    setupUi(this);
    clearFilterButton->setIcon(QIcon(":/icons/edit-clear.png"));
    m_currentModel = 0;
    m_sourceListModel = new SourceListModel(this);
    sourceListView->setModel(m_sourceListModel);
    actionAboutQt->setIcon(QPixmap(QLatin1String(
           ":/trolltech/qmessagebox/images/qtlogo-64.png")));
    m_sfpm = new QSortFilterProxyModel(this);
    m_sfpm->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_sfpm->setFilterKeyColumn(-1);
    playListView->setItemDelegate(new StarDelegate());
    playListView->setModel(m_sfpm);
    QSettings s;
    if (s.contains("geometry")) {
        QRect rect = qVariantValue<QRect>(s.value("geometry"));
        setGeometry(rect);
    }
}


void MainWindow::changeEvent(QEvent* e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::on_lineEdit_textChanged(QString text) {
    m_sfpm->setFilterFixedString(text);
}

void MainWindow::on_actionQuit_triggered() {
    QSettings s;
    s.setValue("geometry", geometry());
    qApp->quit();
}

void MainWindow::on_sourceListView_clicked(QModelIndex index) {
    m_currentModel = m_sourceListModel->playList(index.row());
    m_sfpm->setSourceModel(m_currentModel);
    playListView->reset();
    setWindowFilePath(m_currentModel->objectName());
}

void MainWindow::closeEvent(QCloseEvent* evt) {
    on_actionQuit_triggered();
    QMainWindow::closeEvent(evt);
}

void MainWindow::on_actionAboutQt_triggered() {
    qApp->aboutQt();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::information(this, tr("About %1").arg(qApp->applicationName()), 
                             tr("Model-View detail, lab 3"));
}

void MainWindow::on_actionCut_triggered() {
    on_actionCopy_triggered();
    on_actionRemove_triggered();
}

void MainWindow::on_actionCopy_triggered() {
    QItemSelectionModel* smodel = playListView->selectionModel();
    QModelIndexList qmil = smodel->selectedRows();
    if (qmil.size() == 0) return;
    QMimeData* md = playListView->model()->mimeData(qmil);
    m_clippedList.clear();
    foreach (QModelIndex idx, qmil) {
        QVariant data = idx.data(Qt::UserRole);
        qlonglong qll = data.toLongLong();
        MetaData* md = reinterpret_cast<MetaData*>(qll);
        QWeakPointer<MetaData> wp(md);
        QSharedPointer<MetaData> sp(wp);
        m_clippedList << sp;
    }
    qApp->clipboard()->setMimeData(md);
}

void MainWindow::on_actionPaste_triggered() {
    const QMimeData* md = qApp->clipboard()->mimeData();
    if (md != 0) {
        //int rc = model()->rowCount();
        QModelIndex idx = playListView->currentIndex();
        if (!idx.isValid()) return;
        int row = idx.row();
        playListView->model()->dropMimeData(md, Qt::CopyAction, row, 0, 
                                            QModelIndex());
    }
}

void MainWindow::on_actionRemove_triggered() {
    QAbstractItemModel* model= playListView->model();
    QModelIndexList mil = playListView->selectionModel()->selectedRows();
    while (!mil.isEmpty()) {
        QModelIndex idx = mil.takeLast();
        qDebug() << "removing: " << idx.row();
        model->removeRow(idx.row(), QModelIndex());
    }
}

void MainWindow::on_actionRefresh_triggered() {
    playListView->reset();
}

