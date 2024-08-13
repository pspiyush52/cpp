#ifndef __POLYGON_H
#define __POLYGON_H

#include <cmath>
#include <iostream>

class Polygon {
    public:
        virtual int getNSides() const final {
            return this->numberOfSides;
        }
        virtual double area() const = 0;
        virtual double perimeter() const final {
            double p{};
            for (int i{}; i < this->numberOfSides; ++i)
                p += this->sides[i];
            return p;
        }
        virtual int numOfDiagonals() const final {
            return static_cast<int>((this->numberOfSides * (this->numberOfSides - 3)) / 2);
        }
        virtual ~Polygon() {
            if (this->sides) {
                delete[] this->sides;
                this->sides = {};
                this->numberOfSides = {};
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const Polygon& P) {
            P.streamInsert(out);
            return out;
        }
    
    protected:
        Polygon(int numOfSides) {
            if (numOfSides > 2) {
                this->sides = new double[numOfSides];
                this->numberOfSides = numOfSides;
            }
        }
        void setNSide(int sideIndex, double length) {
            this->sides[sideIndex] = length;
        }
        double getNSide(int sideIndex) const {
            return this->sides[sideIndex];
        }
        virtual void streamInsert(std::ostream& out) const = 0;

    private:
        double* sides{};
        int numberOfSides;
};

class Triangle : public Polygon {
    public:
        Triangle(double x, double y, double z): Polygon(3) {
            this->setNSide(0, x);
            this->setNSide(1, y);
            this->setNSide(2, z);
        }
        double area() const {
            double S = (this->getNSide(0) + this->getNSide(1) + this->getNSide(2)) / 2;
            return std::sqrt(S * (S - this->getNSide(0)) * (S - this->getNSide(1)) * (S - this->getNSide(2)));
        }
        bool isEquilateral() const {
            return (this->getNSide(0) == this->getNSide(1) && this->getNSide(0) == this->getNSide(2));
        }
        bool isIsosceles() const {
            return (
                this->getNSide(0) == this->getNSide(1) ||
                this->getNSide(1) == this->getNSide(2) ||
                this->getNSide(0) == this->getNSide(2)
            );
        }
    
    protected:
        virtual void streamInsert(std::ostream& out) const {
            out 
                << "<Triangle@" << this 
                << "(" << getNSide(0) 
                << ", " << getNSide(1)
                << ", " << getNSide(2)
                << ")>";
        }
};

class Quadrilateral : public Polygon {
    public:
        Quadrilateral(double x, double y, double z, double w): Polygon(4) {
            this->setNSide(0, x);
            this->setNSide(1, y);
            this->setNSide(2, z);
            this->setNSide(3, w);
        }
        double area() const {
            return 0;
        }
    
    protected:
        virtual void streamInsert(std::ostream& out) const {
            quadPrint(out, "Quadrilateral");
        }
        void quadPrint(std::ostream& out, const char* name) const {
            out
                << name << "@" << this
                << "(" << getNSide(0)
                << ", " << getNSide(1)
                << ", " << getNSide(2)
                << ", " << getNSide(3)
                << ")>";
        }
};
class Parallelogram : public Quadrilateral {
    public:
        Parallelogram(double x, double y):
            Quadrilateral(x, y, x, y) {}

    protected:
        virtual void streamInsert(std::ostream& out) const {
            quadPrint(out, "Parallelogram");
        }
};
class Rhombus : public Parallelogram {
    public:
        Rhombus(double x): Parallelogram(x, x) {}

    protected:
        virtual void streamInsert(std::ostream& out) const {
            quadPrint(out, "Rhombus");
        }
};
class Rectangle : public Parallelogram {
    public:
        Rectangle(double x, double y): Parallelogram(x, y) {}
        virtual double area() const {
            return this->getNSide(0) * this->getNSide(1);
        }
    
    protected:
        virtual void streamInsert(std::ostream& out) const {
            quadPrint(out, "Rectangle");
        }
};
class Square : public Rectangle {
    public:
        Square(double x) : Rectangle(x, x) {}
    
    protected:
        virtual void streamInsert(std::ostream& out) const {
            quadPrint(out, "Square");
        }
};

#endif  // __POLYGON_H