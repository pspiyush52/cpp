#include "print.h"
#include "avl.h"
#include <cstdint>

const int UPTO = 10000;

template<typename HashFunc>
int check_collisions(HashFunc f);

uint32_t hash(uint32_t n) {
    return ((n & 0x0000FFFF) << 4) + (n ^ 0xFFFF0000);
}

int main(void)
{
    for (int i{1000}; i < 1100; ++i)
        print("i:", i, ", h(i):", hash(i));
    // int num_of_collisions = check_collisions(hash);
    // std::cout << num_of_collisions << '\n';

    return 0;
}

template<typename HashFunc>
int check_collisions(HashFunc f) {
    Set<uint32_t> hash_values;
    uint32_t collisions{}, i{}, hash_value{};
    for (; i < UPTO; ++i) {
        hash_value = f(i);
        if (hash_values.in(hash_value))
            ++collisions;
        else
            hash_values.insert(hash_value);
    }
    return collisions;
}
