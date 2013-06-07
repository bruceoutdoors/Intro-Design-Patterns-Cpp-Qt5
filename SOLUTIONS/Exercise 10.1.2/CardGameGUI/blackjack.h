#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QMainWindow>
class CardDeck;
class CardHand;
class QLabel;
class QGridLayout;
class QSpinBox;

namespace Ui {
class BlackJack;
}

class BlackJack : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BlackJack(QWidget *parent = 0);
    ~BlackJack();
    
private slots:
    void newGame();
    void dealHand();
    void shuffleDeck();
    void hitMe();
    void stay();

private:
    void handOver();
    // delete and read images
    void refreshImages(CardHand *hand, QGridLayout *layout);
    void finalDecision(QString message, QSpinBox *spinbox, int score = 1);

    Ui::BlackJack *ui;
    CardDeck *deck;
    CardHand *playerHand;
    CardHand *dealerHand;
};

#endif // BLACKJACK_H
