#include <iostream>
#include <fstream>
#include <string>
#include <exception>

void read_from_file(const char* filename, int* arr, size_t size){
    std::ifstream file{filename};
    if (file.fail())
        throw std::runtime_error{std::string("Unable to open file ") + filename};
    
    int val, i{};
    
    while(file >> val)
    {
        if (file.fail())
        {
            file.close();
            throw std::runtime_error{
                std::string("Something went wrong while reading from file") + filename
            };
        }
        if (i >= size)
        {
            file.close();
            throw std::runtime_error{
                std::string("Buffer overflow while reading from file ") + filename
            };
        }
        arr[i++] = val;
    }
    file.close();
}

int main(void)
{
    int arr[4];

    try{
        read_from_file("numbers.txt", arr, std::size(arr));
    }
    catch(std::runtime_error& ex){
        std::cout << "Runtime Error: " << ex.what() << '\n';
    }

    for (int num : arr)
        std::cout << "value: " << num << '\n';

    return 0;
}