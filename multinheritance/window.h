#include "color.h"
#include "point.h"
//start id=base
class Rectangle {
 public:
    Rectangle( Const Point& ul, int length, int width);
    Rectangle( const Rectangle& r) ;
    void move (const Point &newpoint);
 private:
    Point m_UpperLeft;
    int m_Length, m_Width;
};

class ScreenRegion {
 public:
    ScreenRegion( Color c=White);
    ScreenRegion (const ScreenRegion& sr);
    virtual color Fill( Color newColor) ;
    void show();
    void hide();
 private:
    Color m_Color;
    // other members...
    
};

class Window: public Rectangle, public ScreenRegion {
 public:
    Window( const Point& ul, int len, int wid, Color c)
        : Rectangle(ul, len, wid), ScreenRegion(c) {} /* Use base class ctors. */

    Window( const Rectangle& rect, const ScreenRegion& sr)
        : Rectangle(rect), ScreenRegion(sr) {}        /* Use base class copy ctors. */
             
    // Other useful member functions ...
};
//end
