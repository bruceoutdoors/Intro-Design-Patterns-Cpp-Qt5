#include "blackjack.h"
#include "ui_blackjack.h"
#include "carddeck.h"
#include "cardhand.h"

#include <QDebug>
#include <QMessageBox>

static const int MAX_COLUMN = 2;

BlackJack::BlackJack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BlackJack)
{
    ui->setupUi(this);
    deck = new CardDeck();

    // initialize card hands as null pointers
    playerHand = nullptr;
    dealerHand = nullptr;

    // connect QActions with Toolbar buttons
    ui->tb_newGame->setDefaultAction(ui->actionNewGame);
    ui->tb_dealHand->setDefaultAction(ui->actionDeal_Hand);
    ui->tb_shuffleDeck->setDefaultAction(ui->actionShuffle_Deck);
    ui->tb_hit_me->setDefaultAction(ui->actionHit_Me);
    ui->tb_stay->setDefaultAction(ui->actionStay);

    // connect QActions with proper slots
    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui->actionDeal_Hand, SIGNAL(triggered()), this, SLOT(dealHand()));
    connect(ui->actionShuffle_Deck, SIGNAL(triggered()), this, SLOT(shuffleDeck()));
    // new signal slot syntax:
    connect(ui->actionHit_Me, &QAction::triggered, this, &BlackJack::hitMe);
    connect(ui->actionStay, &QAction::triggered, this, &BlackJack::stay);

    // start!
    dealHand();
}

void BlackJack::newGame()
{
    qDebug() << "new game";

    ui->sb_dealerScore->setValue(0);
    ui->sb_playerScore->setValue(0);

    shuffleDeck();
    dealHand();
}

void BlackJack::dealHand()
{
    qDebug() << "Deal hand...";
    ui->actionDeal_Hand->setDisabled(true);

    // if disabled by handOver() set enabled
    ui->actionHit_Me->setEnabled(true);
    ui->actionStay->setEnabled(true);

    // if already instantiated, delete to prevent memory leak
    if(playerHand != nullptr || dealerHand != nullptr) {
        delete playerHand;
        delete dealerHand;
        playerHand = nullptr;
        dealerHand = nullptr;
    }

    if(deck->count() <= 4) {
        qDebug() << "insufficient amount of cards...";
        shuffleDeck();
    }

    playerHand = deck->deal(2);
    dealerHand = deck->deal(2);

    refreshImages(playerHand, images_player, ui->layout_player);
    refreshImages(dealerHand, images_dealer, ui->layout_dealer);

    qDebug() << "player hand: " << playerHand->toString();
    qDebug() << QString("dealer hand: %1 thus value of %2")
                .arg(dealerHand->toString())
                .arg(dealerHand->getValue());

    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
}

void BlackJack::shuffleDeck()
{
    qDebug() << "shuffling deck...";
    deck->shuffleDeck();
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
}

void BlackJack::hitMe()
{
    if(deck->count() <= 1) {
        qDebug() << "insufficient amount of cards...";
        shuffleDeck();
    }
    qDebug() << "Adding card...";
    playerHand->append(deck->last());
    deck->removeLast();
    qDebug() << "playerHand now has " << playerHand->toString();
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
    refreshImages(playerHand, images_player, ui->layout_player);
}

void BlackJack::stay()
{
    qDebug() << "Now dealer's turn...";
    // dealer takes as many cards to not exceed 18
    while(dealerHand->getValue() <= 18) {
        dealerHand->append(deck->last());
        qDebug() << "Dealer adds a card: " << deck->last()->toString();
        deck->removeLast();
    }
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
    refreshImages(dealerHand, images_dealer, ui->layout_dealer);
    handOver();
    ui->actionDeal_Hand->setEnabled(true);
}

void BlackJack::refreshImages(CardHand *hand, QList<QLabel*> &labels, QGridLayout *layout)
{
    if(!labels.isEmpty()) {
        qDeleteAll(labels);
        labels.clear();
    }

    labels = hand->getLabels();
    for(int i = 0; i < labels.count(); i++) {
        layout->addWidget(labels[i], i/MAX_COLUMN, i%MAX_COLUMN, 1, 1);
    }
}

void BlackJack::handOver()
{
    qDebug() << "Player's hand is now " << playerHand->getValue();
    qDebug() << "dealer's hand is now " << dealerHand->getValue();

    ui->actionHit_Me->setDisabled(true);
    ui->actionStay->setDisabled(true);

    QMessageBox msgBox;

    // if dealer gets 21, dealer wins automatically
    if(dealerHand->getValue() == 21) {
        msgBox.setText("Dealer gets 21. Dealer wins!");
        msgBox.exec();
        ui->sb_dealerScore->setValue(ui->sb_dealerScore->value() + 1);
        return;
    }

    // if player exceeds 21, gets busted and loose
    if(playerHand->getValue() > 21) {
        msgBox.setText("You exceeded 21 thus have lost!");
        msgBox.exec();
        ui->sb_dealerScore->setValue(ui->sb_dealerScore->value() + 1);
        return;
    }

    // if dealer exceeds 21, gets busted and loose
    if(dealerHand->getValue() > 21) {
        msgBox.setText("Dealer exceeds 21. You win!");
        msgBox.exec();
        ui->sb_playerScore->setValue(ui->sb_playerScore->value() + 1);
        return;
    }

    // if player gets 21, hits blackjack and wins
    if(playerHand->getValue() == 21) {
        msgBox.setText("BlackJack! :D");
        msgBox.exec();
        ui->sb_playerScore->setValue(ui->sb_playerScore->value() + 1);
        return;
    }

    // if player draws 5 cards, wins
    if(playerHand->count() >= 5) {
        msgBox.setText("5 cards?? You win!");
        msgBox.exec();
        ui->sb_playerScore->setValue(ui->sb_playerScore->value() + 1);
        return;
    }

    // if dealer >= player, dealer wins
    if(dealerHand->getValue() >= playerHand->getValue()) {
        msgBox.setText("Dealer hand equal or exceeds player hand. Dealer Wins!");
        msgBox.exec();
        ui->sb_dealerScore->setValue(ui->sb_dealerScore->value() + 1);
    } else {
        // if player > dealer, player wins
        msgBox.setText("Player hand exceeds dealer. Player wins!");
        msgBox.exec();
        ui->sb_playerScore->setValue(ui->sb_playerScore->value() + 1);
    }
}

BlackJack::~BlackJack()
{
    delete playerHand;
    delete dealerHand;
    delete deck;
    delete ui;
}
