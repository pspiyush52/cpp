#ifndef __SHAPES_H
#define __SHAPES_H

#include <iostream>
#include <cmath>

class Shape {
    public:
        Shape() = default;
        virtual void streamInsert(std::ostream&) const = 0;
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual ~Shape() {}
        friend std::ostream& operator<<(std::ostream& out, const Shape& s);
};
std::ostream& operator<<(std::ostream& out, const Shape& s) {
    s.streamInsert(out);
    return out;
}

class Circle : public Shape {
    static constexpr double PI{3.14159265358979};
    public:
        Circle(double r): radius{r} {}
        double area() const {
            return (PI * this->radius * this->radius);
        }
        double perimeter() const {
            return (2 * PI * this->radius);
        }
        double diameter() const {
            return (2 * this->radius);
        }
        void streamInsert(std::ostream& out) const {
            out << "<Cirle: r=" << this->radius << " @" << this << ">";
        }

    private:
        double radius;
};
class Triangle : public Shape {
    public:
        Triangle(double A, double B, double C): a{A}, b{B}, c{C} {}
        Triangle(double A): Triangle{A, A, A} {}
        double area() const {
            double S = (a + b + c) / 2;
            return std::sqrt(S * (S - a) * (S - b) * (S - c));
        }
        double perimeter() const {
            return (this->a + this->b + this->c);
        }
        void streamInsert(std::ostream& out) const {
            out << "<Triangle: (" << this->a << "," << this->b << "," << this->c << ") @" << this << ">";
        }

    private:
        double a;
        double b;
        double c;
};
class Rectangle : public Shape {
    public:
        Rectangle(double l, double b): length{l}, breadth{b} {}
        Rectangle(double lb): Rectangle{lb, lb} {}
        double area() const {
            return (this->length * this->breadth);
        }
        double perimeter() const {
            return (2 * (this->length + this->breadth));
        }
        void streamInsert(std::ostream& out) const {
            out << "<Rectangle: l=" << this->length << ", b=" << this->breadth << " @" << this << ">";
        }

    protected:
        double length;
        double breadth;
};
class Square : public Rectangle {
    public:
        Square(double side): Rectangle(side) {}
        void streamInsert(std::ostream& out) const {
            out << "<Square: s=" << this->length << " @" << this << ">";
        }
};

#endif  // __SHAPES_H