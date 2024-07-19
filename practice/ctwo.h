#ifndef __CTWO_H
#define __CTWO_H

#include <iostream>
#include <type_traits>
#include <cmath>
#include "utils.h"

class Point {
    public:
        Point() = default;
        Point(double X, double Y) : x(X), y(Y){std::cout << *this << " constructed...\n";}
        Point(double x_y) : Point(x_y, x_y){}
        double length() const { return std::sqrt(x*x + y*y); }
        /*
            When we define a custom '<=>' operator, the compiler automatically
            generates the '<', '<=', '>', '>=' operators but the '==' operator
            has to be defined separately and if it is defined the compiler
            further generates the '!=' operator on its own.

            The type double supports partial ordering by default so we use
            partial_ordering as the return type for our spaceship operator
            function.

            We can define the '<=>' operator as a member function or as a free
            standing function, both will support implicit type conversions.
        */
        // std::partial_ordering operator<=>(const Point& p) const;
        auto operator<=>(const Point& p) const;
        /*
            If we want to make comparisons to the fundamental types as well
            then we have to define another function for the '<=>' operator
            which takes a variable of another type as an argument.

            So the below function will support expressions of the format,
                    p1 (Point) <=> rhs (numeric_type)
            
            We do not have to define another function to support the reverse
            order
                    lhs (numeric_type) <=> p1 (Point)
            since the compiler can flip the operands and get the desired
            result using the function we already implemented.
        */
        template<typename T>
        requires std::is_convertible_v<T, double>
        auto operator<=>(const T& rhs) const;

        // Defining operator '==' separately. '!=' will be generated
        // automatically. Supports implicit type conversion.
        bool operator==(const Point& rhs) const;
        
        template <typename T>
        requires std::is_convertible_v<T, double>
        friend bool operator==(const Point& lhs, const T& rhs);
        /*
            The implementation defined below is not required since the
            compiler automatically makes adjustments to use the above template
            by flipping operands if need be.

            template <typename T>
            requires std::is_convertible_v<T, double>
            friend bool operator==(const T& lhs, const Point& rhs);

            Using the above methods of defining '<=>' and '==' operators for
            two Point operands and one Point and one numeric operand we can
            implement all the logical operations which would otherwise require
            18 functions to implement.
        */
        friend std::ostream& operator<<(std::ostream& output, const Point& p);
    
    private:
        double x{};
        double y{};
};

auto Point::operator<=>(const Point& p) const {
    return (length() <=> p.length());
}

template<typename T>
requires std::is_convertible_v<T, double>
auto Point::operator<=>(const T& rhs) const {
    return (length() <=> rhs);
}

bool Point::operator==(const Point& rhs) const {
    return (this->length() == rhs.length());
}

template <typename T>
requires std::is_convertible_v<T, double>
inline bool operator==(const Point& lhs, const T& rhs){
    return (lhs.length() == rhs);
}
/*
template <typename T>
requires std::is_convertible_v<T, double>
inline bool operator==(const T& lhs, const Point& rhs){
    return (lhs == rhs.length());
}
*/
inline std::ostream& operator<<(std::ostream& output, const Point& p){
    output << "Point[x: " << p.x << ", y: " << p.y << ", length: "
    << p.length() << ']';
    return output;
}

#endif  // __CTWO_H