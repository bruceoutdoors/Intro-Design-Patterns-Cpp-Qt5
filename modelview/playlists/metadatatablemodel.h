#ifndef METADATATABLEMODEL_H
#define METADATATABLEMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <QModelIndex>
#include <QStringList>
#include <QList>
#include <QVariant>

#include "metadata.h"

/** Maps QObject properties to columns in the table.
*/

class MetaDataTableModel : public QAbstractTableModel {
public:
    /** Proxy table model for a list of MetaData*.
        Manages the list of MetaData* as if they were children.
     */

    MetaDataTableModel(QList<QSharedPointer<MetaData> > list, QObject* parent=0);
    ~MetaDataTableModel();
    // Required overrides from QAbstractTableModel:
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, 
                       int role = Qt::DisplayRole) const;
    // bool hasChildren(const QModelIndex &) const {return false;}
    // Required overrides for editable table models:
    bool insertRows(int row, int count, const QModelIndex& parent=QModelIndex());
    bool removeRows(int row, int count, const QModelIndex& parent=QModelIndex());
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool setData(const QModelIndex& index, const QVariant& value, 
                 int role=Qt::EditRole);
    // Required overrides for encoding/decoding mime data from clipboard:
    QMimeData* mimeData(const QModelIndexList& indexes) const;
    Qt::DropActions supportedDropActions() const;
    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, 
                              int row, int column, const QModelIndex& parent);
    QStringList mimeTypes() const;
private:
    QList< QSharedPointer<MetaData> > m_list;
    QStringList m_columnProps;
    QStringList m_columnHeaders;
};

#endif        //  #ifndef METADATATABLEMODEL_H


