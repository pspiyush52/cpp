#include <iostream>

template<typename T> T add(T a, T b) // ... (1)
{
    std::cout << "Plain template called.\n";
    return a + b;
}

template<>
int add<int> (int a, int b) // specializes (1)
{
    std::cout << "Specialized template called.\n";
    return a + b;
}

template<>
int* add<int*> (int* a, int* b) // specializes (1)
{
    std::cout << "Template specialization called.\n";
    return a;
}

// overload will be preferred instead of specialization
template<typename T> T* add(T* a, T* b) // overloads (1)
{
    std::cout << "Template overload called.\n";
    return a;
}

/*
// a raw overload will be preferred over any template overload or specialization
int add(int a, int b)
{
    std::cout << "Raw overload called.\n";
    return a + b;
}
*/

int main(void)
{
    int x{};
    int y{};
    add(x, y);
    add(&x, &y); // template overload will be called instead of specialization
    return 0;
}