#ifndef __CIRCLE_H
#define __CIRCLE_H

#include <iostream>
#include <concepts>

template<typename T, typename U>
concept retval = requires (T a, U b) {
    {a.area()} -> std::convertible_to<double>;
    {b.area()} -> std::convertible_to<double>;

    // These work the same as above two
    // requires std::is_convertible_v<decltype(a.area()), double>;
    // requires std::is_convertible_v<decltype(b.area()), double>;
};

class Square;
const double pi{3.14159265358};

class Circle {
    public:
        Circle() = default;
        Circle(double r) : radius(r){}
        double area() const { return  pi * radius * radius; }
        double circum() const { return 2 * pi * radius; }
        
        template<typename T, typename U>
        requires retval<T, U>
        friend auto operator<=>(const T& lhs, const U& rhs);
        // friend auto operator<=>(const Square& s, const Circle& c);
        
        template<typename T, typename U>
        requires retval<T, U>
        friend inline bool operator==(const T& lhs, const U& rhs);
        // friend bool operator==(const Square& s, const Circle& c);

        template<typename T>
        requires std::is_convertible_v<T, double>
        inline auto operator<=>(const T& rhs){
            return (area() <=> rhs);
        }

        template<typename T>
        requires std::is_convertible_v<T, double>
        inline bool operator==(T rhs){
            return (area() == rhs);
        }
        
        friend inline std::ostream& operator<<(std::ostream& output, const Circle& c){
            output << "Circle[radius: " << c.radius << ", area: " << c.area()
            << ']';
            return output;
        }

    private:
        double radius{};
};

#endif  // __CIRCLE_H