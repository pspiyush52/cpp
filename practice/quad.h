#ifndef __QUAD_H
#define __QUAD_H

#include <iostream>

class Rectangle {
    public:
        Rectangle(double l, double b) : length(l), breadth(b){}
        double area() const { return (length * breadth); }
        double perimeter() const { return (2 * (length + breadth)); }
        auto operator<=>(const Rectangle& rhs){
            return (area() <=> rhs.area());
        }
        bool operator==(const Rectangle& rhs){
            return (area() == rhs.area());
        }
        friend std::ostream& operator<<(std::ostream& output, const Rectangle& r){
            output << "Rectangle[l: " << r.length << ", b: " << r.breadth << ']';
            return output;
        }
    
    protected:
        double length;
        double breadth;
};

class Square : public Rectangle {
    public:
        explicit Square(double side) : Rectangle(side, side){}
        friend std::ostream& operator<<(std::ostream& output, const Square& s){
            output << "Square[side: " << s.length << ']';
            return output;
        }
};

#endif  // __QUAD_H