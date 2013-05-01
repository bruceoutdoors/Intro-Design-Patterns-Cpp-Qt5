#ifndef ACTIONEDITORDIALOG_H
#define ACTIONEDITORDIALOG_H

#include "ui_actioneditordialog.h"
class QAction;
#include <QShortcut>
#include <QString>
#include <QDialog>
#include <QList>
#include <QKeySequence>
#include "actioneditor_export.h"

/** A dialog for editing a single action.
	 Captures QKeySequence and displays it in a QLineEdit.
	 @author Alan Ezust
*/

class ACTIONEDITOR_EXPORT ActionEditorDialog : public QDialog, private Ui::ActionEditorDialog {
	Q_OBJECT
public:
    /** @param action - the action we wish to edit the shortcut for */
	explicit ActionEditorDialog(QAction* action, QWidget* parent = 0);
	void keyPressEvent(QKeyEvent*);

	/** @return keys entered since the last clear button */
	QKeySequence keySequence() const {return m_sequence;}

protected slots:
	void on_m_clearButton_clicked();
	void updateUi();
protected:
	void changeEvent(QEvent* e);
private:
	QKeySequence m_sequence;
	QAction* m_action;
	QList<QPair<int, int> > m_events;

};

#endif // ACTIONEDITORDIALOG_H
