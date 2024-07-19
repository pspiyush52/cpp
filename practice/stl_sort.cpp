#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include "arr_string.h"
#include "stream_insert.h"

int main(void)
{
	auto data = {676, 14, 218, 78, 65, 18, 112, 49, 132, 411, 179};
	int list[] = {6, 4, 8, 7, 65, 18, 74, 6, 2, 41, 17, INT_MIN};
	using namespace delim_arr;
	std::cout << "List before sorting : " << list << '\n';
	std::sort(std::begin(list), std::end(list) - 1);
	std::cout << "List after sorting : " << list << '\n';

	std::vector<int> nums{std::begin(data), std::end(data)};
	using namespace __vec__;
	std::cout << "\nVector before sorting : " << nums << '\n';
	std::sort(nums.begin(), nums.end());
	std::cout << "Vector after sorting : " << nums << '\n';
	std::sort(nums.begin(), nums.end(), std::greater<int>());
	std::cout << "Vector after sorting (descending) : " << nums << '\n';

	std::vector<string> names;
	names.push_back("Niharika Joshi");
	names.push_back("Piyush Singh");
	names.push_back("Steve Rogers");
	names.push_back("Tommy Conlan");
	names.push_back("Valentina Petrova");
	names.push_back("Sam Billings");

	std::cout << "\nNames before sorting : " << names << '\n';
	// std::sort(names.begin(), names.end());
	std::ranges::sort(names);
	std::cout << "Names after sorting : " << names << '\n';
	std::sort(names.begin(), names.end(), std::greater<string>());
	std::cout << "Names after sorting (descending) : " << names << '\n';

	return 0;
}