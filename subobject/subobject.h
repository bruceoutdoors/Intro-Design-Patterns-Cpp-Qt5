#ifndef SUBOBJECT_H
#define SUBOBJECT_H
#include <QTextStream>

QTextStream cout(stdout);

//start
class Point {
 public:
    Point(int xx, int yy) : m_x(xx), m_y(yy){}
    ~Point() {
       cout << "point destroyed: ("
            << m_x << "," << m_y << ")" << endl;
    }
 private:
    int m_x, m_y;
};

class Square {
 public:
    Square(int ulx, int uly, int lrx, int lry)
    : m_UpperLeft(ulx, uly), m_LowerRight (lrx, lry)  /* Member initialization
    is required here because there is no default ctor. */
    {}

    Square(const Point& ul, const Point& lr) :
    m_UpperLeft(ul), m_LowerRight(lr) {}              /* Initialize members
        using the implicitly generated Point copy ctor. */
 private:
    Point m_UpperLeft, m_LowerRight;                  /* Embedded subobjects. */
};

//end
#endif        //  #ifndef SUBOBJECT_H
