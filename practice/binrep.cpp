#include "string.h"
#include "frand.h"

template<typename T>
void bin(T var){
    string res;
    for (; var; var >>= 1)
        res.push_front((var % 2) + '0');
    std::cout << res << '\n';
}

// Print any object's byte-wise binary representation
template<typename T, int size = sizeof(T)>
void binrep(const T& var){
    typedef char* pointer;
    pointer ptr = (pointer) &var;
    for (int i{size - 1}; i >= 0; --i)
        std::cout << bstring((int)ptr[i], 8).btoi() << ' ';
    std::cout << '\n';
}

int main(int argc, char* argv[])
{
    if (argc == 2){
        string arg{argv[1]};
        bin(arg.stoull());
    }
    rng r;
    binrep(r);
    return 0;
}