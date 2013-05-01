#include <string>
#include <iostream>

int main() {
    using namespace std;
    string s1("This "), s2("is a "), s3("string.");
    s1 += s2;  /* concatenation */
    string s4 = s1 + s3;
    cout << s4 << endl;
    string s5("The length of that string is: ");
    cout << s5 << s4.length() << " characters." << endl;
    cout << "Enter a sentence: " << endl;
    getline(cin, s2);  /* s2 will contain an entire line. */
    cout << "Here is your sentence: \n" << s2 << endl;
    cout << "The length of your sentence is: " << s2.length() << endl;
    return 0;
}

