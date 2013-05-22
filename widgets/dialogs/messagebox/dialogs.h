#ifndef DIALOGS_H
#define DIALOGS_H

#include <QMainWindow>
#include <QString>

class Dialogs : public QMainWindow
{
    Q_OBJECT

public:
    Dialogs();

public slots:
    void askQuestion();
    void askDumbQuestion();

private:
    QString answer;
};

#endif // DIALOGS_H
