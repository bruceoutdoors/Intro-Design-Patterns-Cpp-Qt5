#include <iostream>
using namespace std;

int main() {
  int x(7), y = 11;
  char ch = 'B';
  double z(1.34);
  ch += x;
  cout << ch << endl;
  cout << y + z << endl;
  cout << x + y * z << endl;
  cout << x / y * z << endl;
}

