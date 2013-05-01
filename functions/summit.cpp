#include <iostream>

int sumit(int num) {
    int sum = 0;
    for (; num ; --num)  /* The parameter gets reduced to 0. */
        sum += num;
    return sum;
}


int main() {
    using namespace std;
    int n = 10;
    cout << n  << endl;
    cout << sumit(n) << endl;
    cout << n << endl;  /* See what sumit() did to n. */
    return 0;
}
/*out
  10
  55
  10
*/

