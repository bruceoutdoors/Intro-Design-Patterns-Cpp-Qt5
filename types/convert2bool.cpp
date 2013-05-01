#include <iostream>
using namespace std;

int main() {
   int j(5);
   int* ip(&j);
   int* kp(0);
   double y(3.4);
   if(y)
      cout << "y looks like true to me!" << endl;
   else
      cout << "y looks like false to me!" << endl;
   cout << "ip looks like " << (ip ? "true" : "false") << endl;
   cout << "kp looks like " << (kp ? "true" : "false") << endl;
   while(--j) {
      cout << j << '\t';
   }
   cout << endl;
}

