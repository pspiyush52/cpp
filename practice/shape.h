#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
#include <string>
#include <string_view>

class Shape {
    public:
        Shape() = default;
        inline Shape(const std::string_view Description):
            description(new std::string{Description}){ count++; }
        ~Shape() { delete description; }
        
        void draw() const {
            std::cout << "Shape::draw() called... Drawing " << *description << '\n';
        }
        static int shape_count(){ return count; }
    
    protected:
        std::string* description{};
        static inline int count{};
};

class Oval : public Shape {
    public:
        Oval() = default;
        Oval(double X_radius, double Y_radius, const std::string_view Description):
            Shape(Description), x_radius(X_radius), y_radius(Y_radius){}
        
        void draw() const {
            std::cout << "Oval::draw() called... Drawing " << *description
            << " with x radius: " << x_radius << " and y radius: " << y_radius << '\n';
        }
    
    protected:
        double get_x_radius() const { return x_radius; }
        double get_y_radius() const { return y_radius; }
    
    private:
        double x_radius{};
        double y_radius{};
};

class Circle : public Oval {
    public:
        Circle() = default;
        Circle(double radius, const std::string_view Description):
            Oval(radius, radius, Description){}
        
        void draw() const {
            std::cout << "Circle::draw() called... Drawing " << *description
            << " with a radius: " << this->get_x_radius() << '\n';
        }
        double get_radius() const { return this->get_x_radius(); }
};

#endif  // __SHAPE_H