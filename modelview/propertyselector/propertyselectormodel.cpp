#include "propertyselectormodel.h"
#include <dataobject.h>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <QAction>

//start id=pvoverrides
PropertySelectorModel::PropertySelectorModel(DataObject* hsrc, QObject* parent) :
QAbstractListModel(parent), m_PropNameSource(hsrc) {
    initializePropertyNames();
}

void PropertySelectorModel::initializePropertyNames() {
    m_PropertyNames = m_PropNameSource->propertyNames();
}

QStringList PropertySelectorModel::getAllPropertyNames() const {
    return m_PropertyNames;
}

int PropertySelectorModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_PropertyNames.count();
}

QVariant PropertySelectorModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        return m_PropertyNames.at(index.row());
    else
        return QVariant();
}

//end

//start id=setData
bool PropertySelectorModel::setData(const QModelIndex &index, const QVariant &value,
                                    int role) {
    if (index.isValid() && role == EditRole) {
        m_PropertyNames.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

ItemFlags PropertySelectorModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return ItemIsEnabled;
    return QAbstractItemModel::flags(index) | ItemIsEditable;
}
//end

bool PropertySelectorModel::insertRows(int position, int rows,
                                       const QModelIndex &parent) {
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        m_PropertyNames.insert(position, "");
    }
    endInsertRows();
    return true;
}


bool PropertySelectorModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);
    emit beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        m_PropertyNames.removeAt(position);
    }
    emit endRemoveRows();
    return true;
}
//start id=getselects
QStringList PropertySelectorModel::getSelectedPropertyNames() const {
    QStringList selects;
    foreach (const QPersistentModelIndex& indx, m_SelectedIndexes)
      if (indx.isValid())
          selects << data(indx).toString();
    return selects;
}
//end
QVariant PropertySelectorModel::headerData(int section, Qt::Orientation orientation,
        int role) const {
    if (role != DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

/** This slot receives a list of indexes of selected items by means of a signal
emitted by the view. It uses tht list to update its own list of selected
indexes and then emits a signal that lets the view know that it can close.
*/
//start id=slots
void PropertySelectorModel::updateSelects(QModelIndexList selects) {
    m_SelectedIndexes.clear();
    QPersistentModelIndex pindx;
    foreach(const QModelIndex &indx, selects) {
        pindx = indx;
        m_SelectedIndexes << indx;
    }
    emit readyCloseWindow(true);
}

void PropertySelectorModel::prepareShow() {
    emit readyRestore(m_SelectedIndexes);
}
//end

