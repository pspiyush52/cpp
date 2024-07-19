#include <set>
#include <functional>
#include "stream_insert.h"

int main(void)
{
	unsigned int arr[] = {65, 12, 4, 8, 9, 4, 64, 5, 31, 84, 96, 37};

	// Initializing by providing the begin and end iterators
	std::multiset<unsigned int> nums_increasing(arr, arr + std::size(arr));
	using namespace __multiset__;
	std::cout << "nums_increasing: " << nums_increasing << '\n';

	// Initializing by providing the begin and end iterators
	std::multiset<unsigned int, std::greater<unsigned int>> nums_decreasing(arr, arr + std::size(arr));
	std::cout << "nums_decreasing: " << nums_decreasing << '\n';
	
	return 0;
}