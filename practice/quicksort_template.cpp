#include <iostream>
#include <vector>
#include "lists.h"
#include "arrs.h"
#include "stream_insert.h"
#include "qsort.h"

int main(void)
{
	// Setting up containers
    int array[] = {98, 48, 64, 37, 12, 1, 94, 84, 11, 37, 4, 72, INT_MIN};
	std::vector<int> nums = {std::begin(array), std::end(array) - 1};
	arr::List<int> list(nums.begin(), nums.end());
    arr::Array<int> Array(array, std::size(array) - 1);

	using namespace __vec__;
	std::cout << "Unsorted vector : " << nums << '\n';
	qsort(nums);
	std::cout << "Sorted vector : " << nums << '\n';

	std::cout << "\nUnsorted list : " << list << '\n';
	qsort(list);
	std::cout << "Sorted list : " << list << '\n';

    using namespace delim_arr;
    std::cout << "\nUnsorted array : " << array << '\n';
    qsort(std::begin(array), std::end(array) - 1);
    std::cout << "Sorted array : " << array << '\n';

    std::cout << "\nUnsorted Array : " << Array << '\n';
    qsort(Array);
    std::cout << "Sorted Array : " << Array << '\n';

	return 0;
}