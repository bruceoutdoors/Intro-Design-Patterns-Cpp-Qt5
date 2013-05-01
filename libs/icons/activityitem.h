#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H
#include "icons_export.h"
#include <QObject>
#include <QStandardItem>

/** A QStandardItem with an activity spinner */
class ICONS_EXPORT ActivityItem : public QObject, public QStandardItem {
    Q_OBJECT
public:
    ActivityItem(QString text);
    /** @return true if the icon is spinning */
    bool isActive() const;  
public slots:
    /** @param isActive if true, start spinning the spinner icon */
    void setActive(bool isActive=true);
protected slots:
    void updateIcon();
private:
    bool m_isActive;
};


#include <QTreeView>
/** A test view for ActivityIcon */
class ICONS_EXPORT ActivityView: public QTreeView {
 Q_OBJECT
public:
    ActivityView(QObject* parent =0);
public slots:
    void itemClicked(QModelIndex);

};


#endif        //  #ifndef ACTIVITYITEM_H
