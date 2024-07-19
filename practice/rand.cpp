#include <iostream>
#include <ctime>

int main(void)
{
    std::time_t seed =  std::time(0), a = 37, b = 41;
    double A{0.7915484751}, val = seed;
    for (int i{}; i < 10; ++i){
        seed = (seed * a + b) % 701;
        val = seed * A;
        val -= (int) val;
        std::cout << static_cast<int>(val * 100) << "  ";
    }
    return 0;
}