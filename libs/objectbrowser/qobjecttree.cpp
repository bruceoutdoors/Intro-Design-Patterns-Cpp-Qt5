#include "qobjecttree.h"

QList<QObject*> QObjectTreeModel::sm_extraObjects;

void QObjectTreeModel::addExtraObject(QObject *extra) {
    sm_extraObjects << extra;
}

	QObjectTreeItem::QObjectTreeItem(QObject *obj_in, QObjectTreeItem *parent) {
        // receivers("test");

        m_parentItem=parent;
        m_obj=obj_in;
        if (m_obj) {

            const QMetaObject *metaobj=m_obj->metaObject();
			if (metaobj) {
                m_object_type=metaobj->className();
			}
			else {
                m_object_type="Unknown";
			}
            // Find a good name for the object. Check a few places.
            QString text = m_obj->objectName();
            if (text.isEmpty())
                text = m_obj->property("title").toString();
            if (text.isEmpty())
                text = m_obj->property("windowTitle").toString();
            if (text.isEmpty())
                text = m_obj->property("text").toString();
            text = text.left(20);
            if (!text.isEmpty()) {
                m_object_type += QString(" (%1)").arg(text);
            }
            connect(m_obj, SIGNAL(destroyed()),
                    this, SLOT(on_object_destroyed()));
        }
		else {
            m_object_type="Objects";
		}
	}
    QObjectTreeItem::~QObjectTreeItem() {
        qDeleteAll(m_childItems);
        m_childItems.clear();
	}

    void QObjectTreeItem::appendChild(QObjectTreeItem *child) {
        m_childItems.append(child);
	}
	void QObjectTreeItem::removeChild(int row) {
		QObjectTreeItem *ptr=child(row);
        m_childItems.removeAt(row);
		if (ptr) {
			delete ptr;
		}
	}

    QObjectTreeItem *QObjectTreeItem::child(int row) {
        return m_childItems.value(row);
	}
    int QObjectTreeItem::childCount() const {
        return m_childItems.count();
	}
    int QObjectTreeItem::columnCount() const {
		return 1;
	}
    QVariant QObjectTreeItem::data(int column) const {
		if (column==0)
            return QVariant(m_object_type);
		else
			return QVariant();
		
	}
    int QObjectTreeItem::row() const {
        if (m_parentItem)
            return m_parentItem->m_childItems.indexOf(const_cast<QObjectTreeItem*>(this));
		return 0;
	}
    QObjectTreeItem *QObjectTreeItem::parent() {
        return m_parentItem;
	}
	QObjectTreeItem *QObjectTreeItem::find_child(QObject *ptr) {
		int j;
		for (j=0; j<childCount(); j++)
            if (child(j)->m_obj==ptr)
				return child(j);
		return 0;
	}
	void QObjectTreeItem::on_object_destroyed() {
        m_obj=0;
	}



	QObjectTreeModel::QObjectTreeModel(QObject *parent) : QAbstractItemModel(parent) {
		rootItem=new QObjectTreeItem(0);
		refresh();
	}
	QObjectTreeModel::~QObjectTreeModel() {
		delete rootItem;
	}

    QVariant QObjectTreeModel::data(const QModelIndex &index, int role) const {
		if (!index.isValid())
        return QVariant();

		if (role==Qt::DisplayRole) {
			QObjectTreeItem *item = static_cast<QObjectTreeItem*>(index.internalPointer());
			if (item)
				return item->data(index.column());
		}
		else if (role==Qt::DecorationRole) {
			QObjectTreeItem *item = static_cast<QObjectTreeItem*>(index.internalPointer());
			if (item) {
                if (item->m_obj->isWidgetType())
					return QIcon(":/images/widget.png");
				else
					return QIcon(":/images/object.png");
			}
		}
		return QVariant();
	}
    Qt::ItemFlags QObjectTreeModel::flags(const QModelIndex &index) const {
		if (!index.isValid())
        return Qt::ItemIsEnabled;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
    QVariant QObjectTreeModel::headerData(int section, Qt::Orientation orientation,
		int role) const 
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return rootItem->data(section);

		return QVariant();
	}
    QModelIndex QObjectTreeModel::index(int row, int column,
                      const QModelIndex &parent) const 
	{
		QObjectTreeItem *parentItem;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<QObjectTreeItem*>(parent.internalPointer());

		QObjectTreeItem *childItem = parentItem->child(row);
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();
	}
    QModelIndex QObjectTreeModel::parent(const QModelIndex &index) const {
		if (!index.isValid())
        return QModelIndex();

		QObjectTreeItem *childItem = static_cast<QObjectTreeItem*>(index.internalPointer());
		QObjectTreeItem *parentItem = childItem->parent();

		if (parentItem == rootItem)
			return QModelIndex();

		return createIndex(parentItem->row(), 0, parentItem);
	}
	QObjectTreeItem *QObjectTreeModel::find_item(QObjectTreeItem *ptr,QObject *obj) {
		if (!ptr) return 0;
        if (ptr->m_obj==obj) return ptr;
		int j;
		for (j=0; j<ptr->childCount(); j++) {
			QObjectTreeItem *ret=find_item(ptr->child(j),obj);
			if (ret) return ret;
		}
		return 0;
	}
	QModelIndex QObjectTreeModel::getindex(QObject *obj) {
		QObjectTreeItem *item=find_item(rootItem,obj);
		if (!item) return QModelIndex();
		return createIndex(item->row(),0,item);
	}
    int QObjectTreeModel::rowCount(const QModelIndex &parent) const {
		QObjectTreeItem *parentItem;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<QObjectTreeItem*>(parent.internalPointer());

		return parentItem->childCount();
	}
    int QObjectTreeModel::columnCount(const QModelIndex &parent) const {
		if (parent.isValid())
			return static_cast<QObjectTreeItem*>(parent.internalPointer())->columnCount();
		else
	        return rootItem->columnCount();
	}
	void QObjectTreeModel::refresh() {
		layoutAboutToBeChanged();
		refresh(QModelIndex());
		layoutChanged();
	}
	void QObjectTreeModel::clear_persistent_data(QModelIndex index) {
		int j;
		for (j=0; j<rowCount(index); j++)
			clear_persistent_data(index.child(j,0));
		changePersistentIndex(index,QModelIndex());
	}
	void QObjectTreeModel::refresh(const QModelIndex &aIndex) {
		QModelIndex index=aIndex;
		QObjectTreeItem *parent = static_cast<QObjectTreeItem *>(index.internalPointer());
		if (!parent) {
			parent = rootItem;
			index=createIndex(0,0,rootItem);
		}
		if (!parent) return;
		if (!index.isValid()) return;

		QObjectList object_list;
		
        if (parent->m_obj)
            object_list=parent->m_obj->children();
		else {
		    object_list.append(qApp);
            object_list.append(sm_extraObjects);
			QWidgetList widgets=qApp->allWidgets();
			int j;
			for (j=0; j<widgets.count(); j++) {
				if (!widgets[j]->parentWidget()) { //top level widget
					object_list.append(widgets[j]);
				}
			}
		}

        int j;
		for (j=0; j<object_list.count(); j++) {
			QObjectTreeItem *child=parent->find_child(object_list[j]);
			if (!child) {
				//emit layoutAboutToBeChanged();
				child=new QObjectTreeItem(object_list[j],parent);
				parent->appendChild(child);
				//emit layoutChanged();
			}
			if (child) {
				refresh(index.child(child->row(),0));
			}
		}

		for (j=0; j<parent->childCount(); j++) {
            if (!object_list.contains(parent->child(j)->m_obj)) {
				//emit layoutAboutToBeChanged();
				clear_persistent_data(index.child(j,0));
				parent->removeChild(j);
				//emit layoutChanged();
				j--;
			}
		}

	}


	QObjectTree::QObjectTree() {
		setup_widget_menu();
	}

	void QObjectTree::setup_widget_menu() {
		widget_menu=new QMenu;

		QAction *Act;

		//Show
		Act = new QAction(tr("Show"), this);
		connect(Act, SIGNAL(triggered()), this, SIGNAL(show_widget()));
		widget_menu->addAction(Act);

		//Hide
		Act = new QAction(tr("Hide"), this);
		connect(Act, SIGNAL(triggered()), this, SIGNAL(hide_widget()));
		widget_menu->addAction(Act);

		//Focus
		Act = new QAction(tr("Focus"), this);
		connect(Act, SIGNAL(triggered()), this, SIGNAL(focus_widget()));
		widget_menu->addAction(Act);
	}

	QObjectTree::~QObjectTree() {
	}
    void QObjectTree::currentChanged ( const QModelIndex & , const QModelIndex & ) {
		emit current_item_changed();
	}
	void QObjectTree::mousePressEvent ( QMouseEvent * event ) {
		QTreeView::mousePressEvent(event);
		if (event->button()==Qt::RightButton) {
			widget_menu->popup(mapToGlobal(QPoint(event->x(),event->y())));
		}
	}
