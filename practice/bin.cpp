#include <cstdlib>
#include "print.h"

int hamming{};
void bin(unsigned int n) {
	if (n) {
		bin(n >> 1);
		std::cout << (n & 1);
	}
}
void sbin(int n) {
	int shift{31};
	for (; shift >= 0; --shift)
		std::cout << ((n & (1 << shift)) ? (++hamming, "1") : "0");
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		print("Missing numeric arg");
		std::exit(EXIT_FAILURE);
	}
	int n{std::stoi(argv[1])};
	std::cout << "Condensed form:  ";
	bin(n);
	std::cout << "\n   32-bit form:  ";
	sbin(n);
	print("\nHamming weight: ", hamming);

	return 0;
}
