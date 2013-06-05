#include "carddeck.h"
#include <QtWidgets>
#include <QTextStream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QTextStream cout(stdout);    
    CardDeck deck;
    CardHand *hand;
    Card *aceCard = new Card(0, 0);
    cout << "image to acecard: " << aceCard->getImage() << endl;
    cout << "Deals to user 2 cards: " << flush;
    hand = deck.deal(2);
    cout << hand->toString() << endl;
    cout << "value of deal: " << hand->getValue() << endl;
    cout << "add ace card." << endl;
    hand->append(aceCard);
    cout << "now value of deal is: " << hand->getValue() <<endl;
    return 0;
}

