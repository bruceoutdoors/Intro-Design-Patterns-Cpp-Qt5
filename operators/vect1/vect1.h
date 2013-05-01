#ifndef VECT1_H
#define VECT1_H

#include  <iostream>
#include  <assert.h>

using namespace std;
//start
class Vect {
public:
    explicit Vect(int n = 10);
    ~Vect() {
        delete []m_P;
    }
    int& operator[](int i) {   /* Access m_P[i].  */
        assert (i >= 0 && i < m_Size);
        return m_P[i];
    }
    int  ub() const {
        return (m_Size - 1);
    }                          /* Upper bound. */
private:
    int*  m_P;
    int   m_Size;
};

Vect::Vect(int n) : m_Size(n) {
    assert(n > 0);
    m_P = new int[m_Size];
}
//end
#endif    
