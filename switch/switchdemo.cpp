#include <QTextStream>
#include "usermanager.h"

QTextStream cout(stdout);
QTextStream cin(stdin);
enum  Choices {LOAD = 1, ADD, CHANGE, CHECK, SAVE, LIST, QUIT}; /* enums are
discussed in Chapter 19. */

// Function Prototypes
void addUsers(UserManager&);
void changePassword(UserManager&);
Choices menu();

//etc.

int main() {
  // some code omitted
  while (1) {
    switch (menu()) {                                           /* menu() obtains a value from the user. */
    case LOAD:  
      cout << "Reading from file ...\n"
	   << um.loadList() << " loaded to list"
	   << endl;
      break;
    case ADD:
      cout << "Adding users to the list ..." << endl;
      addUsers(um);
      break;
    case SAVE:
      cout << "Saving changes ...\n"
	   << um.saveList() << " users in file" << endl;
      break;
    case CHANGE:
      cout << "Changing password ..." << endl;
      changePassword(um);
      break;
    case CHECK:
      cout << "Checking a userid/pw combo ..." << endl;
      checkUser(um);
      break;
    case LIST:
      cout << "Listing users and passwords ...\n";
      um.listUsers();
      break;
    case QUIT:
      cout << "Exiting the program ..." << endl;
      return 0;
    default:
      cout << "Invalid choice! " << endl;
    }
  }
}
