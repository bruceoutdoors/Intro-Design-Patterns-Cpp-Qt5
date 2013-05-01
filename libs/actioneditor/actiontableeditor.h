#ifndef ACTIONTABLEEDITOR_H
#define ACTIONTABLEEDITOR_H
#include "actioneditor_export.h"
#include <QDialog>
#include <QList>
#include "actioneditor_export.h"

class QModelIndex;
class QAction;
class QSortFilterProxyModel;
class ActionTableModel;

namespace Ui {
  class ActionTableEditor;   /* forward namespace class declaration */
};

/** Dialog for editing shortcuts in a table view.
    Inspired by a Qt3 example from qq14.
    Usage: call restoreShortcuts() once at program startup, to restore
    previously edited shortcuts from QSettings.
    Next, call ActionTableEditor::exec(), and it handles the rest, including
          saving changed shortcuts to QSettings.
    @author alan ezust
*/
class ACTIONEDITOR_EXPORT ActionTableEditor : public QDialog {

	Q_OBJECT
 public:
	/** Constructs a list of actions based on what it can find from
		qApp->findChildren and top level widgets children. */
	explicit ActionTableEditor(QWidget* parent=0);

	/** @param actions - list of actions to present in table */
	explicit ActionTableEditor(QList<QAction*> actions, QWidget* parent=0);

	virtual ~ActionTableEditor();

	/** @return a list of QActions that can be found by traversing the
	  QObject trees from the qApp and topLevelWidget roots. */
	static QList<QAction*> allActions();

	/** Restores shortcuts that were saved previously by this
		table
		@param actions list of QActions to restore */
	static void restoreShortcuts(QList<QAction*> actions = allActions()) ;

protected slots:
	void on_m_tableView_activated(const QModelIndex& idx);      /* Auto-connected slot */
	void on_m_filterField_textChanged(const QString& newText);  /* Auto-connected slot */
	/** Save changed shortcuts to QSettings */
	void accept();

protected:
	void setupSortFilter();
	void changeEvent(QEvent* e);

private:
	ActionTableModel* m_model;
	QSortFilterProxyModel* m_sortFilterProxy;
	Ui::ActionTableEditor* m_ui;            /* Designer ui object */
	QList<QAction*> m_changedActions;
};

#endif        //  #ifndef ACTIONTABLEEDITOR_H
