#include <iostream>
#include <vector>
#include <ranges>
#include "stream_insert.h"
#include "random.h"
#include "defs.h"

int main(void)
{
	using namespace __vec__;
	std::vector<int> nums;
	push_random(nums, -100, 100, 20);
	std::cout << "Vector containing random numbers:\n  " << nums << newl;
	std::ranges::filter_view view1(nums, [](int& n){
		return ((n % 7) == 0);
	});
	std::cout << "\nViewing the numbers in the vector which are divisible by 7 : ";
	for (int n : view1)
		std::cout << n << ' '; newline;
	
	auto view2 = std::views::take_while(nums, [](int& n){
		return ((n % 8) != 0);
	});
	// std::ranges::take_while_view view2(nums, [](int& n){
	// 	return ((n % 8) != 0);
	// });
	std::cout << "\nViewing numbers in the vector until a number divisible by 8 is encountered : ";
	for (int n : view2)
		std::cout << n << ' '; newline;
	return 0;
}