#ifndef ACTIONSDIALOG_H
#define ACTIONSDIALOG_H

#include <QAction>
#include <QList>
#include <QWidget>
#include <QTableWidget>

/** based on Qt3 code from the Qt Quarterly issue#14.
    Updated to Qt 4.6 with enhancements by Alan Ezust */
class ActionsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ActionsDialog(const QList<QAction*>& actions, QWidget* parent = 0);

protected slots:
    void accept();

private slots:
    void recordAction(int row, int column);
    void validateAction(int row, int column);

private:
    QString m_oldAccelText;
    QTableWidget* m_actionsTable;
    QList<QAction*> m_actionsList;
};

#endif
