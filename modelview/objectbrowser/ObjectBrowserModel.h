#ifndef OBJECTBROWSERMODEL_H
#define OBJECTBROWSERMODEL_H
//start
#include <QAbstractItemModel>
/** An example tree model that lets you inspect QObjects,
   children and properties */
class ObjectBrowserModel :public QAbstractItemModel {
 public:
    explicit ObjectBrowserModel (QObject* rootObject);
    int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex& index, 
                    int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation, 
                        int role = Qt::DisplayRole) const;
    QModelIndex index ( int row, int column, 
                        const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent ( const QModelIndex& index ) const;

 protected:
    QList<QObject*> children( QObject* parent ) const;
    QString label( const QObject* widget, int column ) const;
    QObject* qObject( const QModelIndex& ) const;
 private:
    QObject *rootItem;
};
//end
#endif /* OBJECTBROWSERMODEL_H */

