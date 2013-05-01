#include <QItemEditorFactory>
#include <QApplication>
#include <QVariant>
#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"
#include "timedisplay.h"


//start id=createeditor
QWidget* StarDelegate::
    createEditor(QWidget* parent, 
                 const QStyleOptionViewItem& option,
                 const QModelIndex& index) const {
    QString field = index.model()->headerData(index.column(),
                                  Qt::Horizontal).toString();
    if (field == "rating")  {
            return new StarEditor(parent);
    }
    if (field == "length") {
        return new TimeDisplay(parent);
    }
    return SUPER::createEditor(parent, option, index);
}
//end
//start id=seteditordata
void StarDelegate::
    setEditorData(QWidget* editor, 
                  const QModelIndex& index) const {
    QVariant val = index.data(Qt::EditRole);
    StarEditor* starEditor = qobject_cast<StarEditor*>(editor);     /* Dynamic type checking. */
    if (starEditor != 0) {
        StarRating sr = qVariantValue<StarRating>(val);             /* Extract user type value from QVariant. */
        starEditor->setStarRating(sr);
        return;
    }
    TimeDisplay* timeDisplay = qobject_cast<TimeDisplay*>(editor);  /* Dynamic type checking. */
    if (timeDisplay != 0) {
        QTime t = val.toTime();
        timeDisplay->setTime(t);
        return;
    }
    SUPER::setEditorData(editor, index);                            /* Let base class handle other types. */
    return;
}
//end
//start id=setmodeldata
void StarDelegate::
    setModelData(QWidget* editor, QAbstractItemModel* model, 
                 const QModelIndex& index) const {
    StarEditor* starEditor = qobject_cast<StarEditor*>(editor);
    if (starEditor != 0) {
        StarRating r = starEditor->starRating();
        QVariant v;
        v.setValue<StarRating>(r);
        model->setData(index, v, Qt::EditRole);
        return;
    }
    TimeDisplay* td = qobject_cast<TimeDisplay*>(editor);
    if (td != 0) {
        QTime t = td->time();
        model->setData(index, QVariant(t));
        return;
    }
    SUPER::setModelData(editor, model, index);
    return;
}
//end
//start id=paint
void StarDelegate::
    paint(QPainter* painter, 
          const QStyleOptionViewItem& option, 
          const QModelIndex& index) const {
    QString field = index.model()->headerData(index.column(),
                                           Qt::Horizontal).toString();
    if (field == "length") {
        QVariant var = index.data(Qt::DisplayRole);
        Q_ASSERT(var.canConvert(QVariant::Time));
        QTime time = var.toTime();
        QString str = time.toString("m:ss");
        painter->drawText(option.rect, str, QTextOption());
        // can't use drawDisplay with QStyledItemDelegate:
        // drawDisplay(painter, option, option.rect, str);
        return;
    }
    if (field != "rating") {
        SUPER::paint(painter, option, index);
        return;
    }
    QVariant variantData = index.data(Qt::DisplayRole);
    StarRating starRating = variantData.value<StarRating>();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
    starRating.paint(painter, option.rect, option.palette,
                     StarRating::ReadOnly);
}
//end

