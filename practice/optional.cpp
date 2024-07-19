#include "utils.h"
#include <optional>

std::optional<size_t> find(int* arr, size_t size, int num);

int main(void)
{
    std::optional<int> num{20};
    // value method returns the value contained in the optional variable
    std::cout << "num : " << num.value() << std::endl;
    // can also use the dereferencing operator to get the value contained in the optional variable
    std::cout << "*num : " << *num << std::endl;
    
    int array[] = {1, 10, 17, 8, 98, 4, 36, 32, 10, 41, 3, 19, 13, INT_MIN};
    std::cout << "\nThe array : " << array << std::endl;

    int key{4};

    std::optional<size_t> index = find(array, std::size(array), key);

    // checking using nullopt
    if (index != std::nullopt)
        std::cout << key << " found at index : " << index.value() << std::endl;
    else
        std::cout << key << " not found in array." << std::endl;

    int key2{11};

    std::optional<size_t> index2 = find(array, std::size(array), key2);

    // checking using has_value() method
    if (index2.has_value())
        std::cout << key2 << " found at index : " << index2.value() << std::endl;
    else
        std::cout << key2 << " not found in array." << std::endl;
    
    std::optional<int> opt_num{}; // initialized to std::nullopt
    int x = opt_num.value_or(8);  // assigns a value 8 if opt_num is std::nullopt
    std::cout << "x : " << x << std::endl;
    
    return 0;
}

std::optional<size_t> find(int* arr, size_t size, int num)
{
    for (size_t i{}; i < size; i++)
        if (arr[i] == num)
            return i;
    return std::nullopt;
}