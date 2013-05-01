
#include <iostream>
#include <assert.h>
using namespace std;

// ChStack implementation with constructor.
const int DEFSIZE = 100;

class ChStack {
public:                                  //the public interface for the ADT ChStack
    explicit ChStack(int size):
    m_Maxlen(size), m_Top(EMPTY) {
        assert(size > 0);
        m_S = new char[size];
    }
    ChStack();                             // default constructor
    ChStack(const ChStack& str);           // copy constructor

    // domain transfer
    ChStack(int size, const char str[]);

    //destructor
    ~ChStack() {
        delete []m_S;
    }

    void reset() {
        m_Top = EMPTY;
    }                                      // mutator
    void push(char c) {
        m_S[++m_Top]= c;
    }                                      // mutator
    char pop() {
        return m_S[m_Top--];
    }                                      // mutator
    char top_of() const {
        return m_S[m_Top];
    }                                      //accessor
    bool isEmpty() const                   // accessor
    {
        return (m_Top == EMPTY);
    }

    bool isFull() const                    // accessor
    {
        return (m_Top == m_Maxlen - 1);
    }
private:
    enum  {EMPTY = -1};
    char*  m_S;                            //changed from m_S[maxlen]
    int    m_Maxlen;
    int    m_Top;
};

//default constructor for ChStack
ChStack::ChStack(): m_S(new char[DEFSIZE]),
m_Maxlen(DEFSIZE), m_Top(EMPTY) {}

//domain transfer




ChStack::ChStack(int size, const char str[])
        : m_Maxlen(size) {
    int i;
    assert(size > 0);
    m_S = new char[size];
    for (i = 0; i < m_Maxlen && str[i]; ++i)
        m_S[i] = str[i];
    m_Top = --i;
}