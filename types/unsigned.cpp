#include <iostream>
using namespace std;
int main() {
  unsigned u(500);
  int i(-2);
  if(u > i)
    cout << "u > i" << endl;
  else
    cout << "u <= i" << endl;
  cout << "i - u = " << i - u << endl;
  cout << "i * u = " << i * u << endl;
  cout << "u / i = " << u / i << endl;
  cout << "i + u = " << i + u << endl;
}
