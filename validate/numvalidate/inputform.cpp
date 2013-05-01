#include "inputform.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QLabel>
#include <QFrame>
#include <QString>
//start
InputForm::InputForm(int ibot, int itop, double dbot, double dtop):
    m_BotI(ibot), m_TopI(itop), m_BotD(dbot), m_TopD(dtop),
    m_IntEntry(new QLineEdit("0")),
    m_DoubleEntry(new QLineEdit("0")),
    m_Result(new QLabel("0")) { 
    setupForm();
    move(500, 500); /* Start in mid screen (approx). */
}

void InputForm::setupForm() {
    //end
    setWindowTitle("Work-Study Salary Calculator");
    QString ltext(QString("Hours Worked (between %1 and %2)")
                  .arg(m_BotI).arg(m_TopI));
    QLabel* label(new QLabel(ltext, this));
    QGridLayout* layout(new QGridLayout(this));
    layout->addWidget(label, 0,0);
    layout->addWidget(m_IntEntry,0,1);
    ltext = QString("Hourly Pay Rate (between %1 and %2)")
        .arg(m_BotD).arg(m_TopD);
    label = new QLabel(ltext, this);
    layout->addWidget(label, 1,0);
    layout->addWidget(m_DoubleEntry,1,1);
    label = new QLabel("Total Pay for the week: ", this);
    layout->addWidget(label, 2,0);
    m_Result->setFrameStyle(QFrame::Panel);
    m_Result->setFrameShadow(QFrame::Raised);
    layout->addWidget(m_Result,2,1);
//start
    QIntValidator* iValid(new QIntValidator(m_BotI, m_TopI, this));
    QDoubleValidator* 
             dValid(new QDoubleValidator(m_BotD, m_TopD, 2, this));
    m_IntEntry->setValidator(iValid);
    m_DoubleEntry->setValidator(dValid);
    connect(m_IntEntry, SIGNAL(returnPressed()), 
            this, SLOT(computeResult()));
    connect(m_DoubleEntry, SIGNAL(returnPressed()),
            this, SLOT(computeResult()));
}
//end

void InputForm::computeResult() {
    double d = m_DoubleEntry->text().toDouble();
    int i = m_IntEntry->text().toInt();
    double res = d * i;
    m_Result->setText(QString("%1").arg(res));
}


