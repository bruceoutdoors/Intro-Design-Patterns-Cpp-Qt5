#include <iostream>
//start
int main()  {
    using namespace std;
    int y[] = {3, 6, 9};
    int x = 12;
    int* px;
    px = y;  /* y, or any array name, is an "alias" for a
        pointer to the first element in the array */
    cout << "What's next: " << *++px << endl;
    cout << "What's next: " << *++px << endl;
    cout << "What's next: " << *++px << endl;
    cout << "What's next: " << *++px << endl;
    return 0;
}
