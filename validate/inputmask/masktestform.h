#ifndef MASK_TEST_FORM_H_
#define MASK_TEST_FORM_H_

#include <QWidget>
#include <QString>

class QLineEdit;
class QLabel;

//start
class MaskTestForm : public QWidget {
   Q_OBJECT
public:
   MaskTestForm();
public slots:  
   void showResult();
   void installMask();
   void again();
private:
   QLineEdit* m_InputMask;
   QLineEdit* m_StringEntry;
   QLabel* m_Result;
   void setupForm();
};
//end


#endif

