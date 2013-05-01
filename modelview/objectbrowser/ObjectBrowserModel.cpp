#include "ObjectBrowserModel.h"
#include <QApplication>
#include <QWidget>

ObjectBrowserModel::ObjectBrowserModel(QObject* root){
    rootItem = root;
}

int ObjectBrowserModel::
columnCount(const QModelIndex& /* parent */) const {
    return 3;
}

int ObjectBrowserModel::rowCount( const QModelIndex& parent ) const {
    return children(qObject(parent)).count();
}

QVariant ObjectBrowserModel::
data(const QModelIndex& index, int role) const{
    if ( !index.isValid() || role != Qt::DisplayRole )
        return QVariant();
    QObject* obj = qObject(index);
    return label( obj, index.column() );
}

QList<QObject*> ObjectBrowserModel::
children( QObject* parent ) const {
    QList<QObject*> result;
    if ( parent == 0 ) {
         result.append( rootItem );
    }
    else
        result = parent->children();
    qSort( result );
    return result;
}

QVariant ObjectBrowserModel::
headerData(const int section, const Qt::Orientation orient, 
           const int role) const {
    if ( orient != Qt::Horizontal || role != Qt::DisplayRole )
        return QAbstractItemModel::headerData( section, orient, role );

    switch ( section ) {
        case 0: return "Class Name";
        case 1: return "Object Name";
        case 2: return "Address";
    }
    return QVariant();
}

QString ObjectBrowserModel::
label(const QObject* obj, const int column) const {
    switch ( column ) {
        case 0: return obj->metaObject()->className();
        case 1: return obj->objectName();
        case 2: {
            QString str;
            str.sprintf("%p", obj);
            return str ;
        }
    
        default:
            return QString();
    }
}

//start id="indexparent"
QModelIndex ObjectBrowserModel::
index(int row, int col, const QModelIndex& parent) const {
    if ((row < 0) || (col < 0) || row >= rowCount() || 
        col >= columnCount()) return QModelIndex();
    return createIndex( row, col, qObject(parent) ); /* Store an internalPointer in the index. */
}

QModelIndex ObjectBrowserModel::parent( const QModelIndex& index ) const {
    if (!index.isValid()) return QModelIndex();
    QObject* obj = qObject(index)->parent();         /* qObject() returns the row child of this index but you want this index's parent QObject pointer which is stored in index.internalPointer(). */
    if ( obj == 0 )
        return QModelIndex();

    QObject* parent = obj->parent();
    int row = children( parent ).indexOf( obj );
    return createIndex( row, 0, parent );
}

QObject* ObjectBrowserModel::
qObject(const QModelIndex& index) const {            /* My index's internalPointer is my parent QObject pointer. I am the row() child of my parent. */
    if ( index.isValid() ) {
        QObject* parent = reinterpret_cast<QObject*>( index.internalPointer() );
        return children(parent)[index.row()];        /* This is me! */
    }
    return 0;                                        /* This is the root. */
}
//end
