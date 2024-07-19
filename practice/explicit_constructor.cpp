#include <iostream>
#include <iomanip>

/*
    3. The explicit keyword in front of the constructor stops the compiler from
    doing an implicit conversion and creating an internal object. It basically
    stops the compiler from using the constructor in implicit conversions.
*/

class Square {
    public:
        explicit Square(double side);
        bool operator<(const Square& s) const;
        bool operator>(const Square& s) const;
        // implicit conversion will be inserted in call by value as well,
        // bool operator<(const Square s);
        // bool operator>(const Square s);
    private:
        double side;
};

int main(void)
{
    const Square s1(4);
    const Square s2(7);
    std::cout << std::boolalpha;
    std::cout << "s1 < s2 : " << (s1 < s2);
    std::cout << "\ns1 > s2 : " << (s1 > s2);

    /*
        1. Since the operator functions take const references as arguments, the compiler
        will try and do an implicit conversion wherever required. Therefore, in the
        comparison s1 > 2, the compiler will check if it can generate an internal Square
        object using 2. This conversion will be possible because the constructor of
        class Square takes only one argument and hence 2 can be used to construct an
        internal Square object and a reference to that object will be passed to the
        function.

        2. This will be possible even if the constructor takes more than one arguments but
        all of the parameters have default values except one. In that case, it will be
        possible to construct an object by passing even one argument to the constructor.
        So the implicit conversion can take place in that case as well.
        For example:
            Square(double side, std::string color = "black");
        
        In this case (s1 < 2) will again insert an implicit conversion because an object can
        be created using only one argument.
    */
    // std::cout << "\ns1 > 2 : " << (s1 > 2); // compiler error if constructor is explicit

    return 0;
}

Square::Square(double Side):
side(Side){}

bool Square::operator<(const Square& s) const
{
    return (side < s.side) ? true : false;
}
bool Square::operator>(const Square& s) const
{
    return (side > s.side) ? true : false;
}