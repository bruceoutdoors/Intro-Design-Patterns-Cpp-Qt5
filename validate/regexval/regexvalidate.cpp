#include "rinputform.h"
#include <QApplication>

int main(int argc, char** argv) {
  QApplication qapp(argc, argv);
  RinputForm rxform;
  rxform.show();
  return qapp.exec();

}
