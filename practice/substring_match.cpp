#include <iostream>

bool __contains(const char* str, const char* pattern){
	if (!(*str))
		return false;
	const char* p = pattern;
	for (; *str && (*str != *p); ++str);
	for (; *str && *p && (*str == *p); ++str, ++p);
	if (*p == 0)
		return true;
	else
		return __contains(str, pattern);
}

bool contains(const char* str, const char* pattern){
	if (*pattern)
		return __contains(str, pattern);
	return false;
}

int main(int argc, char* argv[])
{
	const char* str = "bababdacbcabcadc";
	const char* pattern = "cabcab";
	std::cout << std::boolalpha << contains(str, pattern) << '\n';
	return 0;
}