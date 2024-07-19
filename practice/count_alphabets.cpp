#include "char_counter.h"
#include "string.h"

int main()
{
    const char* str = "abbbabaaaababbbabbabbabaaaabaaaaabbbbababaababbbbaaab";
    std::cout << Counter(str) << '\n';
    std::cout << string(str).count('a') << '\n';
    std::cout << string(str).count('b') << '\n';
    return 0;
}