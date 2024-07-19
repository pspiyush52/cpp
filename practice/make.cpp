#include "string.h"
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc != 2){
		std::cout << "Usage: make [filename without extension]";
		return 1;
	}
	string arg{argv[1]};
	if (arg.contains('.')){
		std::cout << "Enter file name without extension.";
		return 2;
	}
	string dir{argv[0]}, filename{arg + ".cpp"};
	dir.pop_backn(8);
	std::ifstream file(filename.get_str().c_str());
	if (!file){
		std::cout << "Error while opening " << filename << '\n';
		return 3;
	}
	string line, command{"g++ -std=c++20 -O2 -DNDEBUG " + dir + filename};
	while (getline(file, line)){
		if (line){
			line.pop_front();
			if (line.slice(7).similar("include")){
				string::string_list li = line.split();
				if (li.size() == 2){
					if (li[1][-1] == '"'){
						string included_file = (li[1]).pop_back().pop_front();
						string::string_list flist = included_file.split('.');
						if (flist.size() == 2){
							string fname{flist[0] + ".cpp"};
							std::ifstream header_file(fname.get_str().c_str());
							if (header_file){
								command += (" " + dir + fname);
							}
							header_file.close();
						}
					}
				}
			}
		}
	}
    file.close();
    command += (" -o " + dir + arg + ".exe");
	system(command.get_str().c_str());
	return 0;
}