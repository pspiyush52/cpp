#include <iostream>
#include <bitset>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: print_binary.exe num";
        return 1;
    }
    int num = atoi(argv[1]);
    std::cout << std::bitset<32>(num) << std::endl;
    return 0;
}