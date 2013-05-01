#ifndef QOBJECTTREE_H
#define QOBJECTTREE_H

#include <QList>
#include <QWidget>
#include <QObject>
#include <QApplication>
#include <QTreeWidget>
#include <QMetaObject>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QMenu>
#include <QMouseEvent>
#include "obexport.h"
class QObjectTreeItem : public QObject
{
	Q_OBJECT
public:
    QObject *m_obj;

    QObjectTreeItem(QObject *obj_in, QObjectTreeItem *parent = 0);
    ~QObjectTreeItem();

    void appendChild(QObjectTreeItem *child);
	void removeChild(int row);

    QObjectTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    QObjectTreeItem *parent();
	QObjectTreeItem *find_child(QObject *ptr);
public slots:
	void on_object_destroyed();

private:
    QList<QObjectTreeItem*> m_childItems;
    QString m_object_type;
    QObjectTreeItem *m_parentItem;
};

/** A concrete tree model implemented from QAbstractItemModel,
    that allows a QTreeView to inspect the QObjects in memory,
    and all of their QMetaObject/Property/Type/Method info. 
*/
class OBJECTBROWSER_EXPORT QObjectTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QObjectTreeModel(QObject *parent = 0);
    ~QObjectTreeModel();

    /** Add an extra object to be shown in the list */
    static void addExtraObject(QObject* extra);

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
	QObjectTreeItem *find_item(QObjectTreeItem *ptr,QObject *obj);
	QModelIndex getindex(QObject *obj);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
	void refresh();
	void clear_persistent_data(QModelIndex index);
	void refresh(const QModelIndex &aIndex);

    QObjectTreeItem *rootItem;
    static QList<QObject*> sm_extraObjects;
};

class OBJECTBROWSER_EXPORT QObjectTree : public QTreeView {
	Q_OBJECT
public:
	QMenu *widget_menu;
	QObjectTree();
	void setup_widget_menu();
	virtual ~QObjectTree();
protected:
	void currentChanged ( const QModelIndex & current, const QModelIndex & previous );
	void mousePressEvent ( QMouseEvent * event );
signals:
	void current_item_changed();
	void show_widget();
	void hide_widget();
	void focus_widget();
};


#endif

