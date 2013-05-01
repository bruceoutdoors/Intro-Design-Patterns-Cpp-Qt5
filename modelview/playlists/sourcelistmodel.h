#ifndef SOURCELISTMODEL_H
#define SOURCELISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "metadatatablemodel.h"

/**
  Model for a list of playlists.
  */
class SourceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SourceListModel(QObject* parent=0);
    virtual ~SourceListModel();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    MetaDataTableModel* playList(int row) const;

    bool hasChildren(const QModelIndex &) const {return false;}

    // drag and drop operations just dispatch to the proper MetaDataTableModel.
    Qt::DropActions supportedDropActions() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);


private:
    QList<MetaDataTableModel*> m_playlists;

    // Methods for generating test data
    void populateSamples();
    MetaDataTableModel* randomModel(int i);
};

#endif // SOURCELISTMODEL_H
