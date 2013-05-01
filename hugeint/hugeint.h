#ifndef _HUGE_INT_H_
#define _HUGE_INT_H_

class HugeInt {
 public:
    HugeInt();
    HugeInt(long num);
    HugeInt(const HugeInt& hi);
    ~HugeInt();
    void set(const char* digits);
    void set(long num);
    void show(bool newLine = false) const;
    // other useful member functions
 private:
    int* m_DigitArray;
    int m_Size;
};
#endif

