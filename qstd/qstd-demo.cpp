#include <qstd.h>
using namespace qstd; 

int main() {
    QString str;
    int qty;
    double price;
    QFile infile, outfile;
    promptOutputFile(outfile);   // qstd function
    QTextStream out(&outfile);     // connect stream to file.
    do {
        cout << "Enter item name please: " << flush;
        str = cin.readLine();
        out << str << '\n';
        cout << "Quantity: " << flush;
        qty = promptInt();
        out << qty << '\n';
        cout << "Unit price: " << flush;
        price = promptDouble();
        out << price << '\n';
    } while (more("item"));  // another qstd function.
    outfile.close();
    promptInputFile(infile);
    QTextStream in(&infile);
    while (! in.atEnd()) {
        str = in.readLine();
        cout << "item name:  " << str << endl;
        in >> qty;
        cout << "quantity: " << qty;
        in.skipWhiteSpace();
        in >> price;
        cout << "\tprice: " << price << endl;
        in.skipWhiteSpace();
    }
    infile.close();
    return 0;
}

