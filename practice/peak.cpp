#include "carr.h"
#include "frand.h"
#include "isort.h"

template<typename Container>
int find_peak(Container arr);

int main(int argc, char* argv[])
{
    rng r;
    int first_size{r.randint(5, 15)}, i{};
    auto first = isort(r.rnums<array<int>>(0, 100, first_size));
    auto second = r.rnums<array<int>>(0, 100, 20 - first_size);
    array<int> arr(20);
    for (auto& n : first) arr[i++] = n;
    for (auto& n : second) arr[i++] = n;
    std::cout << "The array: " << arr << '\n';
    std::cout << "The peak occurs at index: " << find_peak(arr) << '\n';
    return 0;
}

// template<typename arr_tp, size_t size>
// int find_peak(arr_tp (&arr)[size]){
//     if (arr[0] >= arr[1])
//         return 0;
//     int i{};
//     rrepeat(1, size - 1, i)
//         if (arr[i - 1] <= arr[i] && arr[i + 1] <= arr[i])
//             return i;
//     if (arr[size - 1] >= arr[size - 2])
//         return size - 1;
//     return -1;
// }

template<typename Container>
int find_peak(Container arr){
    int i{}; size_t size{arr.size()};
    for (; i < size - 1; ++i)
        if (arr[i + 1] <= arr[i])
            return i;
    return (i == size - 1) ? i : -1;
}