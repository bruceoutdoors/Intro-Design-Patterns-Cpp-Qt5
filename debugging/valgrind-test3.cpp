/** This program repairs some examples of the memory 
    leaks and other bad programming practices shown in vlgrind-test.cpp. */
#include <iostream>

int notSoBadPointer(int k) {
  int* ip = new int[3];
  ip[0] = k;  
  delete[] ip;                    /* Clean up memory leak. */
  return k;                       /* A returnable value. */
}  


int main() {
  using namespace std;
  int num(4), k(4);               /* At least k is no longer uninitialized. */
  int* iptr = new int[num] ;      /* No longer uninitialized pointer. */
  for (int i = 0; i < num; ++i)
     iptr[i] = i;
  cout << iptr[num-1] << endl;    /* No more trouble! */
  cout << notSoBadPointer(k) << endl;
  delete[] iptr;
}

