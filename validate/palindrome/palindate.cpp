#include "palindate.h"

Palindate::Palindate(QObject* parent) : QValidator(parent) {
}   

/** Returns Acceptable if input string, ignoring case, whitespace, and 
punctuation is a palindrome - otherwise returns Intermediate. 
*/
//start
QValidator::State Palindate::validate(QString& str, int& ) const {
   QString inpStr(str.toLower());
   QString skipchars("-_!,;. \t");
   foreach(QChar ch, skipchars) 
      inpStr = inpStr.remove(ch);       /* You could do this faster with a regex. */
   QString revStr;                      /* Surprising there is no reverse() function. */
   for(int i=inpStr.length(); i > 0; --i) 
      revStr.append(inpStr[i-1]);
   if(inpStr == revStr) 
      return Acceptable;
   else
      return Intermediate;
}
