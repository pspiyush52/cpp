#include <fstream>
#include "string.h"

int main(int argc, char* argv[])
{
    string in, q;
    if (argc >= 2){
        string fopt{"-f"};
        if (fopt.similar(argv[1])){
            std::ifstream file(argv[2]);
            if (!file){
                if (argv[2] == 0){
                    std::cout << "No file name specified\n";
                    return 1;
                }
                std::cout << "Error while opening " << argv[2] << '\n';
                return 2;
            }
            file >> in;
        }
        else{
            std::cout << "Invalid option\n";
            return 3;
        }
    }
    else{
        std::cout << "Enter or paste text: ";
        get(in);
        in.strip();
    }
    std::cout << "\nEnter the query string: ";
    std::cin >> q;
    string::index_list li = in.search_all_i(q);
    std::cout << '\n' << q << " appears a total of "
        << li.size() << " times in the text at the following positions:\n\n";
    std::cout << li << '\n';
    return 0;
}