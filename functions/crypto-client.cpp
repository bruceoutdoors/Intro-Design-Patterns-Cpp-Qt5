#include <QTextStream>
#include "crypto.h"

int main()  {
   QTextStream cout(stdout);
   QString str1 ("asdfghjkl;QWERTYUIOP{}}|123456&*()_+zxcvnm,,, ./?"), 
           str2;
   cout << "Original string: " << str1 << endl;
   cout << "length: " << str1.length() << endl;
   QString seqstr("pspsp");
   ushort key(12579);
   Crypto crypt(key, seqstr);
   str2 = crypt.encrypt(str1);
   cout << "Encrypted string: " << str2 << endl;
   cout << "Recovered string: " << crypt.decrypt(str2) << endl;
}


