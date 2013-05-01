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
  int* iptr;                      /* Uninitialized pointer! */
  int num(4), k(4);               /* At least k is no longer uninitialized. */
  cout << iptr[num-1] << endl;    /* Here's trouble! */
  cout << notSoBadPointer(k) << endl;
}

