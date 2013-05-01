#include "propertyselectorview.h"
#include "propertyselectormodel.h"
#include <QAbstractListModel>
#include <QWidget>
#include <QListView>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QObject>
#include <QSize>
#include <QDebug>
//start id=constructor
PropertySelectorView::
PropertySelectorView(QAbstractListModel* model, QWidget* parent) :
QMainWindow(parent) {
    m_ListView = new QListView(this);
    setCentralWidget(m_ListView);
    PropertySelectorModel* chdmodel(qobject_cast<PropertySelectorModel*>(model));
    m_ListView->setModel(chdmodel);
    m_ListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_ListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QToolBar* toolbar = new QToolBar("Actions", this);
    m_ActionGroup = new QActionGroup(this);
    m_ApplyAction = addChoice("Apply", "Apply Changes");
    m_CancelAction = addChoice("Cancel", "Cancel Changes"); 
    toolbar->addActions(m_ActionGroup->actions());
    QMainWindow::addToolBar(Qt::TopToolBarArea, toolbar);
    connect(m_CancelAction, SIGNAL(triggered(bool)), 
                     this, SLOT(closeWindow(bool)));
    connect(m_ApplyAction, SIGNAL(triggered(bool)), 
                     this, SLOT(sendSelects(bool)));
}
//end
/** After the user has selected headers, this method obtains a list of indexes
of the selected items and uses a signal to send that list to the model.
*/
//start id=selects
void PropertySelectorView::sendSelects(bool) {
    QItemSelectionModel* selectModel = m_ListView->selectionModel();
    QModelIndexList selects = selectModel->selectedIndexes();
    emit selectionsMade(selects);
}
//end

void PropertySelectorView::closeWindow(bool) {
    setVisible(false);
}

/** This method consists of factored out code for creating actions
*/
QAction* PropertySelectorView::addChoice(QString name, QString text) {
    QAction* retval = new QAction(text, this);
    retval->setObjectName(name);
    retval->setEnabled(true);
    m_ActionGroup->addAction(retval);
    return retval;
}

/** This slot is called prior to the restoration of visibility of the view. It
is invoked by a signal in the model which transmits the list of indexes of
selected items so that the most recently applied selects can be seen.
*/
void PropertySelectorView::restoreSelects(QList<QPersistentModelIndex> selects) {
    QItemSelectionModel* selectModel = m_ListView->selectionModel();
    foreach(QPersistentModelIndex indx, selects) 
        selectModel->select(indx, QItemSelectionModel::Select);
}

