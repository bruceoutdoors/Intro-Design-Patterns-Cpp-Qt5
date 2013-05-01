#include <QtGui>
#include "metadata.h"
#include "metadatatablemodel.h"
#include <QSharedPointer>


MetaDataTableModel::MetaDataTableModel(QList<QSharedPointer<MetaData> > list, 
                                 QObject* parent): QAbstractTableModel(parent) {
    m_list = list;
    m_columnProps << "TrackTitle" << "Artist" << "TrackTime" << "AlbumTitle" 
                  << "TrackNumber" << "Genre" << "Rating" ;
    m_columnHeaders << tr("title") << tr("artist") << tr("length")
        << tr("album") << tr("#") << tr("genre") << tr("rating");
}

MetaDataTableModel::~MetaDataTableModel() {
}

bool MetaDataTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    beginInsertRows(parent, row, row+count-1);
    for (int i=0; i<count; ++i) {
        m_list.insert(row+i, QSharedPointer<MetaData>());
    }
    endInsertRows();
    return true;
}

bool MetaDataTableModel::removeRows(int row, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, row, row + count - 1);
    for (int c=0; c<count; ++c) {
        m_list.removeAt(row);
    }
    endRemoveRows();
    return true;
}

int MetaDataTableModel::rowCount(const QModelIndex& parent) const {
    if (parent == QModelIndex()) return m_list.size();
    else return 0;
}

int MetaDataTableModel::columnCount(const QModelIndex& parent ) const {
    if (parent == QModelIndex()) return m_columnProps.size();
    else return 0;
}

QVariant MetaDataTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();
    // Without including EditRole there, the editors will not have initial values
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        int r(index.row()), c(index.column());
        if (r >= m_list.size()) return QVariant();
        if (c >= m_columnProps.size()) return QVariant();
        QSharedPointer<MetaData> p(m_list[r]);
        if (p.isNull()) return QVariant();
        QString propName = m_columnProps[c];
        return p->property(propName.toAscii());
    }
    if (role == Qt::UserRole) {
        QSharedPointer<MetaData> md (m_list[index.row()]);
        if (md.isNull()) return QVariant();
        quint64 encodedPointer = (quint64) md.data();
        return encodedPointer;
    }
    return QVariant();
}

QVariant MetaDataTableModel::headerData(int section, Qt::Orientation orientation, 
                                       int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section < m_columnHeaders.size())
            return m_columnHeaders[section];
    }
    return QVariant();
}


Qt::ItemFlags MetaDataTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsDropEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool MetaDataTableModel::setData(const QModelIndex& index,
    const QVariant &value, int role)  {
    if (!index.isValid()) return false;
    qDebug() << QString("setData(%1,%2,%3)").arg(index.row()).
            arg(m_columnProps.at(index.column())).arg(value.toString());
    if (role == Qt::UserRole) {
        quint64 decodedPointer = index.data(Qt::UserRole).value<quint64>();
        MetaData* md = reinterpret_cast<MetaData*>(decodedPointer);
        QSharedPointer<MetaData> sharedPointer(md);
        m_list.replace(index.row(), sharedPointer);
        emit dataChanged(index, index);
        return true;
    }
    if (role != Qt::EditRole) return false;
    int row(index.row()), col(index.column());
    QSharedPointer<MetaData> p = m_list.at(row);
    if (p.isNull()) return false;
    p->setProperty(m_columnProps.at(col).toAscii(), value);
    emit dataChanged(index, index);
    return true;
}

// Drag and drop operations


QMimeData* MetaDataTableModel::mimeData(const QModelIndexList& indexes) const {
    QMimeData* retval = new QMimeData();
    QSet<int> rows;
    QStringList encodedStrings;
    foreach (const QModelIndex& idx, indexes) {
        if (rows.contains(idx.row())) continue;
        rows << idx.row();
        quint64 pointer = idx.data(Qt::UserRole).value<quint64>();
        QString str = QString("%1").arg(pointer);
        encodedStrings << str;
    }
    if (encodedStrings.size() > 0)
        retval->setText(encodedStrings.join("\n"));
    return retval;
}

Qt::DropActions MetaDataTableModel::supportedDropActions() const {
    return Qt::CopyAction;
}

bool MetaDataTableModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
                                  int row, int col, const QModelIndex& parent) {
    Q_UNUSED(col);
    Q_UNUSED(parent);
    if (action == Qt::IgnoreAction) return true;
    if (!data->hasText()) return false;
    QString text = data->text();
    QStringList lines = text.split("\n");

    if ((row < 0 ) || row >= m_list.size()) {
        row = m_list.size();
    }
    else beginInsertRows(parent, row, row + lines.size() - 1);
    foreach (QString line, lines) {
        quint64 decodedPointer = line.toULongLong();
        MetaData* md = reinterpret_cast<MetaData*>(decodedPointer);
        QWeakPointer<MetaData> wp(md);
        QSharedPointer<MetaData> sharedPointer(wp);
        if ((row < 0 ) || row >= m_list.size()) {
            m_list.append(sharedPointer);
        }
        else {
            m_list.insert(row, sharedPointer);
        }
    }
    endInsertRows();
    reset();
    return true;
}

QStringList MetaDataTableModel::mimeTypes() const {
    return QStringList() << "text/plain" ;
}

