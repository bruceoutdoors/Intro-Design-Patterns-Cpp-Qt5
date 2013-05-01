#include "static.h"
#include <iostream>

int Thing::s_Count = 0;        /* Must initialize static member! */

Thing::Thing(int a, int b)
        : m_First(a), m_Second(b) {
    ++s_Count;
}

Thing::~Thing() {
    --s_Count;
}

void Thing::display() const {
    using namespace std;
    cout << m_First << "$$" << m_Second;
}

void Thing::showCount() {      /* Static function. */
    using namespace std;
    cout << "Count = " << s_Count << endl;
}

