#include <iostream>
#include <ctime>
#include "utils.h"

void square(int& num){ num *= num; }

int* transform(int* arr, void (*transformer)(int&)){
    int i{};
    while (arr[i] != INT_MIN)
        transformer(arr[i++]);
    
    return arr;
}

template<typename T>
T* transform_t(T* arr, size_t size, void (*transformer)(T&)){
	for (size_t i{}; i < size; i++)
		transformer(arr[i]);
	
	return arr;
}

int main(void)
{
    std::srand(std::time(0));
    using namespace fmt;
    int arr[20];
    repeat(19) arr[i] = std::rand() % 100;
    arr[19] = INT_MIN;
    std::cout << "Array: " << arr << '\n';
    
    // std::cout << "Transformed array: " << transform(arr, square) << '\n';
    transform(arr, [](int& num){
        num += 23;
    });
    std::cout << "Transformed array: " << arr << '\n';

    auto restore = [](int& num){
        num -= 23;
    };
    std::cout << "Restored array: " << transform(arr, restore) << '\n';
    newline;

    // Using lambdas as callbacks with templates
    int arr2[] = {32, 15, 84, 311, 10, 89, 3, 9, 122, 17, 8, INT_MIN};
	std::cout << "Array: " << arr2 << '\n';
	std::cout << "Transformed: " << transform_t<int>(arr2, std::size(arr2) - 1, [](int& n){
		n += 2;
	}) << '\n';

	auto tran = [](int& n){ n -= 2; };
	std::cout << "Restored: " << transform_t<int>(arr2, std::size(arr2) - 1, tran) << '\n';

    return 0;
}