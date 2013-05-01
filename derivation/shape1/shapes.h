#ifndef SHAPES_H
#define SHAPES_H

#include <QString>
//start id=shape
class Shape {                           /* An abstract base class. */
 public:
    virtual double area() = 0;          /* Pure virtual function. */
    virtual QString getName() = 0;
    virtual QString getDimensions() = 0;
    virtual ~Shape() {}
};
//end
//start id=derived
class Rectangle : public Shape {
 public:
    Rectangle(double h, double w) :
        m_Height(h), m_Width(w) {}
    double area();
    QString getName();
    QString getDimensions();

 protected:                             /* We want to access m_Height in Square class. */
    double m_Height, m_Width;
};

class Square : public Rectangle {
 public:
    Square(double h)
       : Rectangle(h,h)                 /* Base class
        name in member initialization list - pass arguments
        to base class ctor. */
    { }
    double area();
    QString getName();
    QString getDimensions();
};

class Circle : public Shape {
 public:
    Circle(double r) : m_Radius(r) {}
    double area();
    QString getName();
    QString getDimensions();
 private:
    double m_Radius;
};
//end
#endif        //  #ifndef SHAPES_H

