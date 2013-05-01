#include <QtGui>
#include "keysequencelabel.h"
#include "qobjectbrowseraction.h"

//start id="timer"
KeySequenceLabel::KeySequenceLabel(QWidget* parent) :
    QMainWindow(parent), m_browserAction(new QObjectBrowserAction(this)) {

    setupUi(this);
    startTimer(2000); /* A timer event occurs every 2 seconds. */
    m_paints = 0;
}

void KeySequenceLabel::timerEvent(QTimerEvent*) {
    m_lcdNumber->display(m_paints);
}

void KeySequenceLabel::paintEvent(QPaintEvent* evt) {
    ++m_paints;
    QMainWindow::paintEvent(evt);
}
//end
//start id="keyevent"
void KeySequenceLabel::keyPressEvent(QKeyEvent* evt) {
    bool doNothing = false;

    if (evt->key() == 0) doNothing = true;
    if (m_keys.size() > 3) doNothing = true;
    if (doNothing) {
        QMainWindow::keyPressEvent(evt); /* QWidget's base class handler
                   responds to ESC for pop-up windows. */
        return;
    }
    QPair<int, int> pair = QPair<int, int>(evt->modifiers(), evt->key());
    m_keys << pair;
    evt->accept();
    updateUi();
}

void KeySequenceLabel::updateUi() {
    if (!m_keys.isEmpty()) {
        int keys[4] = {0,0,0,0};
        for (int i=0; i<m_keys.size(); ++i) {
            QPair<int, int> pair = m_keys[i];
            keys[i] = pair.first | pair.second;
        }
        QKeySequence seq = QKeySequence(keys[0], keys[1], keys[2], keys[3]);
        m_label->setText(seq.toString());
    }
    else m_label->clear();
}
//end
//start id="enterleave"
void KeySequenceLabel::enterEvent(QEvent* evt) {

    statusBar()->showMessage(tr("Mouse is in da house"));
    evt->accept();

}

void KeySequenceLabel::leaveEvent(QEvent* evt) {
    statusBar()->showMessage(tr("Mouse has left the building"));
    evt->accept();
}
//end

void KeySequenceLabel::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void KeySequenceLabel::on_actionQuit_triggered()
{
    qApp->quit();
}

void KeySequenceLabel::on_m_clearButton_clicked()
{
    m_keys.clear();
    updateUi();
}

void KeySequenceLabel::on_actionShow_ObjectBrowser_triggered(bool checked)
{
    m_browserAction->setChecked(checked);
}

