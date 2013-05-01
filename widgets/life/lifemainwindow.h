#ifndef LIFEMAINWINDOW_H
#define LIFEMAINWINDOW_H

#include <QMainWindow>
#include <QTime>

class LifeWidget;
namespace Ui {
    class LifeMainWindow;
}

class LifeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum {DEAD=0, ALIVE=1};
    explicit LifeMainWindow(QWidget* parent = 0);
    ~LifeMainWindow();
    void closeEvent(QCloseEvent* evt);
    static int neighborCount(const QImage& img, int x, int y);
private:
    QSize m_boardSize;
    Ui::LifeMainWindow* ui;
    LifeWidget* m_lifeWidget;
    QImage m_current;
    int m_numGenerations;
    QTime m_timer;
    bool m_running;

private slots:
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionQuit_triggered();
    void on_actionClear_triggered();
    void on_actionStartStop_triggered(bool checked);
    void on_actionPopulate_Randomly_triggered();
    void calculate();

};

#endif // LIFEMAINWINDOW_H
