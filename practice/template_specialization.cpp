/*
 * Class template specializations are not templates, they are full
 * classes. If their definitions show up in a header and the header is
 * included in multiple files, we will have ODR violations.
 * 
 * As specializations are separate classes altogether, we would only have
 * access to members defined in the specialized class and not the members
 * defined in the template.
 * 
 * If we choose to specialize a single method for a class, even that will
 * be treated as actual code and not a template so if it appears more
 * than once it will violate the ODR rule.
 * 
 * To solve this problem we can either mark them as inline or move their
 * implementation to a separate file.
 */
#include <iostream>
#include <cstring>

template<typename T>
class Adder{
    public:
        T add(T a, T b);
};

template<typename T>
T Adder<T>::add(T a, T b){ return a + b; }

// Specializing Adder class for char*
template<>
class Adder<char*>{
    public:
        char* add(char* lhs, char* rhs);
};

// template<> // Not required since this is a method of a whole new class
              // and not of a template.
char* Adder<char*>::add(char* lhs, char* rhs){
    return std::strcat(lhs, rhs);
}

int main(void)
{
    char str[20]{"This"};
    char str2[]{" is"};
    Adder<char*> a;
    std::cout << a.add(str, str2);
    return 0;
}