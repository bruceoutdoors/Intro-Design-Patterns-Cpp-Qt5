#include <qstd.h>
using namespace qstd;

int i;   /* Global / Static */
static int j; /* File / Static */
extern int k; /* Global / Static */ 
const int l=10;  /* This is a file scope variable, but it might
not be stored anywhere, since it is easily optimized out by the
compiler. */
extern const int m=20;  /* Global / static */

class Point /* Global scope, but no storage class, since it is 
           not an object */
{
    public:
    QString name; /* class / various - all class scope 
    variables have various storage class, since it depends
    on how the containing objects were created. */
    QString toString() const;    
    private:
    static int count;
    int x, y;  /* class / various */
};

int Point::count = 0; /* Point::count has global scope, but
count by itself has class scope inside class Point. 
The object has static storage class. */

QString Point::toString() const {
    return QString("(%1,%2)").arg(x).arg(y);  /* class / various */
}

int main(int argc, char** argv) /* block / stack */
{
    int j;  /* block / stack */
    register int d;
    int* ip = 0;  /* block / stack */
    ip = new int(4);  /* no scope / heap - the object created 
       has no identifier, so it has no scope. However, it is
       in the heap storage class. */
    Point p; /* block / stack */
    Point* p2 = new Point(); /* no scope / heap */
}


