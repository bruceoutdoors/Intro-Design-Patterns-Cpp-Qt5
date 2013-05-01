#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_
#include <QWidget>
#include <QString>

class Palindate;
class QLineEdit;
class QLabel;
//start
class PalindromeForm : public QWidget {
   Q_OBJECT
public:
   PalindromeForm(QWidget* parent=0);
   QString getPalindrome();
public slots:
   void showResult();
   void again();
private:
   Palindate* m_Palindate;
   QLineEdit* m_LineEdit;
   QLabel* m_Result;
   QString m_InputString;
   void setupForm();
};
//end
#endif

