#include <iostream>
using namespace std;

void foo(int n) {
  cout << n << " is a nice number." << endl;
}


int main() {
   cout << "before call: " << 5 << endl;
   foo(5);
   cout << "before call: " << 6.7 << endl;
   foo(6.7);
   cout << "before call: " << true << endl;
   foo(true);
}
