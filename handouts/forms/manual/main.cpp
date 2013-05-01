#include "order.h"
#include "orderform.h"
QTextStream cout(stdout);
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    OrderForm pf;
    Order order;
    order.setName("Modern Multithreading");
    order.setDateAdded(QDateTime::currentDateTime().date());
    order.setQuantity(1);
    pf.setOrder(&order);
    pf.show();
    int retval = app.exec();
    cout << order.toString() << endl;
    return retval;
}
