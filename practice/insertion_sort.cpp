#include <iostream>
#include "carr.h"
#include "range.h"
#include "functors.h"
#include "points.h"

template<typename Container, typename Comparator = less, typename Projection = identity>
Container& isort(Container& arr, Comparator compare = {}, Projection proj = {}){
    size_t i = 1, j = 0;
    for (; i < arr.size(); ++i)
        for (j = i; (j > 0) && compare(proj(arr[j]), proj(arr[j - 1])); --j)
            swap(arr[j], arr[j - 1]);
    return arr;
}
struct Dist{
    double operator()(Point& p) {
        return p.length();
    }
};
int main(void)
{
    array<int> nums(20);
    rand_range(-100, 100) >> nums;
    std::cout << "Before sorting:  " << nums << "\nAfter sorting:  " << isort(nums) << '\n';

    array<Point> points = {
        {0, 1}, {-0.15, 23}, {10, 2}, {0.791, .31}, {1, 33}, {-0.41, -1.2}
    };

    std::cout << "\nBefore sorting:  " << points << "\nAfter sorting:  " << isort<array<Point>, less, Dist>(points);
    return 0;
}