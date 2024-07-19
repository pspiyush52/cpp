#include <iostream>
#include <cstdlib>

size_t count{};
void towers(int n, char from, char to, char tmp){
    if (n == 0)
        return;
    ++count;
    towers(n - 1, from, tmp, to);
    std::cout << from << " --> " << to << '\n';
    towers(n - 1, tmp, to, from);
}

int main(int argc, char* argv[])
{
    if (argc == 2){
        towers(std::atoi(argv[1]), 'A', 'B', 'C');
        std::cout << "\nDone in " << count << " steps.\n";
    }
    else
        std::cout << "Usage:  towers.exe [number_of_discs]\n";
    return 0;
}