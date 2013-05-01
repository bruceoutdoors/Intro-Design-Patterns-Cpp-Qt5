/********************************************************************
 created: 2005/01/02 14:27
 filename:  XmlTreeModel.cpp (based on fqxmltreemodel)
 authors:  Fanda Vacek (fanda.vacek@volny.cz)
           alan ezust (alan dot ezust at gmail dot com )
*********************************************************************/

#include <QIcon>
#include <QApplication>
#include <QStyle>
#include <QDebug>
#include "exception.h"

#include "xmltreemodel.h"

#define ASCII toAscii().data()

//=============================================
//                XmlTreeModel
//=============================================

bool XmlTreeModel::setContent(QDomNode node) {
    doc= node.ownerDocument();
    return true;
}

bool XmlTreeModel::setContent(QFile &f) throw(Exception) {
    if (!f.open(QIODevice::ReadOnly)) {
        QString s = QString("ERROR open file '%1'").arg(f.fileName());
        qDebug(s.ASCII);
        QString message = QString("XmlTreeModel::setContent(QFile &f):%1").arg(s);
        throw Exception(message);
    }
    if (!doc.setContent(&f)) {
        QString message = QString("ERROR parse file '%s'").arg(f.fileName());

        throw Exception(message);
    }
    return true;
}

class ImplDomNode : public QDomNode {
    protected:
    friend class XmlTreeModel;
    void* getImpl() const {
        return impl;
    }
    ImplDomNode(const QDomNode& nd) : QDomNode(nd) {}
    ImplDomNode(void* impl) : QDomNode((QDomNodePrivate*)impl) {}
};


QDomNode XmlTreeModel::indexToNode(QModelIndex ix) const {
    QDomNode ret = QDomNode();
    if (!ix.internalPointer())
        return ret;
    ImplDomNode node(ix.internalPointer());
    return node;
}


QModelIndex XmlTreeModel::nodeToIndex(int row, int column, QDomNode node) const {
    
    QModelIndex ret;
    if (node.isNull())
        return ret;
    ImplDomNode idn(node);    
    return createIndex(row, column, idn.getImpl());
}

QModelIndex XmlTreeModel::index(int row, int column, const QModelIndex &parent) const {

    QModelIndex ret = QModelIndex();
    do {
        QDomNode nd = indexToNode(parent);

        // If we are out of range, start back at the top
        if (nd.isNull()) {
            nd = doc;
        }

        int count = nd.childNodes().count();
        if (row < 0 || row >= count)
            break;

        // If row > 0, this means an item below the parent was selected. Which
        // one?
        nd = nd.childNodes().item(row);
        ret = nodeToIndex(row, column, nd);
    } while (false);
    return ret;
}

//---------------------------------------------
QModelIndex XmlTreeModel::parent(const QModelIndex &child) const {
    QModelIndex ret;
    do {
        QDomNode node = indexToNode(child);
        if (node.isNull())
            break;
        QDomNode parentNode = node.parentNode();
        //s = parentNode.toElement().tagName();
        if (parentNode.isNull())
            break;
        if (parentNode == doc)
            break; // I've spend two days writing this line :))
        QDomNode parentParentNode = parentNode.parentNode();
        QDomNodeList lst = parentParentNode.childNodes();
        for (int i=0; i < lst.count(); ++i) {
            QDomNode n = lst.item(i);
            //qDebug() << "i: " << i << "data:"<< n.getImpl() << "node: "<<n.toElement().tagName();
            if (n == parentNode) {
                ret = nodeToIndex(i, 0, parentNode);
                break;
            }
        }
    } while (false);
    return ret;
}

//---------------------------------------------
int XmlTreeModel::rowCount(const QModelIndex & parent) const {
    int ret = 0;
    QDomNode nd = indexToNode(parent);
    if (nd.isNull())
        nd = doc;

    // For text nodes, we want to be able to occupy extra rows
    // to break up long lines into additional table entries.
    if (nd.isText()) {
        QString value = nd.nodeValue();
        return value.count("\n");
    }
    ret = nd.childNodes().count();
    return ret;
}

//---------------------------------------------


/**
  In this two-column representation, the first column is a directory
  tree and the second column is a "view" of the contents of
  the node pointed to in the first column.
  */

int XmlTreeModel::columnCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return 2;
}

//---------------------------------------------
bool XmlTreeModel::hasChildren(const QModelIndex & parent) const {
    return (rowCount(parent) > 0);
}

/**
  Returns a QVariant, which might be a piece of text, or an icon representing
  the node.
 
  Question: For text, which contain newlines, how can we tell the View 
  class to render it with line-wrap?
  
  @param index - a pointer to the node for which we want to
        return some displayable information.
  
  @param role - either DecorationRole or DisplayRole. Because this is a
        callback, it is used by the view for both roles.
*/

QVariant XmlTreeModel::data(const QModelIndex& index, int role) const {
    static bool first_scan = true;
    static QIcon icoNode;
    static QIcon icoProcessInstr;
    static QIcon icoOther;

    if (first_scan) {
        first_scan = false;
        icoNode.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_DirClosedIcon), QIcon::Normal, QIcon::Off);
        icoNode.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_DirOpenIcon), QIcon::Normal, QIcon::On);
        icoProcessInstr.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_FileIcon));
        icoOther.addPixmap(QApplication::style()->standardPixmap(QStyle::SP_FileIcon));
    }

    if (!index.isValid())
      return QVariant();
    QDomNode nd = indexToNode(index);
    if (nd.isNull())
        return QVariant("NODE NOT FOUND");

    QVariant ret;

    if (role == DecorationRole) {
        if (index.column() == 0) {
            if (nd.isElement())
                ret = QVariant(icoNode);
            else if (nd.isProcessingInstruction())
                ret = QVariant(icoProcessInstr);
            else
                ret = QVariant(icoOther);
        }
    } else if (role == DisplayRole) {
        if (nd.isElement()) {
            if (index.column() == 0)
                ret = QVariant(" " + nd.nodeName());
            else if (index.column() == 1) {
                QDomElement el = nd.toElement();
                ret = nd.nodeName();
                if (!el.isNull()) {
                    QDomNamedNodeMap attrs = el.attributes();
                    QString s;
                    for (unsigned i=0; i < attrs.count(); ++i) {
                        QDomNode n = attrs.item(i);
                        if (i > 0)
                            s += ", ";
                        s += n.nodeName() + "='" + n.nodeValue() + "'";
                    }
                    ret = s;
                }
            }
        }
        else { // not an element - textnodes fall through to this condiiton
            if (index.column() == 0)
                ret = " " + nd.nodeName();
            else if (index.column() == 1) {
                // This is the actual text, newlines and all
                //                qDebug() << "value: " << nd.nodeValue();
                // Q: How to return formatted text? HTML?
                ret = nd.nodeValue();
            }
        }
    }
    return ret;
}

//---------------------------------------------
QVariant XmlTreeModel::headerData(int section, Qt::Orientation o, int role) const {
    QVariant ret;
    if (o == Qt::Horizontal) {
        if (role == DisplayRole)
            switch(section) {
            case 0:
                ret = "Name";
                break;
            case 1:
                ret = "Attributes";
                break;
            }
    }
    if (ret.isNull())
        ret = QAbstractItemModel::headerData(section, o, role);
    return ret;
}

ItemFlags XmlTreeModel::flags(const QModelIndex &index) const {
    if (index.isValid()) {
        return Qt::ItemIsSelectable;
    }
    return 0;
}

