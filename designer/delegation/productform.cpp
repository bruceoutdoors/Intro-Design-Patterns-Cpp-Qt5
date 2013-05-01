
#include <QtGui>
#include "productform.h"
#include "ui_ProductForm.h"
#include "product.h"

ProductForm::ProductForm(Product* product, QWidget* parent)
: QDialog(parent), m_ui(new Ui::ProductForm),  m_model(product) {
    m_ui->setupUi(this); /* Populate the UI object with valid
    instances with properties set from values in the .ui file. */
    update();
}

void ProductForm::setModel(Product* p) {
    m_model =p;
}

void ProductForm::accept() {
    commit();
    QDialog::accept();  /* Closes the dialog. */
}

void ProductForm::commit() {
    if (m_model == 0) return;
    qDebug() << "commit()";
    m_model->setName(m_ui->nameLineEdit->text());
    QTextDocument* doc = m_ui->descriptionEdit->document();
    m_model->setDescription(doc->toPlainText());
    m_model->setDateAdded(m_ui->dateEdit->date());
    m_model->setPrice(m_ui->priceSpinbox->value());
}

void ProductForm::update() {
    if (m_model ==0) return;
    qDebug() << "update()";
    m_ui->nameLineEdit->setText(m_model->name());
    m_ui->priceSpinbox->setValue(m_model->price());
    m_ui->dateEdit->setDate(m_model->dateAdded());
    m_ui->descriptionEdit->setText(m_model->description());
}
