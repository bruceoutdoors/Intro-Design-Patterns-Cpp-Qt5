#include <QTextStream>
#include <cmath>

int main() {
   QTextStream cout(stdout);
   QTextStream cin(stdin);
   int num(0), root(0), count;
   cout << "How many perfect squares? "<< flush;
   cin >> count;
   for(num = 0;; ++num) {
      root = sqrt(num);  /* Convert sqrt to int. */
      if(root * root != num) 
         continue;
      cout << num << endl;
      --count;
      if(count == 0) 
         break;
   }
}

