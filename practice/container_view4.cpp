#include <iostream>
#include <vector>
#include "views.h"
#include "stream_insert.h"
#include "random.h"
#include "lists.h"

int main(void)
{
	using namespace __vec__;
	std::vector<int> nums;  push_random(nums, -100, 100, 20);
	auto evens = [](int& n){ return ((n % 2) == 0); };
	auto odds = [](int& n){ return ((n % 2) != 0); };
	auto sixes = [](int& n){ return ((n % 6) == 0); };
	auto id = [](int& n){ return n; };
	
	// Composing different views
	Views v(Views(nums, evens), sixes);
	std::cout << "Using usual composition : " << v << '\n';
	std::cout << "Using '|' operator with rvalue Views : " << (Views(nums, evens) | Views(nums, sixes)) << '\n';
	std::cout << "Using '|' operator directly with the container and predicates : " << (nums | evens | sixes) << '\n';

	std::cout << "\nVector of random numbers:\n  " << nums << '\n';
	for (int& n : nums | odds)
		n = 0;
	std::cout << "\nVector after selectively setting odd numbers to 0:\n  " << nums << '\n';

	List<int> list;  append_random(list, -100, 100, 30);
	std::cout << "\nList of random values:\n  " << list << '\n';
	for (int& n : list | odds)
		n = 0;
	std::cout << "\n List after selectively setting odd values to 0:\n  " << list << '\n';
	return 0;
}