#include <iostream>
using namespace std;

class Snafu {
public:
    Snafu(int x) : mData(x) {}
    void showSum(Snafu & other) const {
        cout << mData + other.mData << endl; 
    }
  
private:
    int mData;
};

void foo(const Snafu & myObject1,
         const Snafu & myObject2) {
    // [ . . . ]  
    myObject1.showSum(myObject2);
}

int main() {

    Snafu myObject1(12345);
    Snafu myObject2(54321);

    foo(myObject1, myObject2);

}

