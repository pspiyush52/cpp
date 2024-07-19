#include <fstream>
#include "arr_string.h"
#include "crypt.h"

int main(int argc, char* argv[])
{
    if (argc == 2){
        std::ifstream file(argv[1]);
        if (file){
            string text, filename{argv[1]}, name, extension;
            string::string_list parts{filename.split('.')};
            std::ofstream out;
            if (argv[1][0] == '.'){
                name = std::move(parts[1].from_pos(1));
                extension = std::move(parts[2]);
            }
            else{
                name = std::move(parts[0]);
                extension = std::move(parts[1]);
            }
            out.open((name + "_encrypted." + extension).c_str(), std::ios::out);
            file >> text;
            out << text.transform<perm_encrypt>();
            out.close();
        }
        else
            std::cout << "File does not exist.\n";
        file.close();
    }
    else
        std::cout << "Usage: .\\encrypt.exe [filename.extension]\n";
    return 0;
}