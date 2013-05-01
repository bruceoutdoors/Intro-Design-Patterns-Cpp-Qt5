#include <cstdlib>
//start
int look() {
    int i=0;
    for (i=0; i<10; ++i) {
        if (i == rand() % 20)
            goto found; /* It would be better to use
        break or continue. */
    }
    return -1;
found:                  /* goto serves as a forward declaration for a label. */
    return i;
}
//end

int main() {
    look();
}
