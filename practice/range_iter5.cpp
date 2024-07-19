#include <iostream>
#include <vector>
#include "random.h"
#include "range.h"
#include "view.h"
#include "functors.h"
#include "stream_insert.h"

int main(void)
{
	std::vector<int> nums(50);
	std::vector<int> oddnums(10);

	rand_range(0, 100) >> nums;
	(nums | odds()) >> oddnums;
	
	using namespace __vec__;
	std::cout << "nums:\n  " << nums << '\n';
	std::cout << "\noddnums:\n  " << oddnums << '\n';
	
	return 0;
}