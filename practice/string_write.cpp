#include <iostream>
#include <fstream>
#include "arr_string.h"

int main(void)
{
    string Name{"Niharika Joshi"};
    size_t size{Name.size()};
    std::ofstream sizes("sizes.bin");
    std::ofstream data("string_data.bin");
    sizes.write((char*) &size, sizeof(size));
    data.write((char*) &Name[0], Name.size());
    sizes.close();
    data.close();

    char buf[50];
    std::ifstream sizes_r("sizes.bin");
    std::ifstream data_r("string_data.bin");
    sizes_r.read((char*) &size, sizeof(size));
    data_r.read((char*) buf, size);
    buf[Name.size()] = '\0';
    std::cout << buf << '\n';

    return 0;
}