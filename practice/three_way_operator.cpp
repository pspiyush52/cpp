#include <iostream>
#include <type_traits>
/*
    In C++20 if we implement the three way comparison operator for our class
    the compiler will automatically generate implementations for the '<',
    '<=', '>', '>=' operators.
*/
template <typename T = int>
requires std::is_convertible_v<T, double> && requires (T a){ requires sizeof(a) >= 2; }
class triple{
    public:
        triple() = default;
        triple(T x, T y, T z) : a(x), b(y), c(z){}
        triple(T num) : triple(num, num, num){}
        /*
            The compiler automatically generates the '<', '<=', '>', '>='
            operators. Default also puts in the '==' and '!=' operators.
            The compiler will also do internal adjustments to make it work
            even with implicit conversions since (a > b) can be written as
                (a <=> b) > 0          or            (b <=> a) < 0
            The generated operators will perform member wise comparisons.
        */
        auto operator<=>(const triple& rhs) const = default;

    private:
        T a{};
        T b{};
        T c{};
};

int main(void)
{
    triple t1{2}, t2{3, 1, 8};
    std::cout << std::boolalpha;
    std::cout << "t1 < t2 : " << (t1 < t2) << '\n';
    std::cout << "t1 <= t2 : " << (t1 <= t2) << '\n';
    std::cout << "t1 > t2 : " << (t1 > t2) << '\n';
    std::cout << "t1 >= t2 : " << (t1 >= t2) << '\n';
    std::cout << "t1 == t2 : " << (t1 == t2) << '\n';
    std::cout << "t1 != t2 : " << (t1 != t2) << '\n';
    // works even with implicit conversions
    std::cout << "t1 < 5 : " << (t1 < 5) << '\n';
    std::cout << "3 >= t2 : " << (3 >= t2) << '\n';

    return 0;
}
/*
    A possible '<' operator implementation:

        bool operator<(const triple& rhs) const {
            return (
                (a < rhs.a) ||
                (b < rhs.b) ||
                (c < rhs.c)
            );
        }
*/