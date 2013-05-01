
#include <iostream>
using namespace std;

long x = 17; 
float y = 7.3;              /* Scope: ________________ */
static int z = 11;          /* Scope: ________________ */

class Thing {
    int m_Num;              /* Scope: ________________ */
public:
    static int s_Count;     /* Scope: ________________ */
    Thing(int n = 0) : m_Num(n) {++s_Count;}
    ~Thing() {--s_Count;}
    int getNum() { return m_Num; }
};

int Thing::s_Count = 0;
Thing t(11);

int fn(char c, int x) {     /* Scope: ________________ */
    int z = 5;              /* Scope: ________________ */
    double y = 6.933; 
    { char y;               /* Scope: ________________ */
    Thing z(4);             /* Scope: ________________ */
    y = c + 3; 
    ::y += 0.3;             /* Scope: ________________ */
    cout << y << endl;      /* Scope: ________________ */
    }
    cout << Thing::s_Count
         << endl;           /* Scope: ________________ */
    y /= 3.0;               /* Scope: ________________ */
    ::z++;                  /* Scope: ________________ */
    cout << y << endl;
    return x + z;
}

int main() {
    int x, y = 10; 
    char ch = 'B';          /* Scope: ________________ */
    x = fn(ch, y); 
    cout << x << endl; 
    cout << ::y << endl;    /* Scope: ________________ */
    cout << ::x / 2 << endl;
    cout << ::z << endl;
}

