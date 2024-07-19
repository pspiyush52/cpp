#include <fstream>
#include "arr_string.h"
#include "crypt.h"

int main(int argc, char* argv[])
{
    if (argc == 2){
        string text;
        std::ifstream file(argv[1]);
        if (file){
            file >> text;
            std::cout << text.transform<perm_decrypt>() << '\n';
        }
        else
            std::cout << "File does not exist.\n";
        file.close();
    }
    else
        std::cout << "Usage: .\\decrypt.exe [filename.extension] [pass]\n";
    return 0;
}