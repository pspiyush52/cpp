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
		"         this is some text           ",
		"word",
		"           word",
		"word                 ",
		"       word           "
	};
	
	auto tester = [](string& str){
		string res{str.first_word()};
        std::cout << "For" << DELIM_BEGIN << str << DELIM_END;
		if (res)
			std::cout << DELIM_BEGIN << res << DELIM_END;
		else
			std::cout << "<empty>";
        std::cout << '\n';
	};

	for (string& s : strings)
		tester(s);
	
	return 0;
}