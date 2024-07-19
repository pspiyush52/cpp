#include <stdio.h>
#include <stdlib.h>

bool is_prime(long long n){
    if (n < 2)
        throw 0;
    for (int i = 2; i * i <= n; ++i)
        if (n % i)
            continue;
        else
            return false;
    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;
    long long n = atoll(argv[1]);
    try{
        if (is_prime(n))
            printf("%lld is prime.\n", n);
        else
            printf("%lld is not prime.\n", n);
    }
    catch(...){
        printf("Valid range is 2 to LLONG_MAX");
    }
    return 0;
}
