#include <iostream>
#include <iomanip>
#include <map>
#include "stream_insert.h"

int main(void)
{
	// Multimap allows insertion of duplicate values
	std::multimap<unsigned int, const char*> books;
	books.emplace(1718, "Oedipus");
	books.insert({
		std::make_pair(1667, "Paradise Lost"),
		std::make_pair(1601, "Hamlet"),
		std::make_pair(1902, "The Power of Darkness"),
		std::make_pair(1611, "Tempest"),
		std::make_pair(1859, "A Tale of Two Cities"),
		std::make_pair(1880, "The Brothers Karamazov"),
		std::make_pair(1766, "The Vicar of Wakefield"),
		std::make_pair(1859, "On the Origin of Species")
	});
	using namespace __multimap__;
	std::cout << books << '\n';

    std::cout << "+------+------------------------------------------+\n";
    std::cout << "| Year | " << std::setw(40) << "Book                  " << " |";
    std::cout << "\n+------+------------------------------------------+";
    std::cout << '\n';
    for (auto& [year, book] : books)
        std::cout << "| " << year << " | " << std::setw(40) << book << " |\n";
    std::cout << "+------+------------------------------------------+";
	
	return 0;
}