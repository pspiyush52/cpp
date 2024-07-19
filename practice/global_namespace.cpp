#include <iostream>

void print(double x, double y, auto fun);
double add(double x, double y);

int main(void)
{
    // double add(double x, double y);
    auto add = [](double x, double y){
        std::cout << "(Local add called) ";
        return x + y - 0.214;
    };
    double x{45.2};
    double y{84.7};
    print(x, y, add);

    // :: operator is used to refer to the items in the global namespace
    print(x, y, ::add);
    return 0;
}

void print(double x, double y, auto fun){
    std::cout << x << " + " << y << " = " << fun(x, y) << '\n';
}

double add(double x, double y){
    std::cout << "(Global add called) ";
    return x + y;
}