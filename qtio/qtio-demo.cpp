#include <QDate>
#include <QFile>
#include <QTextStream>
//start
#include <qstd.h>

int main() {
    using namespace qstd;
    QDate d1(2002, 4,1), d2(QDate::currentDate());
    int days;
    cout << "The first date is: " << d1.toString()
            << "\nToday's date is: " 
            << d2.toString("ddd MMMM d, yyyy")<< endl;

    if (d1 <  d2)
        cout << d1.toString("MM/dd/yy") << " is earlier than " 
                << d2.toString("yyyyMMdd") << endl;

    cout << "There are " << d1.daysTo(d2) 
            << " days between "
            << d1.toString("MMM dd, yyyy") << " and " 
            << d2.toString(Qt::ISODate)  << endl;

    cout << "Enter number of days to add to the first date: " 
            <<  flush;
    days = promptInt();
    cout << "The first date was " << d1.toString()
            << "\nThe computed date is " 
            <<  d1.addDays(days).toString() << endl;
    cout << "First date displayed in longer format: "
            << d1.toString("dddd, MMMM dd, yyyy")  << endl;
//end
    cout << "\nNow we save the following dates to a file: \n"
           << d1 .toString() << '\t' << d2.toString() << endl;
    QFile outfile;
    promptOutputFile(outfile);
    QTextStream ofs (&outfile);
     ofs << d1.toString() << '\n';
     ofs << d2.toString() << '\n';
     outfile.flush();
     outfile.close();
     cout << "Now we read those dates from the file:\n";
     QFile infile;
     promptInputFile(infile);
     QTextStream ifstr(&infile);
     QString dateStr;
     QDate dt1, dt2;          // we use new variables
     dateStr = ifstr.readLine();
     dt1 = QDate::fromString(dateStr);
     dateStr = ifstr.readLine();
     dt2 = QDate::fromString(dateStr);
     cout << "Here are the dates we read from the file:\n"
             << dt1.toString() << '\n' 
             << dt2.toString() <<  endl;
     infile.close();
     return 0; 
}

