#include "complex.h"

int main() {
    Complex c1 (4.5, 1.2);
    Complex c2 (3.6, 1.5);
    
    Complex c3 = c1 + c2;
    Complex c4 = c3 + 1.4; /* Right operand is promoted. */
    Complex c5 = 8.0 - c4; /* Left operand is promoted. */
    Complex c6 = 1.2 + c4; /* Error: left operand
        is not promoted for member operators. */
}
