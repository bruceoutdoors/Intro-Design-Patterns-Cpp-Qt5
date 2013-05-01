#include "rinputform.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QLabel>
#include <QFrame>

//start
QRegExp RinputForm::s_PhoneFormat(
  "(\\+?1[- ]?)?\\(?(\\d{3,3})\\)?[\\s-]?(\\d{3,3})[\\s-]?(\\d{4,4})");

RinputForm::RinputForm(QWidget* parent)
:   QWidget(parent),
    m_PhoneEntry(new QLineEdit),
    m_PhoneResult(new QLabel) {
    setupForm();
    move(500, 500); /* Start in mid screen (approx). */
}

void RinputForm::setupForm() {
    //end
    setWindowTitle("Phone Number Validator");
    QLabel* label = new QLabel("Phone number:", this);
    QGridLayout* layout(new QGridLayout);
    layout->addWidget(label, 0,0);
    layout->addWidget(m_PhoneEntry,0,1);
    label = new QLabel("Phone result: ", this);
    layout->addWidget(label, 1,0);
    m_PhoneResult->setFrameStyle(QFrame::Panel);
    m_PhoneResult->setFrameShadow(QFrame::Raised);
    layout->addWidget(m_PhoneResult,1,1);
    setLayout(layout);
    //start
    QRegExpValidator* 
          phoneValid(new QRegExpValidator(s_PhoneFormat, this));
    m_PhoneEntry->setValidator(phoneValid);
    connect(m_PhoneEntry, SIGNAL(returnPressed()),
            this, SLOT(computeResult()));
}

void RinputForm::computeResult() {
    m_Phone = m_PhoneEntry->text();
    if (s_PhoneFormat.exactMatch(m_Phone)) {
        QString areacode = s_PhoneFormat.cap(2);
        QString exchange = s_PhoneFormat.cap(3);
        QString number = s_PhoneFormat.cap(4);
        m_PhoneResult->setText(QString("(US/Canada) +1 %1-%2-%3")
              .arg(areacode).arg(exchange).arg(number));
    }
}
//end

