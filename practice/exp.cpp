#include <cstdlib>
#include "integer.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " base exponent\n";
        std::exit(EXIT_FAILURE);
    }
    Integer x = argv[1], res{"1"};
    long long n = std::stol(argv[2]);
    for (; n > 0; --n)
        res = res * x;
    std::cout << '\n' << res << '\n';
    std::cout << "Width: " << res.size() << '\n';
    return 0;
}
