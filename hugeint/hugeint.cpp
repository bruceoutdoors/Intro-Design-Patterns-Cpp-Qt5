#include "hugeint.h"
#include <iostream>

HugeInt::HugeInt() : m_Size(0), m_DigitArray(0) {}

HugeInt::HugeInt(long num) {
    m_Size = 0;
    set(num);
}

void HugeInt::set(long num) {
    if (m_Size) 
        delete [] m_DigitArray;
    m_Size = 0;
    int num2 = num;
    while (num2) {
        ++m_Size;
        num2 /= 10;
    }
    m_DigitArray = new int [m_Size]; 
    for (int i = 0; i < m_Size; ++i) {
        m_DigitArray[i] = num % 10;
        num /= 10;
    }
}
//start
HugeInt::HugeInt(const HugeInt& hi) {
    m_Size = hi.m_Size;
    m_DigitArray = new int[m_Size];
    for (int i = 0; i < m_Size; ++i)
        m_DigitArray[i] = hi.m_DigitArray[i];
}

HugeInt::~HugeInt() {
    delete [] m_DigitArray;
}
//end
void HugeInt::show(bool newLine /*=false*/) const {
    using namespace std;
    for (int i = m_Size; i > 0; --i)
        cout << m_DigitArray[i-1];
    if (newLine)
        cout << endl;
}

/* Here we assume that digits is an array of numerical digits, 
   each between 0 and 9, with a terminating null char. */
void HugeInt::set(const char* digits) {
    if (m_Size) 
        delete [] m_DigitArray;
    for (m_Size = 0; digits[m_Size]; ++m_Size);
    m_DigitArray = new int[m_Size];
    for (int i = 0; i < m_Size; ++i) {
        if ('0' > digits[i] || digits[i] > '9') {
            //Design policy decision: What should we do here??
        }
        m_DigitArray[m_Size - i -1] = digits[i] - '0';
    }
}

