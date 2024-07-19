#include "print.h"
#include "carr.h"

int main(int argc, char* argv[])
{
    if (argc == 2){
        auto dec = [](char c){ return c - 'a' + 1; };
        long long hash{}, mul{1};
        const char* str = argv[1];
        for (; *str; ++str, mul *= 26)
            hash += dec(*str) * mul;
        print("Hash value:", hash);
    }
    else{
        array<char> alpha('a', 'z');
        for (size_t i{}; i < alpha.size(); ++i)
            std::cout << '[' << (i + 1) << ':' << alpha[i] << "] ";
    }
    return 0;
}
