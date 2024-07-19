#include <iostream>

int main(void)
{
    // if we want the lambda function to take parameters of the same type, we can
    // use the following templated lambda function
    auto add = [] <typename T> (T a, T b) -> T {
        return (a + b);
    };
    double x {3.48745};
    double y {14.7863};
    std::cout << "add(" << x << ", " << y << ") : " << add(x, y) << std::endl;

    auto total = [] <typename T> (T* collection, size_t size) -> T {
        T sum{};
        for (size_t i{}; i < size; i++)
            sum += collection[i];
        return sum;
    };

    // int arr[]{21, 10, 11, 36, 31, 8, 56, 78, 19, 34};
    double arr[]{1.45, 2.8404, 0.7458, 2.1454, 3.694, 1.0102, 7.184};
    std::cout << "total(arr) : " << total(arr, std::size(arr)) << std::endl;
    std::cout << std::endl;

    // can also be used with multiple types
    auto fun = [] <typename T, typename U> (T a, U b) {
        std::cout << "Argument 1 : " << a << std::endl;
        std::cout << "Argument 2 : " << b << std::endl;
    };

    int num {3};
    fun(x, y);
    fun(x, num);

    return 0;
}