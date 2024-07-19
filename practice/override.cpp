/*
 * The override identifier is specifyies that a virtual function overrides
 * another virtual function.
 * 
 * Whenever the override identifier appears after a function declaration it
 * specifies that the function is an overridden version. The compiler checks
 * to see if the base class contains a virtual function with the exact same
 * signature, and if there is not, it will result in a compiler error.
 * 
 * It is a mechanism to prevent mistakes while overriding class methods.
 */
#include <iostream>
#include <string>
#include <string_view>

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
        /*
         * Specifying virtual override after the function declaration makes
         * the compiler look at the base class to check if there is a virtual
         * function with the exact same signature or not. In this case there
         * is a virtual function in the base class with the same signature so
         * the code will pass compilation.
         */
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