#ifndef KEYSEQUENCELABEL_H
#define KEYSEQUENCELABEL_H
//start
#include "ui_keysequencelabel.h"
#include <QList>
#include <QPair>
class QObjectBrowserAction;

class KeySequenceLabel : public QMainWindow, private Ui::KeySequenceLabel {
    Q_OBJECT
 public:
    explicit KeySequenceLabel(QWidget* parent = 0);
 protected:                         /* QWidget event handler overrides */
    void changeEvent(QEvent* e);
    void keyPressEvent(QKeyEvent*);
    void leaveEvent(QEvent*);
    void enterEvent(QEvent*);
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);  /* QObject event handler override */
    void updateUi();
 private slots:
    void on_actionShow_ObjectBrowser_triggered(bool checked);
    void on_m_clearButton_clicked();
    void on_actionQuit_triggered();
 private:
    QObjectBrowserAction* m_browserAction;
    QList<QPair<int, int> > m_keys;
    int m_paints;
};
//end

#endif // KEYSEQUENCELABEL_H

