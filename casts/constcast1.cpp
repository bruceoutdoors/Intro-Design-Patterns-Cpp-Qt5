#include <iostream>
using namespace std;

int main() {
    const int N = 22;
    int* pN = const_cast<int*>(&N);
    *pN = 33;
    cout << N << '\t' << &N << endl;
    cout << *pN << '\t' << pN << endl;
}
/*OUT
22      0xbf91cfa0
33      0xbf91cfa0 */