#include <iostream>
#include <set>
#include <cstring>
#include "stream_insert.h"

bool scomp(const char* x, const char* y);
typedef bool (*cstring_comparator)(const char*, const char*);

int main(void)
{
	std::set<const char*, cstring_comparator> names(scomp);

	/*std::set<const char*, cstring_comparator> names([](const char* x, const char* y){
		return std::strcmp(x, y) < 0;
	});*/
	
	names.insert({"Niharika", "Piyush", "Sarah", "Xander", "Zemo", "Steve", "Ram Khilavan"});
	using namespace __set__;
	std::cout << "Names:  " << names << '\n';
	return 0;
}

bool scomp(const char* x, const char* y){
	return std::strcmp(x, y) < 0;
}