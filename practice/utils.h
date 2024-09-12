#ifndef __UTILS_H
#define __UTILS_H

#include "print.h"
#include "range.h"
#include <stdio.h>
#include <chrono>

/**
 * @brief Measures the running time of a function fun and returns
 * the time taken in microseconds.
 * @param fun The function whose running time is to be measured.
 * @param args Arguments to be passed to fun if any.
*/
template<typename func_tp, typename... Arguments>
inline int64_t timeit(func_tp& fun, Arguments&... args){
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    fun(args...);
    auto end = high_resolution_clock::now();
    auto d = duration_cast<microseconds>(end - start);
    return d.count();
}
template<typename func_tp, typename... Arguments>
inline int64_t timeit(func_tp&& fun, Arguments&&... args){
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    fun(args...);
    auto end = high_resolution_clock::now();
    auto d = duration_cast<microseconds>(end - start);
    return d.count();
}

template<typename T>
inline const T& max(const T& x){ return x; }

// Returns the maximum out of any number of arguments of the same type
template<typename T, typename... Arguments>
inline const T& max(const T& x, const Arguments&... args){
    const T& rest_max = max<T>(args...);
    return (x > rest_max) ? x : rest_max;
}

template<typename T>
inline const T& min(const T& x) { return x; }

// Returns the minimum out of any number of arguments of the same type
template<typename T, typename... Arguments>
inline const T& min(const T& x, const Arguments&... args){
    const T& rest_min = min<T>(args...);
    return (x < rest_min) ? x : rest_min;
}

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
    inline bool is_whitespace(const char& ch){
        switch (ch){
            case ' ':
            case '\t':
            case '\f':
            case '\n':
            case '\r':
            case '\v':
                return true;
            default:
                return false;
        }
    }
}

/// @brief Utilities to display delimited arrays on the output using cout
///        and some formatted output functions.
namespace fmt{
    inline void print_u(const char *s)
    {
        int num = printf("%s", s);
        putchar('\n');
        while (num-- != 0)
            putchar('-');
        putchar('\n');
    }

    inline void print_u(const char *s, char u_char)
    {
        int num = printf("%s", s);
        putchar('\n');
        while (num-- != 0)
            putchar(u_char);
        putchar('\n');
    }

    template<typename string_tp>
    void print_u(const string_tp& str) {
        auto size = str.size();
        std::cout << str << '\n';
        for (decltype(size) i{}; i < size; ++i)
            putchar('-');
        putchar('\n');
    }
    template<typename string_tp>
    void print_u(const string_tp& str, char u_char) {
        auto size = str.size();
        std::cout << str << '\n';
        for (decltype(size) i{}; i < size; ++i)
            putchar(u_char);
        putchar('\n');
    }

    inline void line(char line_char = '-'){
        for (int i{}; i < 127; ++i)
            putchar(line_char);
        putchar('\n');
    }

    inline void start(char ch = '-', size_t width = 127){
        size_t num_dashes = (width - 5) / 2, i{};
        for (; i < num_dashes; i++)
            putchar(ch);
        printf("START");
        for (i = 0; i < num_dashes; i++)
            putchar(ch);
        putchar('\n');
    }
    
    inline void end(char ch = '-', size_t width = 127){
        size_t num_dashes = (width - 3) / 2, i{};
        for (; i < num_dashes; i++)
            putchar(ch);
        printf("END");
        for (i = 0; i < num_dashes; i++)
            putchar(ch);
        putchar('\n');
    }
}

/*
inline void custom_terminate(){
    std::exception_ptr ptr = std::current_exception();
    try{
        if (ptr)
            std::rethrow_exception(ptr);
    }
    catch(std::exception& ex){
        printf("Unhandled exception:\n  %s\n", ex.what());
    }
    std::abort();
}
*/

#endif  // __UTILS_H
