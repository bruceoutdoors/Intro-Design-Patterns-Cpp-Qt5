#include <QApplication>
#include "masktestform.h"

int main(int argc, char** argv) {
  QApplication qapp(argc, argv);
  MaskTestForm mtform;
  mtform.show();
  return qapp.exec();

}
