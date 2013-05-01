#ifndef _RINPUT_FORM_H_
#define _RINPUT_FORM_H_

#include <QWidget>
#include <QRegExp>
#include <QString>

class QLineEdit;
class QLabel;
//start

class RinputForm : public QWidget {
    Q_OBJECT
 public:
    explicit RinputForm(QWidget* parent=0);
    void setupForm();
 public slots:
    void computeResult();
 private:
    QLineEdit* m_PhoneEntry;
    QLabel* m_PhoneResult;
    QString m_Phone;
    static QRegExp s_PhoneFormat;
};
//end
#endif

