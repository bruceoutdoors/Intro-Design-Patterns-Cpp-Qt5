#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QMainWindow>
class CardDeck;
class CardHand;
class QLabel;
class QGridLayout;

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
    // delete and read images
    void refreshImages(CardHand *hand, QList<QLabel *> &labels, QGridLayout *layout);
    
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
    QList<QLabel*> images_player;
    QList<QLabel*> images_dealer;
};

#endif // BLACKJACK_H
