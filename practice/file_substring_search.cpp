#include <fstream>
#include "arr_string.h"

int main(void)
{
	string text, query;
	size_t count{};
	std::cout << "Enter the file name to search: ";
	std::cin >> text;
	std::ifstream file(text.c_str());
	if (!file){
		std::cout << "Error while opening " << text << '\n';
		file.close();
		return 0;
	}
	file >> text;
	std::cout << "\nEnter the query: ";
	std::cin >> query;
	if ((count = text.counti(query)))
		std::cout << "Query occurs in the string " << count <<  " times.\n";
	else
		std::cout << "Query does not exist in the string.\n";
	file.close();
	return 0;
}