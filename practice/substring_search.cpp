#include <iostream>

long long search(const char* str, const char* pattern, long long& i){
    if (!(*str))
        return -1;
    const char* p = pattern;
    for (; (*str) && (*str != *p); ++str, ++i);
    for (; (*str) && (*p) && (*str == *p); ++str, ++p);
    if (*p == 0)
        return i;
    else
        return search(str, pattern, ++i);
}

long long search(const char* str, const char* query){
    if (*query == 0)
        return -1;
    long long i{};
    return search(str, query, i);
}

int main(void)
{
    const char* str = "This is a string with some words words repeated on on purpose pose.";
    const char* pattern = "purpo";
    std::cout << search(str, pattern) << '\n';
    return 0;
}