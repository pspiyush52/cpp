#ifndef __SQUARE_H
#define __SQUARE_H

#include "circle.h"

class Square {
    public:
        Square() = default;
        Square(double Side) : side(Side){}
        double area() const { return side * side; }
        double perimeter() const { return 4 * side; }

        // comparisons b/w any two types which implement the area() method
        // which returns a type convertible to double
        template<typename T, typename U>
        requires retval<T, U>
        friend inline auto operator<=>(const T& lhs, const U& rhs){
            return (lhs.area() <=> rhs.area());
        }
        // Alt.:
        // friend inline auto operator<=>(const Square& s, const Circle& c){
        //     return (s.area() <=> c.area());
        // }

        // comparisons b/w any two types which implement the area() method
        // which returns a type convertible to double
        template<typename T, typename U>
        requires retval<T, U>
        friend inline bool operator==(const T& lhs, const U& rhs){
            return (lhs.area() == rhs.area());
        }
        // Alt.:
        // friend inline bool operator==(const Square& s, const Circle& c){
        //     return (s.area() == c.area());
        // }

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

        friend inline std::ostream& operator<<(std::ostream& output, const Square& s){
            output << "Square[side: " << s.side << ", area: " << s.area()
            << ']';
            return output;
        }

    private:
        double side{};
};

#endif  // __SQUARE_H