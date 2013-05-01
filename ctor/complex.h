#include <string>
using namespace std;

class Complex {
 public:
    Complex(double realPart, double imPart);
    Complex(double realPart);
    Complex();
    string toString() const;
 private:
    double m_R, m_I;
};

