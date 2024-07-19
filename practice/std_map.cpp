#include <map>
#include <cstring>
#include "stream_insert.h"

typedef bool (*string_comparator)(const char*, const char*);

int main(void)
{
	std::map<const char*, unsigned int, string_comparator> people(
		[](const char* x, const char* y){
			return std::strcmp(x, y) < 0;
		}
	);
	people.emplace("Niharika Singh", 31);

	auto show_status = [](std::map<const char*, unsigned int, string_comparator>::iterator& t, bool res){
			if (res)
				std::cout << "Inserted " << t->first << " into the map.\n";
			else
				std::cout << "Failed to insert " << t->first << " into the map.\n";
		};
	
	auto&&[k, r] =  people.emplace(std::make_pair("Piyush Singh", 27));
	show_status(k, r);

	// To check the result of the insertion
	auto&& [key, res] =  people.insert(std::pair<const char*, unsigned int>("Steve Rogers", 150));
	if (res)
		std::cout << "Inserted " << key->first << " into the map.\n";
	else
		std::cout << "Failed to insert " << key->first << " into the map.\n";
	
	people.insert({
		std::pair<const char*, unsigned int>("Zemo", 38),
		std::pair("Ram Khilavan", 45),
		std::pair("Sarah Taylor", 38)
	});
	using namespace __map__;
	std::cout << "People:  " << people << '\n';

	std::cout << "\nRange based loop:\n";
	for (auto& [key, value] : people)
		std::cout << " {" << key << ", " << value << "}\n";

	std::cout << "\nRange based loop without using auto binding:\n";
	for (const std::pair<const char*, unsigned int>& item : people)
		std::cout << " {" << item.first << ", " << item.second << "}\n";

	std::cout << "\nLoop using iterator:\n";
	std::map<const char*, unsigned int>::iterator iter = people.begin();
	for (; iter != people.end(); ++iter)
		std::cout << " {" << iter->first << ", " << iter->second << "}\n";
	return 0;
}