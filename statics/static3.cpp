#include "static3.h"
#include <iostream>

int Client::s_SavedID(1000);

int main() {
    Client cust1("George");
    cout << cust1.getID() << endl;
    cout << Client::getName() << endl;
}

