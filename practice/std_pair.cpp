#include <iostream>
#include <utility>

struct Point{
	double x{};
	double y{};
};

int main(void)
{
	std::pair<int, const char*> first{1, "Niharika Joshi"};
	auto second = std::make_pair(2, "Piyush Singh");

	auto[num1, str1] = first;
	auto show = [](const int& num, const char* str){
		std::cout << "num:  " << num << ", str:  " << str << '\n';
	};
	show(num1, str1);

	auto[num2, str2] = second;
	show(num2, str2);

	Point p{1.2, 4};
    // Binding references
	auto& [x, y] = p;
	x = 10;  y = 20;
	std::cout << "p.x: " << p.x << ", p.y: " << p.y << '\n';

	Point points[]{{1, 2}, {-4, 3.7}, {12, 10}, {3.4, 0.79}, {-12.14, -6}, {4, 5}, {33, 1}};
    std::cout << "Points:\n";
	for (auto[x, y] : points)
		std::cout << "    [" << x << ", " << y << "]\n";
	
	return 0;
}