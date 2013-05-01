#include <QTextStream>
#include <QRegExp>
#include <QString>

static QTextStream cout(stdout);
static QTextStream cin(stdin);

//start
QRegExp filtercharacters ("[\\s-\\+\\(\\)\\-]"); /* Remove these characters from the string that the user supplies. */

QRegExp usformat                                 /* All U.S. format numbers have country-code 1, and have 3 + 3 + 4 = 10 digits. Whitespaces, dashes and parantheses between these digit groups are ignored, but they help to make the digit groups recognizable. */
("(\\+?1[- ]?)?\\(?(\\d{3})\\)?[\\s-]?(\\d{3})[\\s-]?(\\d{4})");

QRegExp genformat
("(00)?([[3-9]\\d{1,2})(\\d{2})(\\d{7})$");      /* Landline country codes in Europe begin with 3 or 4, Latin America with 5, Southeast Asia and Oceania with 6, East Asia with 8, and Central, South and Western Asia with 9. Country codes may be 2 or 3 digits long. Local phone numbers typically have 2(or 3) + 2 + 7 = 11(or 12) digits. This program does not attempt to interpret city codes.*/

QRegExp genformat2
("(\\d\\d)(\\d\\d)(\\d{3})");                    /* The last 7 digits will be be arranged as  2 + 2 + 3. */


QString countryName(QString ccode) {
   if(ccode == "31") return "Netherlands";
   else if(ccode == "351") return "Portugal";
//end
   else if(ccode == "41") return "Switzerland";
   else if(ccode == "420") return "Czech Republic";
   else if(ccode == "56") return "Chile";
   else if(ccode == "595") return "Paraguay";
   else if(ccode == "62") return "Indonesia";
   else if(ccode == "680") return "Palau";
   else if(ccode == "86") return  "China";
   else if(ccode == "886") return "Taiwan";
   else if(ccode == "91") return "India";
   else if(ccode == "962") return "Jordan";
//start   
   //Add more codes as needed ..."
   else return "Unknown - but possibly valid";
}

QString stdinReadPhone() {                       /* Ensures the user-entered phone string complies with a regular expression, and extracts the proper components from it. Returns a properly formatted phone string. */
   QString str;
   bool knownFormat=false;
   do {                                          /* Keep asking until you get a valid number. */
      cout << "Enter a phone number (or q to quit): ";
      cout.flush();
      str = cin.readLine();
      if (str=="q")
         return str;
      str.remove(filtercharacters);              /* Remove all dashes, spaces, parens, and so on. */
      if (genformat.exactMatch(str)) {
         QString country = genformat.cap(2);
         QString citycode = genformat.cap(3);
         QString rest = genformat.cap(4);
         if (genformat2.exactMatch(rest)) {
            knownFormat = true;
            QString number = QString("%1-%2-%3")
                               .arg(genformat2.cap(1))
                               .arg(genformat2.cap(2))
                               .arg(genformat2.cap(3));
            str = QString("(%1) + %2 (0)%3-%4").arg(countryName(country))
                    .arg(country).arg(citycode).arg(number);
        }
     }
//end
     else if (usformat.exactMatch(str)) {
        knownFormat = true;
        QString areacode = usformat.cap(2);
        QString exchange = usformat.cap(3);
        QString number = usformat.cap(4);
        str = QString("(US/Canada) +1 %1-%2-%3")
                 .arg(areacode).arg(exchange).arg(number);
     }
//start
     if (not knownFormat) {
        cout << "Unknown format" << endl;
     }
  } while (not knownFormat) ;
  return str;
}

int main() {
    QString str;
    do {
        str =  stdinReadPhone();
        if (str != "q")
            cout << " validated: " << str << endl;
    } while (str != "q");
    return 0;
}
//end
