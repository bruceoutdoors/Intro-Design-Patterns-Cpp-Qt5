const int NN = 10;      // file scope
const int MM = 44;      // file scope
extern const int QQ = 7; // can be accessed from other files   

int main() {
// NN = 12;        // error
   int array[NN];  // okay
// QQ++;           // error
   double darray[QQ];
   return 0;
}

