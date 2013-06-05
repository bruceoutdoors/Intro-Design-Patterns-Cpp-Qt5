#include "blackjack.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackJack w;
    w.show();

    return a.exec();
}
