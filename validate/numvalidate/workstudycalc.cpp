#include "inputform.h"
#include <QApplication>

int main(int argc, char** argv) {
  QApplication qapp(argc, argv);
  int ibot(5), itop(20);
  double dbot(6.50), dtop(25.00);
  InputForm iform(ibot, itop, dbot, dtop);
  iform.show();
  return qapp.exec();

}
