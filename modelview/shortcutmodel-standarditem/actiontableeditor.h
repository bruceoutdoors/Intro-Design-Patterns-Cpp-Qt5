#ifndef ACTIONTABLEEDITOR_H
#define ACTIONTABLEEDITOR_H


#include <QDialog>
#include <QList>
#include <QModelIndex>
class QStandardItem;
class QAction;
class QStandardItemModel;
class Ui_ActionTableEditor;

/** ActionTableEditor Widget, for editing shortcuts in a table view.
   @author ezust
 */
//start
class ActionTableEditor : public QDialog {
    Q_OBJECT
public:
    ActionTableEditor(QWidget* parent = 0);
    ~ActionTableEditor();
protected slots:
    void on_m_tableView_activated(const QModelIndex& idx=QModelIndex());
    QList<QStandardItem*> createActionRow(QAction* a);
protected:
    void populateTable();
    void changeEvent(QEvent* e);
private:
    QList<QAction*> m_actions;
    QStandardItemModel* m_model;
    Ui_ActionTableEditor* m_ui;
};
//end



#endif        //  #ifndef ACTIONTABLEEDITOR_H
