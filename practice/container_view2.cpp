#include <iostream>
#include <vector>
#include "view.h"
#include "lists.h"
#include "stream_insert.h"
#include "random.h"

int main(void)
{
	std::srand(std::time(0));
	std::vector<int> nums;
	push_random(nums, -100, 100, 20);
	using namespace __vec__;
	std::cout << "Vector of random numbers:\n  " << nums << '\n';
	View negatives(nums, [](int& n){
		return (n < 0);
	});
	auto iter = negatives.begin();
	for (; iter != negatives.end(); ++iter)
		*iter = 0;
	std::cout << "\nVector after modifying the negative values:\n  " << nums << '\n';

	List<int> list;
	append_random(list, -100, 100, 20);
	std::cout << "\nList of random numbers:\n  " << list << '\n';
	View odds(list, [](int& n){
		return ((n % 2) != 0);
	});
	auto _iter = odds.begin();
	for (; _iter != odds.end(); ++_iter)
		*_iter = 0;
	std::cout << "\nModified odd numbers from the list:\n  " << list << '\n';

	int arr[15];
	fill_random(std::begin(arr), std::end(arr), -10, 10);
    std::cout << '\n';
	for (int n : arr)
		std::cout << n << ' ';
	std::cout << '\n';

	return 0;
}