#ifndef PROPERTYSELECTORVIEW_H
#define PROPERTYSELECTORVIEW_H

#include "propertyselectormodel.h"
#include <QAbstractListModel>
#include <QWidget>
#include <QListView>
#include <QMainWindow>
#include <QActionGroup>
#include <QObject>
#include <QAction>

class PropertySelectorView : public QListView
{
    Q_OBJECT

public:
    PropertySelectorView(QAbstractListModel* model, QWidget* parent = 0);

signals:
    void selectionsMade(QModelIndexList selects);

public slots:
    void sendSelects(bool);
    void closeWindow(bool);
    void restoreSelects(QList<QPersistentModelIndex> selects);

private:
    QAction* addChoice(QString name, QString text);
    QListView* m_ListView;
    QActionGroup* m_ActionGroup;
    QAction* m_ApplyAction;
    QAction* m_CancelAction;
};

#endif // PROPERTYSELECTORVIEW_H
