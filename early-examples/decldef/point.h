class Point {                           /* Class head. */
 public:
    Point(int x, int y, int z);         /* A constructor declaration. */
    int distance(Point other);          /* A function declaration. */
    double norm() const {               /* Declaration and definition. */         
        return distance(Point(0,0,0));
    } 
 private:
    int m_Xcoord, m_Ycoord, m_Zcoord;   /* Data member declaration. */
};

