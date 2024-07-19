#ifndef __UTILS_H
#define __UTILS_H

#include <iostream>
#include <memory>
#include <concepts>
#include <climits>
#include <float.h>

/// @brief Utilities for C-Style strings.
namespace sut{
    inline size_t strlen(const char* str){
        size_t i{};
        for (; str[i]; i++);
        return i;
    }
    inline bool islower(const char ch){
        return ((ch >= 97) && (ch <= 122));
    }
    inline bool isupper(const char ch){
        return ((ch >= 65) && (ch <= 90));
    }
    inline char tolower(const char ch){
        if (isupper(ch))
            return (ch + 32);
        return ch;
    }
    inline char toupper(const char ch){
        if (islower(ch))
            return (ch - 32);
        return ch;
    }
    inline int strcmpi(const char* lhs, const char* rhs){
        size_t lhs_len = strlen(lhs);
        size_t rhs_len = strlen(rhs);
        if (lhs_len != rhs_len)
            return (lhs_len - rhs_len);
        for (size_t i{}; i < lhs_len; i++)
            if (tolower(lhs[i]) != tolower(rhs[i]))
                return (lhs[i] - rhs[i]);
        return 0;
    }
}

/// @brief Utilities to display delimited arrays on the output using cout
///        and some formatted output functions.
namespace fmt{
    inline void print_u(const char *s)
    {
        int num = printf("%s", s);
        std::cout << std::endl;
        while (num-- != 0)
            std::cout << '-';
        std::cout << std::endl;
    }

    inline void print_u(const char *s, char u_char)
    {
        int num = printf("%s", s);
        std::cout << std::endl;
        while (num-- != 0)
            std::cout << u_char;
        std::cout << std::endl;
    }

    inline void line(char line_char = '-'){
        for (int i{}; i < 127; ++i)
            std::cout << line_char;
        std::cout << '\n';
    }

    inline void start(char ch = '-', size_t width = 127){
        size_t num_dashes = (width - 5) / 2, i{};
        for (; i < num_dashes; i++)
            std::cout << ch;
        std::cout << "START";
        for (i = 0; i < num_dashes; i++)
            std::cout << ch;
        std::cout << '\n';
    }
    
    inline void end(char ch = '-', size_t width = 127){
        size_t num_dashes = (width - 3) / 2, i{};
        for (; i < num_dashes; i++)
            std::cout << ch;
        std::cout << "END";
        for (i = 0; i < num_dashes; i++)
            std::cout << ch;
        std::cout << '\n';
    }
}

namespace __helpers{

    struct tautology {
        template<typename T>
        bool operator()(T&&){
            return true;
        }
    };

    template<typename T>
    concept is_numeric = std::is_convertible_v<T, double>;

    template<typename T>
    concept comparable = requires (T a, T b){
        a < b; a <= b;
        a > b; a >= b;
    };

    template<typename T>
    requires comparable<T>
    T min(T a, T b){
        return (a < b) ? a : b;
    }

    template<typename T>
    requires comparable<T>
    T max(T a, T b){
        return (a > b) ? a : b;
    }

    template<typename T>
    requires std::is_integral_v<T>
    unsigned char __num_digits(T num){
        if (!num)
            return 1;
        unsigned char count{};
        for (; num; num /= 10)
            ++count;
        return count;
    }
    
    template<typename T>
    requires std::is_floating_point_v<T>
    unsigned char __num_digits(T num){
        size_t n = static_cast<size_t>(num * 10e5);
        return __num_digits(n);
    }

}

#endif  // __UTILS_H