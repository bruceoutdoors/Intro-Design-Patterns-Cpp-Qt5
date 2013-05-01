#include <QAction>
#include <QStyle>
#include <QKeyEvent>
#include <QIcon>
#include "actioneditordialog.h"
#include "ui_actioneditordialog.h"
//#include <QDebug>

ActionEditorDialog::ActionEditorDialog(QAction* action, QWidget* parent) :
    QDialog(parent), m_action(action),
    m_ui (new Ui::ActionEditorDialog) {
    m_ui->setupUi(this);
    m_ui->m_actionNameLabel->setText(action->text());
    m_sequence = m_action->shortcut();
    setFocusPolicy(Qt::StrongFocus);
    updateUi();
}

ActionEditorDialog::~ActionEditorDialog() {
    delete m_ui;

}

void ActionEditorDialog::keyPressEvent(QKeyEvent* evt) {
    if (evt->key() == 0 || evt->key() > 256) return;
    if (m_events.size() > 3) return;
//    qDebug() << "Saving event: " << evt->modifiers() << evt->key();
    m_events << evt;
    evt->accept();
    updateUi();
}

void ActionEditorDialog::updateUi() {
    if (!m_events.isEmpty()) {
        int keys[4] = {0,0,0,0};
        for (int i=0; i<m_events.size(); ++i) {
            QKeyEvent *evt = m_events[i];
            keys[i] = evt->modifiers() | evt->key();
        }
        m_sequence = QKeySequence(keys[0], keys[1], keys[2], keys[3]);
    }
    m_ui->m_shortcutLineEdit->setText(m_sequence.toString());
}

void ActionEditorDialog::on_m_clearButton_clicked() {
    m_events.clear();
    m_sequence = QKeySequence();
    m_ui->m_shortcutLineEdit->clear();
}

void ActionEditorDialog::changeEvent(QEvent* e) {
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
