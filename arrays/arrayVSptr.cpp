#include <iostream>
using namespace std;

int main()  {
   int a[] = {12, 34, 56, 78};
   cout << a << "\t" << &a[1] - a << endl;
   int x = 99;
//   a = &x;
   int* pa;
   cout << pa << endl;
   pa = &x;
   cout << pa << "\t" << pa - &a[3] << endl;
   cout << a[4] << "\t" << a[5] << endl;
   cout << *(a + 2) << "\t" << sizeof(int) <<endl;
   void* pv = a;
   cout << pv << endl;
   int* pi = static_cast<int*>(pv);
   cout << *(pi + 2) << endl;
   return 0;
}

