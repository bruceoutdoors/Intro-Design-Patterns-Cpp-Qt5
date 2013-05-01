#ifndef ACTIONEDITORDIALOG_H
#define ACTIONEDITORDIALOG_H


#include <QShortcut>
#include <QString>
#include <QDialog>
#include <QList>
#include <QKeySequence>
class QAction;

namespace Ui {
class ActionEditorDialog;
}

/** A dialog for editing a single action.
     Captures keySequences and displays them in a lineEdit.
*/

class ActionEditorDialog : public QDialog {
    Q_OBJECT
 public:
    explicit ActionEditorDialog(QAction* action, QWidget* parent = 0);
    ~ActionEditorDialog();
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
    QList<QKeyEvent*> m_events;
    Ui::ActionEditorDialog* m_ui;
};

#endif // ACTIONEDITORDIALOG_H
