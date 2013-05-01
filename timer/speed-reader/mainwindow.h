#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "randomstring.h"

namespace Ui {
    class MainWindow;
}
//start
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
protected:
    void changeEvent(QEvent* e);
    void processTrial();
private:
    Ui::MainWindow* ui;
private slots:
    void on_nextButton_clicked();
    void on_responseString_returnPressed();
    void on_startButton_clicked();
    void on_lengthSlider_valueChanged(int value);
    void on_exposureSlider_valueChanged(int value);
    void timerDisplayRandStr();
private:
    int m_expInterval;
    RandomString m_randStr;
    int m_trials;
    int m_correctChars;
    int m_totTrials;
    int m_totCorrectChars;
};
//end
#endif // MAINWINDOW_H
