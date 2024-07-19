#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(std::time(0));
	int min{10}, max{1000};
	double A{0.6180339887498949}, rnum;
	for (int i{}; i < 10; ++i){
		rnum = std::rand() * A;
		rnum -= static_cast<int>(rnum);
		std::cout << (min + static_cast<int>(rnum * max)) << "  ";
	}
	return 0;
}