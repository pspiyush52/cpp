#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main(void)
{
	long long seed{std::time(0)}, a{71}, b{37}, from{50}, to{1000};
	for (int i{}; i < 10; ++i){
		seed = from + (std::abs((a * seed + b) % (to - from)));
		std::cout << seed << "  ";
	}
	return 0;
}