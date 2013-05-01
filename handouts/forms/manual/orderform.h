#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QtGui>

class Order;

class OrderForm : public QWidget {
    Q_OBJECT
public:
    OrderForm(QWidget* parent =0);

    void setOrder(Order* prod);
public slots:
    void submit();
    void cancel();


private:
    QLineEdit* m_nameEdit;
    QDateEdit* m_dateEdit;
    QSpinBox* m_quantitySpin;
    QPushButton* m_submitButton;
    QPushButton* m_cancelButton;

    Order *m_Order;
};



#endif        //  #ifndef ORDERFORM_H
