#include <QApplication>
#include "palindromeform.h"

int main(int argc, char** argv) {
  QApplication qapp(argc, argv);
  PalindromeForm palform;
  palform.show();
  return qapp.exec();

}
