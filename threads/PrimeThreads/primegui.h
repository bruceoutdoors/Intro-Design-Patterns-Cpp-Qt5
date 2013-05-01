#ifndef PRIMEGUI_H
#define PRIMEGUI_H

#include <QDialog>
#include "primeserver.h"
namespace Ui {
    class PrimeGUI;
}

class PrimeGUI : public QDialog
{
    Q_OBJECT

public:
    explicit PrimeGUI(QWidget *parent = 0);
    ~PrimeGUI();

private:
    Ui::PrimeGUI *ui;
    PrimeServer m_primeServer;
public slots:
    void showResults(QString);
    void accept();
    void reject();

};

#endif // PRIMEGUI_H
