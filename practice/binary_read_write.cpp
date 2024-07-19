#include <iostream>
#include <fstream>

int main(void)
{
    int arr[] = {4, 2, 1, 5, 8, 5, 6, 7};
    std::ofstream of("binrw");
    of.write((char*) arr, sizeof(arr));
    of.close();
    for (int i = 0; i < 8; ++i)
        arr[i] = 0;
    
    std::ifstream infile("binrw");
    infile.read((char*) arr, sizeof(arr));
    for (int i{}; i < 8; ++i)
        std::cout << arr[i] << ' ';
    
    std::cout << '\n';
    return 0;
}