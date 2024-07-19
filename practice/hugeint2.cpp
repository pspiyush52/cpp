#include <iostream>
#include "hugeint.h"

int main(void)
{
	h_int x, y;
	std::cout << "Enter x: ";  std::cin >> x;
	std::cout << "Enter y: ";  std::cin >> y;
	std::cout << " x + y = " << x + y;
	return 0;
}