#include "stack.h"
#include <QString>
#include <qstd.h>
using namespace qstd;

int main() {
    Stack<QString> strs;
    strs.push("hic");
    strs.push("haec");
    strs.push("hoc");
//  strs.removeAt(2);  /* Error, inherited QList methods are private. */
    int n = strs.size();
    cout << n << " items in stack" << endl;
    for (int i = 0; i < n; ++i)
        cout << strs.pop() << endl;
}


