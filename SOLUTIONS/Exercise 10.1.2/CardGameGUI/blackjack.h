#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QMainWindow>
class CardDeck;
class CardHand;

namespace Ui {
class BlackJack;
}

class BlackJack : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BlackJack(QWidget *parent = 0);
    ~BlackJack();
    void handOver();
    
private slots:
    void newGame();
    void dealHand();
    void shuffleDeck();
    void hitMe();
    void stay();

private:
    Ui::BlackJack *ui;
    CardDeck *deck;
    CardHand *playerHand;
    CardHand *dealerHand;
};

#endif // BLACKJACK_H
