#include "arr.h"
#include "utils.h"

int main(void)
{
    sep;
    using namespace fmt;
    double arr[] = {1.2, 63.15, 0.78, 6.45, 36, 0.984, 34.12, 17.91, DBL_MIN};
    size_t size = std::size(arr), i{};
    std::cout << "Array before sorting: " << arr << '\n';
    sort::mergesort(arr, size - 1);
    std::cout << "\nArray after sorting: " << arr << '\n';
    sep;

    arr::Array<unsigned int> uiarr{48, 31, 63, 10, 64, 81, 30, 10, 11, 94, 18, 37, 52};
    std::cout << "Array before sorting: " << uiarr << '\n';
    sort::mergesort(uiarr);
    std::cout << "\nArray after sorting: " << uiarr << '\n';
    sep;
    
    return 0;
}