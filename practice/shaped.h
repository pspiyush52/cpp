#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
#include <string>
#include <string_view>
/*
 * We mark the draw functions as virtual making it clear that we want dynamic
 * binding and that the function call should be resolved not by looking at the
 * pointer type but rather the type of the object whose address the pointer
 * stores.
 */
class Shape {
    public:
        Shape() = default;
        inline Shape(const std::string_view Description):
            description(new std::string{Description}){ count++; }
        Shape(const Shape& src) : description(new std::string{*src.description}){}
        ~Shape() { delete description; }
        
        virtual void draw() const {
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
        
        virtual void draw() const override {
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
            Oval(radius, radius, Description){};
        
        virtual void draw() const override {
            std::cout << "Circle::draw() called... Drawing " << *description
            << " with a radius: " << this->get_x_radius() << '\n';
        }
        double get_radius() const { return this->get_x_radius(); }
};

#endif  // __SHAPE_H