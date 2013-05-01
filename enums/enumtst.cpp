#include <iostream>
using namespace std;

int main(int, char** ) {
    enum Signal { off, on } sig;            /* A new type, 2 new enum identifiers,
                           and a variable definition all in one line. */
    sig = on;
    enum Answer { no, yes, maybe = -1 };    /* Just the type/enum definitions. */
    Answer ans = no;                        /* An instance of an enum. */
//    enum Neg {no,false} c;                /* Illegal redefinitions of identifiers. */
    enum { lazy, hazy, crazy } why;         /* An unnamed enum variable. */
    int  i, j = on;                         /* An enum can always convert to int. */
    sig = off;  
    i = ans; 
//  ans = s                                 /* Conversions between enum types cannot be done implicitly. */
    ans = static_cast<Answer>(sig);         /* Conversion is okay with a cast. */
    ans = (sig ? no : yes); 
    sig = static_cast<Signal>(9);           /* Bad news! */
    Signal sig2(sig);                       /* Have we added an unnamed enumerator? */
    why = hazy;
    cout << "sig2, ans, i, j, why "
         << sig2 << ans << i << j << why << endl;
    return 0;
}

/*OUT
src/enums> ./enums
sig2, ans, i, j, why 91011
src/enums>
*/

