#ifndef UNDOMAINWIN_H
#define UNDOMAINWIN_H

#include <QMainWindow>
#include <QUndoStack>

class QWidget;
class QLabel;
class QImage;
class QEvent;
namespace Ui {
    class UndoMainWin;
}

class UndoMainWin : public QMainWindow {
    Q_OBJECT
 public:
    explicit UndoMainWin(QWidget* parent = 0);
    ~UndoMainWin();

 public slots:
    void displayImage(const QImage& img);

 private:
    Ui::UndoMainWin* ui;
    QLabel* m_ImageDisplay;
    QImage m_Image;
    QUndoStack m_Stack;

private slots:
    void on_redoButton_clicked();
    void on_openButton_clicked();
    void on_actionAdjust_Color_triggered();
    void on_actionUndo_The_Last_Action_triggered();
    void on_actionHorizontal_Mirror_triggered();
    void on_actionVertical_Mirror_triggered();
    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionClose_triggered();
    void on_saveButton_clicked();
    void on_quitButton_clicked();
    void on_adjustColorButton_clicked();
    void on_undoButton_clicked();
    void on_verticalMirrorButton_clicked();
    void on_horizontalMirrorButton_clicked();
    void on_actionOpen_triggered();
};

#endif // UNDOMAINWIN_H
