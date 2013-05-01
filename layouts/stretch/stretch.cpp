#include <QApplication>

#include "cardtable.h"

int main(int argc, char* argv[]) {
	QApplication app (argc, argv);
	CardTable ct;
	ct.show();
	return app.exec();


}
