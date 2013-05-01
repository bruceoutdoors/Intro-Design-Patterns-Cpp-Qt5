#include <QTableView>
#include <QMenu>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QApplication>
#include <QSettings>
#include "ui_actiontableeditor.h"
#include "actiontablemodel.h"
#include "actiontableeditor.h"
#include "actioneditordialog.h"

//start id="setup"
ActionTableEditor::ActionTableEditor(QWidget* parent)
    :  QDialog(parent), m_ui(new Ui::ActionTableEditor) {
    // Designer UI class initialization
    m_ui->setupUi(this);
    m_model = new ActionTableModel(allActions(), this);
    setupSortFilter();
}

ActionTableEditor::
ActionTableEditor(QList<QAction*> actions, QWidget* parent) :
  QDialog(parent) {
    m_ui->setupUi(this);
    m_model = new ActionTableModel(actions, this);
    setupSortFilter();
}

QList<QAction*> ActionTableEditor::allActions() {
    QList<QAction*> actions;

    foreach (QAction* a, qApp->findChildren<QAction*>()) {
        if (a->children().size() > 0) continue;
        if (a->text().size() > 0) actions << a;
    }
    foreach (QWidget* w, qApp->topLevelWidgets())
        foreach (QAction* a, w->findChildren<QAction*>()) {
            // skip menus
            if (qobject_cast<QMenu*>(a->parent()) != 0) continue;
            if (a->text().size() > 0) actions << a;
        }
    return actions;
}
//start id=dialog
void ActionTableEditor::
on_m_tableView_activated(const QModelIndex& idx) {
    int row = idx.row();
    QAction* action = m_model->action(row);
    ActionEditorDialog aed(action);

    int result = aed.exec();
    if (result ==  QDialog::Accepted) {
        QKeySequence ks = aed.keySequence();
        m_model->setData(idx, ks.toString());
        m_changedActions << action;
    }
}
//end
//start id=settings
void ActionTableEditor::accept() {
    QSettings s;
    s.beginGroup("shortcut");
    foreach (QAction* act, m_changedActions) {
        s.setValue(act->text(), act->shortcut() );
    }
    s.endGroup();
    QDialog::accept();
}
//end
void ActionTableEditor::restoreShortcuts(QList<QAction*> actions) {
    QSettings s;
    s.beginGroup("shortcut");
    foreach (QAction* act, actions) {
        QVariant v = s.value(act->text(), QVariant());
        if (!v.isNull()) {
            QKeySequence ks = v.value<QKeySequence>();
            act->setShortcut(ks);
        }
    }
    s.endGroup();
}
//start id="sortfilter"
void ActionTableEditor::setupSortFilter() {
    m_sortFilterProxy = new QSortFilterProxyModel(this);
    m_sortFilterProxy->setSourceModel(m_model);       /* SortFilterProxy source model set to ActionTableModel. */
    m_ui->m_tableView->setModel(m_sortFilterProxy);   /* Table view model set to proxy model instead of ActionTableModel. */    
    m_sortFilterProxy->setFilterKeyColumn(-1);        /* Filter on all fields. */

}
void ActionTableEditor::on_m_filterField_textChanged  /* Auto-connected slot. */  
    (const QString& newText) { 
    m_sortFilterProxy->setFilterFixedString(newText); /* Change the filter string. */
}
//end
ActionTableEditor::~ActionTableEditor() {
    delete m_ui; /* the other pointer members are QObject with this as parent */
}

void ActionTableEditor::changeEvent(QEvent* e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


