#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <type_traits>
#include <concepts>

template<typename T>
concept numeric = std::is_convertible_v<T, double>; // using a type trait to build a concept

template<typename T>
concept multipliable = requires (T a, T b) {
    a * b;  // makes sure the syntax is valid
};

template<typename T>
concept summable = requires (T a, T b) {
    a + b;  // makes sure the syntax is valid
};

// syntax check can be done with multiple statements as well
template<typename T>
concept Incrementable = requires (T a) {
    a += 1;
    a++;
    ++a;
}; // this will check if the variable of type T can be incremented using any of the 3 methods or not

template<typename T>
requires numeric<T>
T min(T a, T b)
{
    return (a < b) ? a : b;
}

template<typename T>
T add(T a, T b) requires summable<T>
{
    return a + b;
}

template<multipliable T>
const T& prod (T& a, T& b)
{
    a *= b;
    return (a);
}

class cstring {
    public:
        cstring(const char*);
        cstring(std::string);
        cstring(char*);
        cstring operator+(cstring& str2)
        {
            cstring c("");
            size_t size = std::strlen(str) + std::strlen(str2.str) + 1;
            c.print_str = new char[size];
            for (size_t i{}; i < size; i++)
                c.print_str[i] = '\0';
            std::strcat(c.print_str, str);
            std::strcat(c.print_str, str2.str);
            return c;
        }
        ~cstring();
    private:
        const char* str;
        char* print_str;
        friend std::ostream& operator<<(std::ostream& output, cstring& c)
        {
            if (c.print_str)
                output << c.print_str;
            else
                output << c.str;
            return output;
        }
};

cstring::cstring(const char* string)
{
    str = string;
    print_str = nullptr;
}
cstring::cstring(std::string string)
{
    str = string.c_str();
    print_str = nullptr;
}
cstring::cstring(char* string)
{
    str = string;
    print_str = nullptr;
}
cstring::~cstring()
{
    if (print_str)
        delete[] print_str;
}

int main(void)
{
    int x{20};
    int y{16};
    std::cout << "min(" << x << ", " << y << ") : " << min(x, y) << std::endl;
    std::cout << "prod(" << x << ", " << y << ") : " << prod(x, y) << std::endl;

    std::string str1 {"blue"};
    std::string str2 {" sky"};
    // std::cout << prod(str1, str2); // will produce an error since two strings are not multipliable
    std::cout << "add(" << std::quoted(str1) << ", " << std::quoted(str2) << ") : " << std::quoted(add(str1, str2)) << std::endl;
    std::cout << std::endl;

    const char* first_name = "Niharika";
    const char* last_name = "Joshi";
    // std::cout << add(first_name, last_name); // will produce an error since two const char* cannot be added using the + operator

    cstring c1("blue");
    cstring c2(str2);
    std::cout << "cstring c1 : " << c1 << std::endl;
    std::cout << "cstring c2 : " << c2 << std::endl;

    cstring c3 = add(c1, c2); // works since the + operation is supported between 2 objects of cstring class
    std::cout << "add(c1, c2) : " << c3 << std::endl;

    return 0;
}