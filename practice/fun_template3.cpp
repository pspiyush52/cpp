#include <iostream>
#include <cstring>

template<typename T> T max(T a, T b)
{
    return (a > b) ? a : b;
}

// specializing max for const char*
template<>
const char* max<const char*> (const char* a, const char* b)
{
    return (std::strcmp(a, b) > 0) ? a : b;
}

int main(void)
{
    std::cout << max(36, 9) << std::endl;
    std::cout << max("c++", "templates") << std::endl;
    return 0;
}