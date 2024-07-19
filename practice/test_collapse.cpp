#include "arr_string.h"
#define DELIM_BEGIN "!----"
#define DELIM_END "----!"

int main()
{
	string strings[] = {
		"",
		" ",
		"       ",
		"  \n  ",
		"\n\n\n\n",
		"this is some text",
		"   this is some text",
		"this is some text     ",
		"            this is some text     ",
		"         this    is      some         text           ",
		"word",
		"           word",
		"word                 ",
		"       word           "
	};
	
	auto glwr = [](string& str){
		std::cout << "For" << DELIM_BEGIN << str << DELIM_END;
		string res{str.collapsed()};
		if (res)
			std::cout << DELIM_BEGIN << res << DELIM_END;
		else
			std::cout << "<empty>";
		std::cout << '\n';
	};

	for (string& s : strings)
		glwr(s);
	
	return 0;
}