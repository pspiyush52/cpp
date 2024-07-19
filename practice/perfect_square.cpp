#include <stdio.h>
#include <stdlib.h>

bool is_perfect_square(long long num){
    long long i = 1;
    for (; num > 0; i += 2)
        num -= i;
    return (num) ? false : true;
}

int main(int argc, char* argv[])
{
    if (argc == 2)
        printf ((is_perfect_square(atoll(argv[1]))) ? "Perfect square" : "Not a perfect square");
    return 0;
}