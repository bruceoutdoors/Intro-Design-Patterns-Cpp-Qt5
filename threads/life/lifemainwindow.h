#ifndef LIFEMAINWINDOW_H
#define LIFEMAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QRect>
#include <QImage>
#include "lifeslice.h"

class LifeWidget;
namespace Ui {
    class LifeMainWindow;
}

/** An example of Conway's game of life distributed across
    threads using QtConcurrent mapReduce functions.
*/ 
class LifeMainWindow : public QMainWindow
{
    Q_OBJECT

public:  
    explicit LifeMainWindow(QWidget *parent = 0);
    ~LifeMainWindow();
    void closeEvent(QCloseEvent *);

private:
    Ui::LifeMainWindow *ui;
    LifeWidget* m_lifeWidget;
    QImage m_current;
    int m_numGenerations;
    QTime m_timer;
    bool m_running;

private slots:
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_triggered();
    void on_threadSpinBox_valueChanged(int );
    void on_actionQuit_triggered();
    void on_actionClear_triggered();
    void on_actionStartStop_triggered(bool checked);
    void on_actionPopulate_Randomly_triggered();
    void calculate();
};

#endif // LIFEMAINWINDOW_H
