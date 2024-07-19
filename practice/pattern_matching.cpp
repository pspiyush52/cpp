#include <iostream>

template<size_t str_size, size_t pattern_size>
bool contains(char (&str)[str_size], char (&pattern)[pattern_size]){
    if (pattern_size > str_size)
        return false;
    size_t upto{str_size - pattern_size + 1};
    for (size_t i{}, j{}; i < upto; ++i){
        for (j = 0; (j < pattern_size) && (str[j + i] == pattern[j]); ++j);
        if (j == pattern_size - 1)
            return true;
    }
    return false;
}

bool contains_p(const char* str, const char* pattern){
    const char* ptr;
    do{
        for (ptr = pattern; *str && (*ptr == *str); ++ptr, ++str);
            if (!*ptr)
                return true;
    } while (*str++);
    return false;
}

int main(void)
{
    std::cout << std::boolalpha;
    char str[] = "strawberry";
    char pattern[] = "err";
    std::cout << contains(str, pattern) << '\n';
    std::cout << contains_p(str, pattern) << '\n';
    return 0;
}