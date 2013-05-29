#include "orderform.h"
/* You must implement the missing methods in this file */

OrderForm::OrderForm(QWidget* parent)
{
    m_nameEdit = new QLineEdit();
    m_dateEdit = new QDateEdit;
    m_dateEdit->setDisplayFormat("dd/MM/yyyy");
    m_quantitySpin = new QSpinBox();
    m_unitPrice = new QDoubleSpinBox();
    m_totalPrice = new QDoubleSpinBox();
    m_totalPrice->setReadOnly(true);
    m_submitButton = new QPushButton(tr("submit"));
    m_cancelButton = new QPushButton(tr("cancel"));

    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox = new QHBoxLayout;
    QFormLayout* layout = new QFormLayout;

    layout->addRow(tr("Name"), m_nameEdit);
    layout->addRow(tr("Date"), m_dateEdit);
    layout->addRow(tr("Quantity"), m_quantitySpin);
    layout->addRow(tr("Unit Price"), m_unitPrice);
    layout->addRow(tr("Total Price"), m_totalPrice);

    hbox->addStretch();
    hbox->addWidget(m_submitButton);
    hbox->addWidget(m_cancelButton);

    vbox->addLayout(layout);
    vbox->addLayout(hbox);

    setLayout(vbox);

    // connections
    connect (m_unitPrice, SIGNAL(valueChanged(double)), this, SLOT(updateTotal()));
    connect (m_quantitySpin, SIGNAL(valueChanged(int)), this, SLOT(updateTotal()));
    connect (m_submitButton, SIGNAL(pressed()), this, SLOT(submit()));
    connect (m_cancelButton, SIGNAL(pressed()), this, SLOT(close()));
}

void OrderForm::setOrder(Order* prod)
{
    prod->setName(m_nameEdit->text());
    prod->setDateAdded(m_dateEdit->date());
    prod->setQuantity(m_quantitySpin->value());
    prod->setPrice(m_unitPrice->value());
}

void OrderForm::updateTotal()
{
    m_totalPrice->setValue(m_unitPrice->value() * m_quantitySpin->value());
}

void OrderForm::submit()
{
    if(m_nameEdit->text() == "") {
        QMessageBox msgBox;
        msgBox.setWindowTitle("dude.");
        msgBox.setText("Please enter name.");
        msgBox.exec();
        return;
    }
    setOrder(m_Order);
    QMessageBox msgBox;
    msgBox.setText(m_Order->toString());
    msgBox.exec();
}
