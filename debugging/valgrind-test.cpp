/** This program contains some examples of memory 
    leaks and other bad programming practices. */
#include <iostream>

int badpointer2(int k) {
  int* ip = new int[3];
  ip[0] = k;
  return ip[3];                   /* Out of bounds index */
}                                 /* Memory leak: allocated memory is no longer accessible. */


int main() {
  using namespace std;
  int* iptr;                      /* iptr is uninitialized. */
  int num(4), k;                  /* k is uninitialized. */
  cout << iptr[num-1] << endl;    /* What is the state of iptr? */
  cout << badpointer2(k) << endl; /* Sending uninitialized arg to function. */
}

