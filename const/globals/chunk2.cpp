extern const int NN = 22;     // a different constant
extern const int MM;          // error
// declare global constant - storage allocated elsewhere
extern const int QQ;    // external declaration 
void newFunction() {
   int x = QQ + NN;
}


