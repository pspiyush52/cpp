#include <iostream>
#include <streambuf>

std::ostream& cur(std::ostream& output){
    output.setf(std::ios::showpos);
	output << "INR ";
	output.fill('x');
	output.width(10);
	return output;
}

int main(void)
{
	int bal{5154};
	std::cout << "Account balance is : " << cur << bal << '\n';
	return 0;
}