#ifndef XMLTREEMODEL_H
#define XMLTREEMODEL_H

/** A tree model for a QDomNode
 created: 2005/01/02 14:27
 filename:  XmlTreeModel.h
 authors:  Fanda Vacek (fanda.vacek@volny.cz)
           Alan Ezust (alan dot ezust at gmail dot com )
 Version: Qt4.0rc1 (2005/06/04)
 
*********************************************************************/

#include <QDomDocument>
#include <QAbstractItemModel>
#include <QFile>
#include <exception.h>
using namespace Qt;

/** Data model for XML Dom Nodes in a QTreeView.
*/

class XmlTreeModel : public QAbstractItemModel {
public:
    XmlTreeModel(QObject *parent = NULL)
            : QAbstractItemModel(parent) {}
    ~XmlTreeModel() { }

    /**
       opens, parses a file using DOM, and then
       represents it as a TreeModel.
       
       @param f - the file to open
    */
    bool setContent(QFile &f) throw(Exception);
    
    /**
       Wraps an XmlTreeModel around an existing Dom Tree.
       @param node  an already parsed XML tree
      */
    bool setContent(QDomNode node);
    
    /* The below methods are the callbacks overridden from the
       base class, to make this model as "active" as possible. 
     */
    
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    ItemFlags flags(const QModelIndex &index) const;    
    QModelIndex parent ( const QModelIndex & index ) const;
    int rowCount(const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    bool hasChildren( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data( const QModelIndex & index, int role = DisplayRole ) const;
    QVariant headerData( int section, Qt::Orientation o, int role = DisplayRole ) const;

    protected:
    QDomDocument doc;

protected:

    // Adaptor functions to go between the two APIs
    QDomNode indexToNode(QModelIndex ix) const;
    QModelIndex nodeToIndex(int row, int column, QDomNode node) const;

};

#endif        //  #ifndef XMLTREEMODEL_H

