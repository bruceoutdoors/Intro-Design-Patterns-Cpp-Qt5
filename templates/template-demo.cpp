#include "fraction.h"
#include "complex.h"
#include <iostream>

//start id=power
template <class T> T power (T a, int exp) {
  T ans = a;
  while (--exp > 0) {
    ans *= a;
  }
  return (ans);
}
//end
//start id=main

int main() {
  Complex z(3,4), z1;
  Fraction f(5,6), f1;
  int n(19);
  z1 = power(z,3);              /* First instantiation: T is Complex. */
  f1 = power(f,4);              /* Second instantiation: T is Fraction. */
  z1 = power<Complex>(n, 4);    /* Supply an explicit template 
  parameter if the actual argument is not "specific" enough.
  This results in a call to a function that was already instantiated. */
  z1 = power(n,5);              /* Which version gets called? */

}
//end
