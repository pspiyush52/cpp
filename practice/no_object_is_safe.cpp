#include <iostream>
#include "arr_strings.h"

int main(void)
{
	string name{"Niharika Joshi"};
	
	void* ptr = &name;
	size_t size = *((size_t*)(((char**)(ptr)) + 1));
	size_t* p_size = ((size_t*)(((char**)(ptr)) + 1));
	char* str = *((char**)(&name));
	
    memcpy(str + 9, "Singh", 5);
	
    for (int i{}; i < size; i++)
		std::cout << str[i];
	
	std::cout << "\nsize: " << size << '\n';

    char** p_str = (char**)(ptr);
    free(*p_str);
    char str2[] = "Piyush Singh";
    *p_str = str2;
    *p_size = 12;
    
    std::cout << name << '\n';
    
    *p_str = nullptr;  // to prevent attempting to delete stack memory
	return 0;
}