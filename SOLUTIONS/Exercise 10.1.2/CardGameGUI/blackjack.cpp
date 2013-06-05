#include "blackjack.h"
#include "ui_blackjack.h"

BlackJack::BlackJack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BlackJack)
{
    ui->setupUi(this);
}

BlackJack::~BlackJack()
{
    delete ui;
}
