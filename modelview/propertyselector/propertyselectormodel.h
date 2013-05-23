#ifndef PROPERTYSELECTORMODEL_H
#define PROPERTYSELECTORMODEL_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QPersistentModelIndex>
#include <QAbstractListModel>
#include "dataobject.h"

class PropertySelectorModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PropertySelectorModel(DataObject* hsrc, QObject* parent = 0);
    void initializePropertyNames();
    QStringList getAllPropertyNames() const;
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QPersistentModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);
    QStringList getSelectedPropertyNames() const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void updateSelects(QModelIndexList selects);
    void prepareShow();

signals:
    void readyRestore(QList<QPersistentModelIndex>);
    void readyCloseWindow(bool);

private:
    QList<QPersistentModelIndex> m_SelectedIndexes;
    DataObject* m_PropNameSource;
    QStringList m_PropertyNames;
};
//end



#endif // PROPERTYSELECTORMODEL_H
