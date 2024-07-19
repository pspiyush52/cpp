#include <iostream>
#include <vector>
#include "range.h"
#include "view.h"
#include "functors.h"
#include "stream_insert.h"
#include "arrs.h"

int main(void)
{
	std::cout << "Odd numbers in the range [0, 30):\n  ";
	for (auto n : range(0, 30) | odds())
		std::cout << n << ' ';
	std::cout << '\n';
	
	std::cout << "\nGenerating 15 random numbers and viewing only the odd numbers from among them:\n  ";
	for (int i : rand_range(10, 200, 15) | odds())
		std::cout << i << ' ';
	std::cout << '\n';

	std::vector<int> nums(20);
	(rand_range(0, 100) | odds()) >> nums;
	using namespace __vec__;
	std::cout << "\nCreating a vector of size 20 and filling it with random odd values in the range [0, 100):\n  ";
	std::cout << nums << '\n';

	arr::Array<int> oddnums(5);
	(rand_range(0, 500)|odds()) >> oddnums;
	std::cout << "\nCreating an arr::Array of size 5 and filling it with odd random numbers.\n";
	std::cout << "Generating random numbers in the range [0, 500) and viewing only the odd numbers from among them.\n  ";
	std::cout << oddnums << '\n';
	return 0;
}