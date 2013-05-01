#include "primegui.h"
#include "ui_primegui.h"
#include <QtGui>
#include "primeserver.h"
PrimeGUI::PrimeGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimeGUI)
{
    ui->setupUi(this);

    int nthreads = QThreadPool::globalInstance()->maxThreadCount();

    ui->numThreadsSpinbox->setValue(nthreads);
    ui->highestNumberSpinbox->setValue(1000000);


    connect (&m_primeServer, SIGNAL(results(QString)),
             this, SLOT(showResults(QString)));
}

void PrimeGUI::showResults(QString msg) {
    ui->resultsEdit->append(msg);
    ui->buttonBox->setStandardButtons(QDialogButtonBox::Close | QDialogButtonBox::Ok);
}


void PrimeGUI::reject() {
   if (m_primeServer.isRunning())
        m_primeServer.cancel();
   else QDialog::reject();
}

PrimeGUI::~PrimeGUI()
{
    delete ui;
}

void PrimeGUI::accept()
{
    if (m_primeServer.isRunning()) {
        qDebug() << "already running.";
        return;
    }
    int nthreads = ui->numThreadsSpinbox->value();
    int highestNumber = ui->highestNumberSpinbox->value();
    ui->buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
    qApp->processEvents();
    m_primeServer.doCalc(nthreads, highestNumber, ui->concurrentBox->isChecked());
}
