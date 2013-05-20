
#ifndef APPLICATION_H
#define APPLICATION_H

#include <qmainwindow.h>
#include <QPrinter>

class QDialog;
class QTextEdit;

class ApplicationWindow: public QMainWindow
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget* parent=0);
    ~ApplicationWindow();

protected:
    void closeEvent( QCloseEvent* );

private slots:
    void newDoc();
    void choose();
    void load( const QString &fileName );
    void save();
    void saveAs();
    void print();
    void whatsThis();
    void setWindowModified(bool value=true) {
        QMainWindow::setWindowModified(value);
    }

    void about();
    void editShortcuts();
    void objectBrowser();

private:


    QPrinter *printer;
    QTextEdit *textEdit;
    QString filename;
};


#endif
