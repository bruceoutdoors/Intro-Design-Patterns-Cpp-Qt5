#include <iostream>
using namespace std;

bool test(int x, int y)
{ return x / y; }

int main()
{ int m = 17, n = 18;
  cout << test(m,n) << endl;
  cout << test(n,m) << endl;
  m += n;
  n /= 5;
  cout << test(m,n) << endl;
}

