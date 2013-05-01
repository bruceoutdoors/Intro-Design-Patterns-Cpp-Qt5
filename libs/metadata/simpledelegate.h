#ifndef SIMPLEDELEGATE_H
#define SIMPLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemEditorFactory>
#include "metadataexport.h"

/**
   A simple item delegate for MetaDataObject properties.
   Overrides how a QTime is displayed in a playlistview.
*/
//start
class METADATAEXPORT SimpleDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    typedef QStyledItemDelegate SUPER;
    SimpleDelegate(QObject *parent = 0) : SUPER(parent) { }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
};
//end


#endif        //  #ifndef SIMPLEDELEGATE_H
