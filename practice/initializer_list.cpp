#include <iostream>
/*
 * Syntax:
 * class_name(param list) : member_var1(param_x1), member_var2(param_x2), ...
 * One advantage of using initializer lists is that the initialization happens
 * at object creation time itself, whereas in usual member-wise copy
 * initialization the object is created first and then the values are assigned
 * to member variables one by one and thus avoiding unnecessary copies.
 * 
 * The order of variables does not matter in member-wise copy initialization but
 * the order matters when it comes to initializer lists.
 */
class Box {
    public:
        Box(double Length, double Breadth = 1, double Height = 1);
        double volume();
    private:
        double length;
        double breadth;
        double height;
};

int main(void)
{
    Box b(4);
    std::cout << "Volume : " << b.volume() << std::endl;
    return 0;
}

// syntax for initializer list initialization
Box::Box(double Length, double Breadth, double Height):
length(Length), breadth(Breadth), height(Height){}

double Box::volume(){
    return length * breadth * height;
}