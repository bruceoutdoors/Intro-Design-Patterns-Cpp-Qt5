#include <QtGui>
#include "palindate.h"
#include "palindromeform.h"

//start
PalindromeForm::PalindromeForm(QWidget* parent) : QWidget(parent),
  m_Palindate(new Palindate),
  m_LineEdit(new QLineEdit),
  m_Result(new QLabel) {
    setupForm();
}

void PalindromeForm::setupForm() {
   setWindowTitle("Palindrome Checker");
   m_LineEdit->setValidator(m_Palindate);
   connect(m_LineEdit, SIGNAL(returnPressed()),
           this, SLOT(showResult()));
//end
   connect(m_LineEdit, SIGNAL(textChanged(QString)),
           this, SLOT(showResult()));
   QPushButton* againButton = new QPushButton("Another Palindrome", this);
   QPushButton* quitButton = new QPushButton("Quit", this);
   QFormLayout *formL = new QFormLayout(this);
   formL->addRow("String to test:", m_LineEdit);
   formL->addRow("Result:", m_Result);
   QHBoxLayout *hBox = new QHBoxLayout;
   formL->addRow(hBox);
   hBox->addWidget(againButton);
   hBox->addWidget(quitButton);
   m_Result->setFrameStyle(QFrame::Panel);
   m_Result->setFrameShadow(QFrame::Raised);
   connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
   connect(againButton, SIGNAL(clicked()), this, SLOT(again()));
   move(500, 500); /* Start in mid screen (approx). */
//start
}
void PalindromeForm::showResult() {
   QString str = m_LineEdit->text();
   int pos(0);
   if(m_Palindate->validate(str,pos) == QValidator::Acceptable) {
      m_InputString = str;
      m_Result->setText("Valid Palindrome!");
   }
   else {
      m_InputString = "";
      m_Result->setText("Not a Palindrome!");
   }
}
//end
void PalindromeForm::again() {
   m_LineEdit->clear();
   m_Result->setText("");
   m_LineEdit->setFocus();
}

