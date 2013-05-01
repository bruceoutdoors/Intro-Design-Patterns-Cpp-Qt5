#ifndef STARDELEGATE_H
#define STARDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

/** Based on the StarDelegate example in the Qt 4.6 examples */
class StarDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    typedef QStyledItemDelegate SUPER;
    StarDelegate(QObject* parent=0) : SUPER(parent) {};
    QWidget* createEditor(QWidget* parent, 
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;
    void paint(QPainter* painter, 
               const QStyleOptionViewItem& option, 
               const QModelIndex& index) const;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const;
    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const;
};

#endif // STARDELEGATE_H

