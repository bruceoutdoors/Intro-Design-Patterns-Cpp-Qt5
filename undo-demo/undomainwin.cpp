#include <QtWidgets>
//start
#include "image-manip.h"
#include "ui_undomainwin.h"
#include "undomainwin.h"

UndoMainWin::UndoMainWin(QWidget *parent) 
: QMainWindow(parent), ui(new Ui::UndoMainWin), 
  m_ImageDisplay(new QLabel(this)), m_Image(QImage()) {
  ui->setupUi(this);
  m_ImageDisplay->setMinimumSize(640,480);
}

UndoMainWin::~UndoMainWin() {
  delete ui; /* Neither a QObject nor a child, it 
                must be deleted explicitly. */
}

void UndoMainWin::displayImage(const QImage &img) {
    m_ImageDisplay->setPixmap(QPixmap::fromImage(img)); 
}

void UndoMainWin::on_actionOpen_triggered() {
    m_Image.load(QFileDialog::getOpenFileName());
    displayImage(m_Image);
}

void UndoMainWin::on_horizontalMirrorButton_clicked() {
    MirrorPixels* mp = new MirrorPixels(m_Image, true);
    m_Stack.push(mp);
    displayImage(m_Image);
}


void UndoMainWin::on_adjustColorButton_clicked() {
    double radj(ui->redSpin->value()), gadj(ui->greenSpin->value()), 
    badj(ui->blueSpin->value());
    AdjustColors* ac = new AdjustColors(m_Image, radj, gadj, badj);
    m_Stack.push(ac);
    displayImage(m_Image);
}
//end
void UndoMainWin::on_actionAdjust_Color_triggered() {
    ui->redSpin->setFocus();
}
void UndoMainWin::on_openButton_clicked() {
     on_actionOpen_triggered();
}

void UndoMainWin::on_actionHorizontal_Mirror_triggered() {
    on_horizontalMirrorButton_clicked();
}

void UndoMainWin::on_verticalMirrorButton_clicked()
{
    MirrorPixels* mp = new MirrorPixels(m_Image, false);
    m_Stack.push(mp);
    displayImage(m_Image);
}

void UndoMainWin::on_actionVertical_Mirror_triggered()
{
    on_verticalMirrorButton_clicked();
}

void UndoMainWin::on_undoButton_clicked()
{
    m_Stack.undo();
    displayImage(m_Image);
}

void UndoMainWin::on_actionUndo_The_Last_Action_triggered()
{
    on_undoButton_clicked();
}

void UndoMainWin::on_quitButton_clicked()
{
    QApplication::quit();
}

void UndoMainWin::on_actionQuit_triggered()
{
    on_quitButton_clicked();
}

void UndoMainWin::on_saveButton_clicked()
{
    QString filename(QFileDialog::getSaveFileName());
    m_Image.save(filename);
}

void UndoMainWin::on_actionSave_triggered()
{
    on_saveButton_clicked();
}

void UndoMainWin::on_actionClose_triggered()
{
    m_ImageDisplay->clear();
    m_Image.allGray();
}


void UndoMainWin::on_redoButton_clicked()
{
    m_Stack.redo();
    displayImage(m_Image);
}
