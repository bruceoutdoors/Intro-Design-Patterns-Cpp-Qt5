#include <iostream>

class Point {
  public:
  Point(int px, int py)
       : m_X(px), m_Y(py) {}    /* _________ */

    void set(int nx, int ny) {
        m_X = nx;
        m_Y = ny;
    }
    void print() const {
        using namespace std;
        cout << "[" << m_X << "," << m_Y << "]";
        m_printCount ++;        /* _________ */
    }
  private:
    int m_X, m_Y;
    int m_printCount;           /* _________ */
};

int main() {
    Point p(1,1);
    const Point q(2,2);
    p.set(4,4);                 /* _________ */
    p.print();
    q.set(4,4);                 /* _________ */
    q.print();                  /* _________ */
    return 0;
}

/** 1. What are the errors?
    a. is not allowed here.
    b. m_pointCount is missing here causing a compiler error.
    c. missing semicolon in the {}.
    d. m_pointCount is missing here causing a runtime error.
    e. nothing is wrong.
Answer: d. integers need to be initialized.
2. What are the errors?
    a. nothing is wrong.
    b. m_printCount needs to be const.
    c. m_printCount needs to be explicit.
    d. compiler error - can't change m_printCount.
    e. m_printCount needs to be volatile.
Answer: d.
3. What is the error?
    a. Nothing is wrong.
    b. m_printCount needs to be volatile.
    c. m_printCount needs to be const.
    d. m_printCount needs to be mutable.
    e. m_printCount needs to be explicit.
Answer: d.
4. What are the errors?
    a. can't call const member.
    b. can't call non-const member.
    c. nothing is wrong.
    d. set needs to be const.
    e. set needs to be volatile.
Answer: c.
5. What are the errors?
    a. can't call const member
    b. can't call non-const member.
    c. set needs to be volatile.
    d. q needs to be non-const.
    e. set needs to be volatile.
Answer: b and d
6. What is the error?
    a. Nothing is wrong.
    b. can't call non-const member.
    c. print needs to be const.
    d. q needs to be explicit.
    e. can't call const member.
Answer: a. */
