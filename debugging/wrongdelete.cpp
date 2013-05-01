void badpointer1(int* ip, int n) {
  ip = new int[n];
  delete ip;   /* Wrong delete syntax. */
}

int main() {
  int* iptr;
  int num(4);
  badpointer1(iptr, num); 
}

