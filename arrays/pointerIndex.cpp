#include <iostream>
using namespace std;

int main()  {
    int x = 23;
    int y = 45;
    int* px = &x;
    cout << "px[0] = " << px[0] << endl;
    cout << "px[1] = " << px[1] << endl;
    cout << "px[2] = " << px[2] << endl;      
    cout << "px[-1] = " << px[-1] << endl;
    return 0;
}
/*OUT
// g++ on Mac OSX:
px[0] = 23
px[1] = 1606413624
px[2] = 32767
px[-1] = 45

// g++ on Linux (Ubuntu):
px[0] = 23
px[1] = -1219095387
px[2] = -1216405456
px[-1] = 45

// g++ on Windows XP (mingw)
px[0] = 23
px[1] = 45
px[2] = 2293588
px[-1] = 2009291924

// Windows XP with MS Visual Studio compiler:
px[0] = 23
px[1] = 45
px[2] = 1245112
px[-1] = 1245024
*/

