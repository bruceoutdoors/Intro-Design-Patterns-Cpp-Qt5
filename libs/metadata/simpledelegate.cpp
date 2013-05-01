#include <QDebug>
#include <QApplication>
#include <QMetaType>
#include <QVariant>
#include <QPainter>
#include <QItemEditorFactory>
#include <preference.h>
#include "simpledelegate.h"
#include "preferencecombo.h"
#include "timedisplay.h"


//start id=paint
void SimpleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    QStyle *style = QApplication::style();

    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();

    QVariant var(index.data(Qt::DisplayRole));
    if (var.isNull()) {
//        qDebug() << "mp3fd:paint - variant is null";
        return;
    }

    if (var.userType() == qMetaTypeId<Preference>()) {
        Preference p = var.value<Preference>();
        QString s = QString("%1").arg(p.intValue());
        //painter->drawText(option.rect, s, QTextOption());
        style->drawItemText(painter, option.rect, index.flags(), option.palette, true, s);
        return;
    }
    if (field == "TrackTime") {

        QTime time;
        if (var.canConvert(QVariant::Time)) time = var.toTime();
        else {
            int secs = var.toInt();
            time = time.addSecs(secs);
        }
        QString str = time.toString("m:ss");
        // painter->drawText(option.rect, str, QTextOption());
        style->drawItemText(painter, option.rect, index.flags(),  option.palette, true, str);
        return;
    }
    SUPER::paint(painter, option, index);
}
//end

