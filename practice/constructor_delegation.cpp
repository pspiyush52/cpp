#include <iostream>
// Constructor delegation is when a constructor calls another constructor
// to create an object.

class Square {
    public:
        Square(double Side);
        Square(double Side, const std::string& Color, int Shading);
        bool operator<(const Square& s) const;
        bool operator>(const Square& s) const;

    private:
        double side;
        std::string color;
        int shading;
        double position;
};

int main(void)
{
    Square s(4.5);
    return 0;
}

// Initializer lists can work with both () or {} for initialization

// The one param constructor is calling the three param constructor to create the object
Square::Square(double Side):
Square{Side, "black", 10}{
    std::cout << "One param constructor called..." << " object created at " << this << std::endl;
    // after we return from three param constructor's body we can intialize the other member
    // variable or do anything we want really
    position = 1.0;
}
Square::Square(double Side, const std::string& Color, int Shading):
side{Side}, color{Color}, shading{Shading}{
    std::cout << "Three param constructor called... " << " object created at : " << this << std::endl;
}

/*
    When the one param constructor is called,
    1. it will further call the three param constructor
    2. the three param constructor will create and initialize the object
    3. the body of the three param constructor will be executed
    4. Control will go back to the one param constructor and the body of the one param
       constructor will be executed.

    When using constructor delegation we cannot initialize any other member variable in the initializer
    list along with the call to the other constructor, i.e., the following are invalid:

        Square::Square(double Side):
        Square(Size, "black", 10), position(1.0){}

        Or,

        Square::Square(double Side):
        position(1.0), Square(Size, "black", 10){}

        i.e., no other initialization possible with delegation
*/

bool Square::operator<(const Square& s) const
{
    return (side < s.side) ? true : false;
}
bool Square::operator>(const Square& s) const
{
    return (side > s.side) ? true : false;
}