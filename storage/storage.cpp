
#include <QString>


int i;                              /* Scope: ______________   Storage class: ____________ */
static int j;                       /* Scope: ______________   Storage class: ____________ */
extern int k;                       /* Scope: ______________   Storage class: ____________ */
const int l=10;                     /* Scope: ______________   Storage class: ____________ */
extern const int m=20;              /* Scope: ______________   Storage class: ____________ */

class Point                         /* Scope: ______________   Storage class: ____________ */
{
    public:
    QString name;                   /* Scope: ______________   Storage class: ____________ */
    QString toString() const;
    private:
    static int count;
    int x, y;                       /* Scope: ______________   Storage class: ____________ */
};

int Point::count = 0;               /* Scope: ______________   Storage class: ____________ */

QString Point::toString() const {
    return QString("(%1,%2)").arg(x).arg(y); 
                                    /* Scope: ______________   Storage class: ____________ */
}

int main(int argc, char** argv)     /* S/SC of argc and argv: _________________*/
{
    int j;                          /* Scope: ______________   Storage class: ____________ */
    register int d;
    int* ip = 0;                    /* Scope: ______________   Storage class: ____________ */
    ip = new int(4);                /* Scope: ______________   Storage class: ____________ */
    Point p;                        /* Scope: ______________   Storage class: ____________ */
    Point* p2 = new Point();        /* Scope: ______________   Storage class: ____________ */
}


