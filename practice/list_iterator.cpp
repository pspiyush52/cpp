#include <iostream>
#include <vector>
#include <algorithm>
#include "iterator.h"
#include "random.h"
#include "stream_insert.h"

int main(void)
{
	List<int> nums;
	append_random(nums, 10, 50, 20);
	List<int>::iterator iter = nums.begin();
	*iter = 1000;
	std::cout << "List: " << nums << '\n';
	auto res = std::ranges::find(nums, 40);
	if (res != nums.end())
		std::cout << "Found " << *res << " in the list.\n";
	else
		std::cout << "List does not contain 40.\n";
	return 0;
}