#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QtWidgets>

//class Order;
#include "order.h"

class OrderForm : public QWidget {
    Q_OBJECT
public:
    OrderForm(QWidget* parent =0);
    void setOrder(Order* prod);

public slots:
    void updateTotal();
    void submit();

private:
    QLineEdit* m_nameEdit;
    QDateEdit* m_dateEdit;
    QSpinBox* m_quantitySpin;
    QDoubleSpinBox* m_unitPrice;
    QDoubleSpinBox* m_totalPrice;
    QPushButton* m_submitButton;
    QPushButton* m_cancelButton;

    Order *m_Order;
};



#endif        //  #ifndef ORDERFORM_H
