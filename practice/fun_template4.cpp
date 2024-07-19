#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#define newline printf("\n");

// Template for general types
template<typename T> T max(T a, T b)
{
    std::cout << "template T max(T a, T b) called.\n";
    return (a > b) ? a : b;
}

// Template for pointer types
template<typename T> T* max(T* a, T* b)
{
    std::cout << "template T* max(T* a, T* b) called.\n";
    return (*a > *b) ? a : b;
}

/*
    A raw overload will be preferred in case of const char* even when we have a template
    dealing with pointers as the compiler avoids the unnecessary overhead of generating
    a function using the template when there is one already available for use.
    This overload will only be called for const char* pointers.
*/
const char* max(const char* a, const char* b)
{
    std::cout << "Raw overload called.\n";
    return (std::strcmp(a, b) > 0) ? a : b;
}

int main(void)
{
    const char* str1 {"function"};
    const char* str2 {"overload"};
    std::cout << "Calling max with two const char* variables : ";
    auto str_result = max(str1, str2);
    std::cout << "max(" << std::quoted(str1) << ", " << std::quoted(str2) << ") : " << str_result << std::endl;
    newline

    int x {101};
    int y {77};
    std::cout << "Calling max with two int variables : ";
    auto int_result = max(x, y);
    std::cout << "max(" << x << ", " << y << ") : " << int_result << std::endl;
    newline

    int* ptr_x {&x};
    int* ptr_y {&y};
    std::cout << "Calling max with two int* variables : ";
    auto ptr_result = max(ptr_x, ptr_y);
    std::cout << "max(&x, &y) : " << std::endl;
    std::cout << "max(" << ptr_x << ", " << ptr_y << ") : " << ptr_result << std::endl;
    std::cout << "*" << ptr_x << " : " << *ptr_x << ", *" << ptr_y << " : " << *ptr_y << std::endl;
    std::cout << "*" << ptr_result << " : " << *ptr_result << std::endl;

    return 0;
}