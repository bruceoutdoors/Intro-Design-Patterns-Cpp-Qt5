#ifndef THING_H_
#define THING_H_

class Thing {
 public:
    void set(int num, char c);
    void increment();
    void show();
 private:
    int m_Number;
    char m_Character;
};
#endif

