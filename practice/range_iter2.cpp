#include <iostream>
#include <vector>
#include "random.h"
#include "range_iter.h"
#include "stream_insert.h"

int main(void)
{
	std::vector<int> nums;
	push_random(nums, -100, 100, 20);
	using namespace __vec__;
	std::cout << "Vector of random values:\n  " << nums << '\n';
	
    auto oddfun = [](int& n){
		return ((n % 2) != 0);
	};
	range odds(nums, oddfun);
	
    for (; !odds.at_end(); ++odds)
		*odds = 0;
	
    std::cout << "\nVector after resetting the odd values:\n  " << nums << '\n';
	std::cout << "\nSize of range iterator : " << sizeof(odds) << '\n';
	
    return 0;
}