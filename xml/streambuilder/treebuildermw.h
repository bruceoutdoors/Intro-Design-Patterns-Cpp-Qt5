#ifndef TREEBUILDERMW_H
#define TREEBUILDERMW_H

#include <QMainWindow>

#include <QTreeView>
class XmlTreeModel;
namespace Ui {
    class TreeBuilderMW;
}

class TreeBuilderMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit TreeBuilderMW(QWidget *parent = 0);
    ~TreeBuilderMW();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_actionOpen_File_triggered();
    void open(QString fileName);
    void on_actionQuit_triggered();
    void clicked(QModelIndex idx);
    void gotoLine(unsigned int lineNumber);

private:
    Ui::TreeBuilderMW *ui;
    XmlTreeModel*m_treeModel;

};

#endif // TREEBUILDERMW_H
