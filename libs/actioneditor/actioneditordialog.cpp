#include <QAction>
#include "actioneditordialog.h"
#include <QStyle>
#include <QKeyEvent>
#include <QIcon>

#include <QDebug>
static QSet<int> modifiers;

ActionEditorDialog::ActionEditorDialog(QAction* action, QWidget* parent) :
    QDialog(parent), m_action(action) {
    if (modifiers.size() == 0) {
        modifiers << 0  << Qt::Key_unknown << Qt::Key_Shift << 16777250 <<
                Qt::Key_Alt << Qt::Key_Control;
    }
    setupUi(this);
    m_actionNameLabel->setText(action->text());
    m_actionIconLabel->setPixmap(action->icon().pixmap(50, 50));
    m_sequence = m_action->shortcut();
    setFocusPolicy(Qt::StrongFocus);
    updateUi();
}
//start id="keypressevent"
void ActionEditorDialog::keyPressEvent(QKeyEvent* evt) {        /* evt contains information about our keypress */
    int key = evt->key();
    if (modifiers.contains(key)) return;
    if (m_events.size() > 3) return;                                   /* only 4 can fit into a QKeySequence */
    QPair<int, int> pair = QPair<int, int>(evt->modifiers(), evt->key());
    qDebug() << "mods: " << evt->modifiers() << "key: " << evt->key();
    m_events << pair;                   /* Save the keystroke as a pair, to list of key events */
    evt->accept();                      /* Event does not need to be processed by any other widget */
    updateUi();
}
//end
//start id="updateui"
void ActionEditorDialog::updateUi() {
    if (!m_events.isEmpty()) {
        int keys[4] = {0,0,0,0};
        for (int i=0; i<m_events.size(); ++i) {
            QPair<int, int> pair = m_events[i];
            keys[i] = pair.first | pair.second;
        }
        m_sequence = QKeySequence(keys[0], keys[1], keys[2], keys[3]);
    }
    m_shortcutLineEdit->setText(m_sequence.toString());
}
//end
void ActionEditorDialog::on_m_clearButton_clicked() {
    m_events.clear();
    m_sequence = QKeySequence();
    m_shortcutLineEdit->clear();
}

void ActionEditorDialog::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
