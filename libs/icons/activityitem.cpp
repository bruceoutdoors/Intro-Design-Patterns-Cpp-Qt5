#include "activityitem.h"
#include "activity.h"
#include <QtGui>

ActivityItem::ActivityItem(QString text) 
: QObject(), QStandardItem(text) {
    m_isActive = false;
    setIcon(QIcon(":/icons/inactive.png"));
}

bool ActivityItem::isActive() const {
    return m_isActive;
}

void ActivityItem::setActive(bool isActive) {
    if (m_isActive == isActive) return;
    m_isActive = isActive;
    if (isActive) {
        connect (getMovie(), SIGNAL(frameChanged(int)),
            this, SLOT(updateIcon()));
    }
    else {
        disconnect (getMovie(), 0, this, 0);
        setIcon(QIcon(":/icons/inactive.png"));
    }
}

void ActivityItem::updateIcon() {
    setIcon(getCurrentIcon());
}

ActivityView::ActivityView(QObject *parent) {
    connect (this, SIGNAL(clicked(QModelIndex)),
             this, SLOT(itemClicked(QModelIndex)));
}

void ActivityView::itemClicked(QModelIndex idx) {
    QStandardItemModel *m = qobject_cast<QStandardItemModel*>(model());
    QStandardItem *item = m->itemFromIndex(idx);
    ActivityItem *ai = dynamic_cast<ActivityItem*>(item);
    bool active = !ai->isActive();
    ai->setActive(active);
}
