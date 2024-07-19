#include <iostream>
#include "utils.h"
#include "functor_lambda.h"

template<typename T>
unsigned int count_valid(T* arr, size_t size, bool (*validator_func)(const T&));

int main(void)
{
    const int SIZE = 15;
    using namespace fmt;
    int arr[SIZE];
    populate(arr, SIZE - 1);
    arr[SIZE - 1] = INT_MIN;
    std::cout << "Array: " << arr << "\n\n";
    
    InRange<int> range_functor(25, 75);
    // Using an anonymous functor
    std::cout << "Number of valid entries in array: "
        << count_valid<int>(arr, std::size(arr), InRange<int>(25, 75)) << '\n';
    
    // Using a named functor
    std::cout << "Number of valid entries in array: "
        << count_valid<int>(arr, std::size(arr), range_functor) << '\n';
    
    // Using a lambda function
    std::cout << "Number of valid entries in array: "
        << count_valid<int>(
            arr,
            std::size(arr),
            [](const int& n){
                return ((n>=25)&&(n<=75));
            }
        ) << '\n';
    return 0;
}

template<typename T>
unsigned int count_valid(T* arr, size_t size, bool (*validator_func)(const T&)){
    unsigned int count{};
    for (size_t i{}; i < size; i++)
        if (validator_func(arr[i]))
            count++;
    return count;
}