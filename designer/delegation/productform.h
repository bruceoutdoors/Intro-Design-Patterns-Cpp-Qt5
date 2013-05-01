#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H
//start
#include <QDialog>
class Product;
class Ui_ProductForm;
class QWidget;
class QAbstractButton;

/**  Example ui integration with Designer -
     using delegation by pointer. */
class ProductForm : public QDialog {
        Q_OBJECT
public:
    explicit ProductForm(Product* product = 0, QWidget* parent=0); /* Mark
       explicit to avoid implicit conversions between pointers!  */
    void setModel(Product* model);

public slots:
    void accept();
    void commit();
    void update();

private:
    Ui_ProductForm *m_ui;
    Product* m_model;
};
//end
#endif        //  #ifndef PRODUCTFORM_H
