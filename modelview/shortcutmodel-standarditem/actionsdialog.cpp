#include <QAction>
#include <QLayout>
#include <QLayout>
#include <QPushButton>
#include <QString>
#include <QTableView>
#include <QHeaderView>


#include "actionsdialog.h"

ActionsDialog::ActionsDialog(const QList<QAction*>& actions, 
                             QWidget* parent)  : QWidget(parent) {
    m_actionsTable = new QTableWidget(actions.count(), 2, this);
    m_actionsTable->horizontalHeader()->setLabel(0, tr("Description"));
    m_actionsTable->horizontalHeader()->setLabel(1, tr("Shortcut"));
    m_actionsTable->verticalHeader()->hide();
    m_actionsTable->setLeftMargin(0);
    m_actionsTable->setColumnReadOnly(0, true);
    int row = 0;
    foreach (const QAction* action, actions) {
        m_actionsTable->setText(row, 0, action->text());
        m_actionsTable->setText(row, 1, QString(action->accel()));
        m_actionsList.append(action);
        ++row;
    }

    connect(actionsTable, SIGNAL(currentChanged(int, int)),  this, SLOT(recordAction(int, int)));
    connect(actionsTable, SIGNAL(valueChanged(int, int)),
            this, SLOT(validateAction(int, int)));

    setWindowTitle(tr("Edit Actions"));
    setObjectName("Action Editor");
}

void ActionsDialog::accept() {
    for (int row = 0; row < (int)actionsList.size(); ++row) {
        QAction *action = actionsList[row];
        action->setAccel(QKeySequence(actionsTable->text(row, 1)));
    }
    QDialog::accept();
}

void ActionsDialog::recordAction(int row, int column) {
    oldAccelText = actionsTable->item(row, column)->text();
}

void ActionsDialog::validateAction(int row, int column) {
    QTableItem *item = actionsTable->item(row, column);
    QString accelText = QString(QKeySequence(item->text()));
    if (accelText.isEmpty() && !item->text().isEmpty())
        item->setText(oldAccelText);
    else
        item->setText(accelText);
}
