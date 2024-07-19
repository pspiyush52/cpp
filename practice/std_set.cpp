#include <set>
#include <functional>
#include <cstring>
#include "stream_insert.h"

bool comp(int a, int b){ return a < b; }
bool str_comp(const char* x, const char* y){
	return std::strcmp(x, y) < 0;
}

typedef bool (*cstring_comparator)(const char*, const char*);

int main(void)
{
	// Specifying comparator using std::function wrapper
	std::set<int, std::function<bool(int, int)>> s(comp);
	s = {6, 1, 51, 4, 1, 63, 1, 6541, 13, 4};
    s.insert({65, 45, 1, 24, 54, 48, -1});
	using namespace __set__;
	std::cout << "Ascending ordered set: " << s << '\n';

	// If we want the ordering to be descending we can specify the
	// comparator using the built-in functor std::greater
	std::set<int, std::greater<int>> s2{6, 1, 51, 4, 1, 63, 1, 6541, 13, 4};
	std::cout << "Descending ordered set: " << s2 << '\n';

	// We can specify our own comparison function using function pointers
	std::set<const char*, cstring_comparator> names(str_comp);
	names = {"Niharika Singh", "Piyush Singh", "Pratima", "Milan Singh"};
	names.emplace("Seema Singh");
	std::cout << names << '\n';

	const char* new_name = "Niharika Singh";

	// The emplace method returns an std::pair object with first member
	// of type iterator to the set and the second member a boolean which
	// indicates whether the emplacement was successful or not.
	auto[iter, res] = names.emplace(new_name);
	if (res)
		std::cout << "Inserted " << new_name << " in the set.\n";
	else
		std::cout << "Insertion of " << new_name << " in the set failed.\n";
	
	return 0;
}