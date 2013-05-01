/********************************************************************************
** Form generated from reading UI file 'actiontableeditor.ui'
** Originally named: ui_actiontableeditor.h
** Created: Sun Nov 28 21:06:16 2010
**    by: Qt User Interface Compiler version 4.7.1
********************************************************************************/

#ifndef UI_ACTIONTABLEEDITOR_H
#define UI_ACTIONTABLEEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE
//start
class Ui_ActionTableEditor
{
public:
  QVBoxLayout *verticalLayout;
  QTableView *m_tableView;
  QSpacerItem *verticalSpacer;
  QDialogButtonBox *m_buttonBox;

  void setupUi(QDialog *ActionTableEditor)
  {
    if (ActionTableEditor->objectName().isEmpty())
      ActionTableEditor->setObjectName(QString::
                                       fromUtf8("ActionTableEditor"));
    ActionTableEditor->resize(348, 302);
    verticalLayout = new QVBoxLayout(ActionTableEditor);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    m_tableView = new QTableView(ActionTableEditor);
    m_tableView->setObjectName(QString::fromUtf8("m_tableView"));
    verticalLayout->addWidget(m_tableView);
//end
    verticalSpacer = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    m_buttonBox = new QDialogButtonBox(ActionTableEditor);
    m_buttonBox->setObjectName(QString::fromUtf8("m_buttonBox"));
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons
                  (QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(m_buttonBox);


    retranslateUi(ActionTableEditor);
    QObject::connect(m_buttonBox, SIGNAL(accepted()), ActionTableEditor, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), ActionTableEditor, SLOT(reject()));

    QMetaObject::connectSlotsByName(ActionTableEditor);
  } // setupUi

  void retranslateUi(QDialog *ActionTableEditor)
  {
    ActionTableEditor->setWindowTitle(QApplication::
                    translate("ActionTableEditor", "Edit Actions", 0, QApplication::UnicodeUTF8));
  } // retranslateUi

};

namespace Ui {
  class ActionTableEditor: public Ui_ActionTableEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONTABLEEDITOR_H
