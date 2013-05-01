#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void clipboardChanged(QClipboard::Mode);
protected:
    void changeEvent(QEvent* e);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
