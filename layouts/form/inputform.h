#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QDialog>
class QLineEdit;
class QDateEdit;
class QPushButton;
class QDialogButtonBox;

class InputForm : public QDialog {
    Q_OBJECT
public:
    explicit InputForm(QWidget* parent = 0);
    void updateUi();
protected slots:
    void accept();
    void chooseColor();
private:
    QColor m_color;
    QLineEdit* m_name;
    QDateEdit* m_birthday;
    QPushButton* m_colorButton;
    QDialogButtonBox* m_buttons;
};

#endif // INPUTFORM_H
