#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

#include <cstdlib>
#include "shoppinglist.h"

void loadShoppingList(ShoppingList& slst) {

    bool ok;
    QString dept, item, qty, more;
    QStringList dptlst, yesno;
    dptlst << "Dairy" << "Meats" << "Produce"
           << "Frozen Foods" << "Household"
           << "Canned Goods" << "Spices";
    yesno << "yes" << "no";
    do {
        dept = QInputDialog::
            getItem(NULL, "ShoppingListApp", "Dept:",
                    dptlst, 0, true, &ok);

        item = QInputDialog::
            getText(NULL, QString("ShoppingListApp"),
                    QString("Item:"), QLineEdit::Normal,
                    QString(), &ok);

        qty = QInputDialog::
            getText(NULL, "ShoppingListApp", "Qty:",
                    QLineEdit::Normal, QString(), &ok);

        slst << QString("%1 - %2 - {%3}").arg(dept)
            .arg(item).arg(qty);
        more = QInputDialog::
            getItem(NULL, "ShoppingListApp", "Another item? ",
                    yesno, 0, false, &ok);
    } while (more == "yes");
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    app.setQuitOnLastWindowClosed(false) ; /* this is necessary
      if there is no QMainWindow and we are opening/closing 
      dialogs. */

    ShoppingList shplst;
    loadShoppingList(shplst);
    qDebug() << "Send the following list to the printer:\n\n";
    qDebug() << shplst.makePrintList();
    return 0;
}

