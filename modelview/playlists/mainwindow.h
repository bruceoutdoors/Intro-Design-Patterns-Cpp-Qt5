#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QSharedPointer>
#include <QSortFilterProxyModel>
#include "ui_mainwindow.h"
#include "metadatatablemodel.h"
class MetaData;
class SourceListModel;

/** Multiple playlists lab with clipboard and drag and drop*/

class MainWindow : public QMainWindow, private Ui::MainWindow {
    friend class PlayListView;
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    static MainWindow* instance();
    void closeEvent(QCloseEvent*);
protected:
    void changeEvent(QEvent* e);

private slots:

private:

    QSortFilterProxyModel* m_sfpm;
    MetaDataTableModel* m_currentModel;


private slots:
    void on_actionRefresh_triggered();
    void on_actionRemove_triggered();
    void on_actionPaste_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void on_sourceListView_clicked(QModelIndex index);
    void on_actionQuit_triggered();
    void on_lineEdit_textChanged(QString );
private:
    SourceListModel* m_sourceListModel;
    QList< QSharedPointer<MetaData> > m_clippedList;
};

#endif // MAINWINDOW_H

