#include <iostream>
#include "stack.h"

int main(void)
{
	Stack<int> s;
	s.push(4);
	s.push(9);
	s.push(12);
	s.push(7);
	s.push(22);
	s.push(14);
	s.pop();
	s.push(2);
	std::cout << "Stack:\n " << s << '\n';

	Stack<int> copy{s};
	return 0;
}