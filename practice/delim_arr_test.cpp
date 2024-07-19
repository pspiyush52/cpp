#define NO_UNIQUE_PTR

#include <iostream>
#include "delim_arr.h"
#include "stream_insert.h"

int main(void)
{
	unsigned int uarr[] = {65, 48, 1, 21, 77, 87, 12, UINT_MAX};
	using namespace delim_arr;
	std::cout << uarr << '\n';

#ifndef NO_UNIQUE_PTR
	del::array<int> arr2 = i::make_array(15, 10);
#else
	int* arr2 = i::make_array(15, 10);
#endif  // NO_UNIQUE_PTR

	std::cout << (arr2) << '\n';

#ifndef NO_UNIQUE_PTR
	del::array<unsigned int> arr3 = ui::make_array(10, 20);
#else
	unsigned int* arr3 = ui::make_array(10, 20);
#endif  // NO_UNIQUE_PTR
	
	std::cout << arr3 << '\n';

#ifdef NO_UNIQUE_PTR
	delete[] arr2;
	delete[] arr3;
#endif  // NO_UNIQUE_PTR

	return 0;
}