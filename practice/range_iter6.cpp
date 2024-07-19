#include <iostream>
#include <cctype>
#include "arr_string.h"
#include "functors.h"
#include "view.h"
#include "range.h"

struct upper{
	bool operator()(char& ch){
		return ((ch >= 65) && (ch <= 90));
	}
};

int main(void)
{
	string name{"Niharika Joshi"};
	std::cout << (name | upper()) << '\n';
	View<string, upper> uppers(name);
	std::cout << uppers << '\n';

	string random('-', 10);
	rand_range('a', 'z') >> random;
	std::cout << random << '\n';
	return 0;
}