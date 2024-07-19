#include <iostream>
#include <string>
/*
    Functors are objects of a class that overloads the () operator.
*/
class print{
    public:
        void operator()(const std::string& str) const {
            std::cout << str << '\n';
        }
        std::string operator()(const std::string& str1, const std::string& str2) const {
            return (str1 + " " + str2);
        }
};

int main(void)
{
    print printer;
    printer("this is C++");
    std::cout << printer("niharika", "joshi") << '\n';
    return 0;
}