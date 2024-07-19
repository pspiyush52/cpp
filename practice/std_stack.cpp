#include <iostream>
#include <ctime>
#include <stack>
#include "utils.h"
#include "stream_insert.h"

int main(void)
{
	std::srand(std::time(0));
	std::stack<int> s;
	repeat(10) s.push(std::rand() % 100);
	using namespace __stack__;
	std::cout << s << newl;
	s.pop();
	std::cout << s << newl;
	s.pop();
	std::cout << s << newl;
	s.pop();
	std::cout << s << newl;
	s.push(111);
	std::cout << s << newl;
	s.pop();
	std::cout << s << newl;
	return 0;
}