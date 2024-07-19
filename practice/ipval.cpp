#include "arr_string.h"

int main(int argc, char* argv[])
{
	string ip_addr;
	if (argc == 2)
		ip_addr = argv[1];
	else
		ip_addr = "192.168.10.11";
	auto components = ip_addr.split('.');
	try{
		string binary_address{
			components[0].bstring(8) + "." +
			components[1].bstring(8) + "." +
			components[2].bstring(8) + "." +
			components[3].bstring(8)
		};
		std::cout << "Address in binary format: " << binary_address << '\n';
	}
	catch(ValueError&){
		std::cout << "Invalid address.\n";
	}
	return 0;
}