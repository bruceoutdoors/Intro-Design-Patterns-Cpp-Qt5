#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QMainWindow>

namespace Ui {
class BlackJack;
}

class BlackJack : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BlackJack(QWidget *parent = 0);
    ~BlackJack();
    
private:
    Ui::BlackJack *ui;
};

#endif // BLACKJACK_H
