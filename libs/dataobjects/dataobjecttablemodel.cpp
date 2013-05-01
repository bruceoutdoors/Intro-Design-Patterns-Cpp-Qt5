#include <QDebug>
#include <QStringList>
#include "dataobjecttablemodel.h"

//start id=extractHeaders
DataObjectTableModel::
DataObjectTableModel(DataObject* headerModel, QObject* parent) :
   QAbstractTableModel(parent) {
    if (headerModel != NULL) {
        extractHeaders(headerModel);
    }
}

int DataObjectTableModel::
fieldIndex(const QString& fieldName) const {
    return m_Headers.indexOf(fieldName);
}

void DataObjectTableModel::
extractHeaders(DataObject* hmodel) {
    m_Original = hmodel;
    QStringList props = hmodel->propertyNames();
    m_Headers.clear();
    foreach (QString prop, props) {
        if (prop == "objectName") continue;
        QMetaProperty mprop = m_Original->metaProperty(prop);
        m_isEditable << mprop.isWritable();
        m_Headers << prop;
    }
}
//end
DataObjectTableModel::~DataObjectTableModel() {

}

int DataObjectTableModel::
findRow(const QString& name) {
    // TODO: Make this a map lookup for better scalability?
    int rc = rowCount();
    for (int i=0; i<rc; ++i) {
        if (m_Data[i]->objectName() == name) {
            return i;
        }
    }
    return -1;
}

void DataObjectTableModel::
rowChanged(const QString& name) {
    int row = findRow(name);
    if (row == -1) return;
    QModelIndex ul = index(row, 0, QModelIndex());
    QModelIndex br = index(row, m_Headers.size(), QModelIndex());
    emit dataChanged(ul, br);
}

//start id=data
QVariant DataObjectTableModel::
data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    int row(index.row()), col(index.column());
    if (row >= rowCount()) return QVariant();
    QSharedPointer<DataObject> lineItem(m_Data.at(row));
    if (lineItem.isNull()) {
        qDebug() << "lineitem=0:" << index;
        return QVariant();
    }
    if (role == Qt::UserRole || role == Qt::ToolTipRole)
        return lineItem->objectName();
    else if (role == DisplayRole || role == EditRole) {
        return lineItem->property(m_Headers.at(col));
    } else
        return QVariant();
}


bool DataObjectTableModel::
setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == EditRole) {
        int row(index.row()), col(index.column());
        QSharedPointer<DataObject> lineItem(m_Data.at(row));
        lineItem->setProperty(m_Headers.at(col), value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
//end

//start id=header
QVariant DataObjectTableModel::
headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != DisplayRole)
         return QVariant();
    if (orientation == Qt::Vertical)
        return QVariant(section);
    if (m_Headers.size() ==0)
        return QVariant();
    if (section >= m_Headers.size()) return QVariant();
    return m_Headers.at(section);
}


int DataObjectTableModel::
rowCount(const QModelIndex&) const  {
    return m_Data.count();
}

int DataObjectTableModel::
columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_Headers.size();
}
//end


//start id=records
bool DataObjectTableModel::
insertRecord(QSharedPointer<DataObject> newRow, int position,
             const QModelIndex& parent) {
    if (position==-1) {
        position=rowCount()-1;
    }
    if (position < 0) position = 0;
    beginInsertRows(parent, position, position);
    m_Data.insert(position, newRow);
    connect(newRow.data(), SIGNAL(dataObjectChanged(QString)),
        this, SLOT(rowChanged(QString)));
    endInsertRows();
    return true;
}
//end
/*
const QSharedPointer<DataObject> DataObjectTableModel::
operator[](int rowNum) const {
    return m_Data.at(rowNum);
}

QSharedPointer<DataObject> DataObjectTableModel::
operator[](int rowNum)  {
    return m_Data.at(rowNum);
}
*/
//start id=abstract
ItemFlags DataObjectTableModel::
flags(const QModelIndex& index) const {
    if (!index.isValid())
        return ItemIsEnabled;
    if (m_isEditable[index.column()])
        return QAbstractItemModel::flags(index) | ItemIsEditable;
    else
        return QAbstractItemModel::flags(index);
}

void DataObjectTableModel::clear() {
    removeRows(0, rowCount(), index(0, 0));
//    reset();
}


bool DataObjectTableModel::
insertRows(int position, int rows, const QModelIndex& parent) {
    beginInsertRows(parent, position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        QSharedPointer<DataObject> dobj (m_Original->clone());
        connect(dobj.data(), SIGNAL(dataObjectChanged(QString)),
            this, SLOT(rowChanged(QString)));
        m_Data.insert(position, dobj);
    }
    endInsertRows();
    return true;
}

bool DataObjectTableModel::
removeRows(int pos, int rows, const QModelIndex& ) {
//  qDebug () << "RemoveRows p: " << pos << "rows:" << rows;
    if (pos + rows > m_Data.size() ) {
        qDebug() << " removerows invalid for size: "<< m_Data.size();
        return false;
    }
//  QModelIndex topLeft(index(pos, 0, parent));
    beginRemoveRows(QModelIndex(), pos, pos+rows-1);
    for (int row = 0; row < rows; ++row) {
       disconnect(m_Data[pos].data(), 0, this, 0);
//   qDebug() << "Removing: " << pos << m_Data[pos]->objectName();
       m_Data.removeAt(pos);
    }
    endRemoveRows();
//  QModelIndex bottomRight(index(pos + rows, columnCount(), parent));

//  emit dataChanged(topLeft, bottomRight);
    return true;
}
//end
//start
QStringList DataObjectTableModel::
toStringList() const {
//    const int EMPTYLEN(14);
    QStringList biglist;
    foreach(QSharedPointer<DataObject> doptr, m_Data) {
        QString linestr(doptr->toString());
//        if (linestr.length() > EMPTYLEN)
          biglist << linestr;
    }
    return biglist;
}

QString DataObjectTableModel::
toString() const {
    return toStringList().join("\n");
}
//end

