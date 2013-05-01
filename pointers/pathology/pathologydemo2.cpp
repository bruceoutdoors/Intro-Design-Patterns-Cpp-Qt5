#include <iostream>
using namespace std;
int main(){
  int a[] = {10, 11, 12, 13, 14, 15};

  int* b = a + 1;
  cout << "a[3] = " << a[3] << '\n'
       << "b[3] = " << b[3] << endl;

  //It gets even worse.
  int c = 123;
  int* d = &c;
  cout << "d[0] = " << d[0] << '\n'
       << "d[1] = " << d[1] << '\n'
       << "d[2] = " << d[2] << endl;

}
