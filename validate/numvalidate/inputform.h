#ifndef _INPUT_FORM_H_
#define _INPUT_FORM_H_

#include <QWidget>

class QLineEdit;
class QLabel;
//start
class InputForm : public QWidget {
    Q_OBJECT
 public:
    InputForm(int ibot, int itop, double dbot, double dtop);
 public slots:
    void computeResult();
 private:
    void setupForm();
    int m_BotI, m_TopI;
    double m_BotD, m_TopD;
    QLineEdit* m_IntEntry;
    QLineEdit* m_DoubleEntry;
    QLabel* m_Result;
};
//end
#endif

