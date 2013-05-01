#include <QTreeView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "ui_actiontableeditor.h"
#include "actiontableeditor.h"
#include "actioneditordialog.h"


ActionTableEditor::ActionTableEditor( QWidget* parent)
    :  QDialog(parent), m_ui(new Ui_ActionTableEditor) {
    m_ui->setupUi(this);
    populateTable();
}

ActionTableEditor::~ActionTableEditor() {
    delete m_ui;
}
//start id="populate"
QList<QStandardItem*> ActionTableEditor::
createActionRow(QAction* a) {
    QList<QStandardItem*> row;
    QStandardItem* actionItem = new QStandardItem(a->text());
    QStandardItem* shortcutItem = 
        new QStandardItem(a->shortcut().toString());                /* Duplicating data from 
        QAction to QStandardItem. */
    actionItem->setIcon(a->icon());                                 /* More duplicate data. */
          
    actionItem->setToolTip(a->toolTip());                           /* More duplicate data. */
    actionItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); /* Read-only model without 
        Qt::ItemIsEditable. */
    shortcutItem->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    shortcutItem->setIcon(a->icon());                               /* More duplicate data. */
    row << actionItem << shortcutItem;
    return row;
}

void ActionTableEditor::populateTable() {
    foreach (QWidget* w, qApp->topLevelWidgets())                   /* All top level widgets. */
        foreach (QAction* a, w->findChildren<QAction*>()) {         /* All QActions that 
           can be found. */            
            if (a->children().size() > 0) continue;                 /* Skip groups of actions. */
            if (a->text().size() > 0) m_actions << a;
        }

    int rows = m_actions.size();
    m_model = new QStandardItemModel(this);
    m_model->setColumnCount(2);
    m_model->setHeaderData(0, Qt::Horizontal, QString("Action"),
                           Qt::DisplayRole);
    m_model->setHeaderData(1, Qt::Horizontal, QString("Shortcut"),
                           Qt::DisplayRole);
    QHeaderView* hv = m_ui->m_tableView->horizontalHeader();
    m_ui->m_tableView->
       setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->m_tableView->
       setSelectionMode(QAbstractItemView::NoSelection);
    hv->setResizeMode(QHeaderView::ResizeToContents);
    hv->setStretchLastSection(true);
    m_ui->m_tableView->verticalHeader()->hide();
    for (int row=0; row < rows; ++row ) {
        m_model->appendRow(createActionRow(m_actions[row]));
    }
    m_ui->m_tableView->setModel(m_model);                           /* Connect the view to its model. */
}
//end
//start id=dialog
void ActionTableEditor::
on_m_tableView_activated(const QModelIndex& idx) {
    int row = idx.row();
    QAction* action = m_actions.at(row);
    ActionEditorDialog aed(action);
    int result = aed.exec();                        /* Pop up modal dialog for editing an action's shortcut. */
    if (result ==  QDialog::Accepted) {             /* This would be a good place to check for duplicate/ambiguous bindings. */
        action->setShortcut(aed.keySequence());     /* Skip the model and set the QAction property directly. */
        m_ui->m_tableView->reset();
    }
}
//end

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

