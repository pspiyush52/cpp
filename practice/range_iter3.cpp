#include <iostream>
#include <vector>
#include "range.h"
#include "view.h"

int main(void)
{
	auto odds = [](long long x){ return ((x % 2) != 0); };
	for (int num : range(12, 54) | odds)
		std::cout << num << ' ';
	
	std::vector<int> nums{45, 21, 57, 83, 78, 6, 54};
	std::cout << '\n' << (nums | odds) << '\n';

	View v = range(45, 150) | [](long long n){
		return ((n % 15) == 0);
	};

	std::cout << '\n' << v << '\n';

	return 0;
}