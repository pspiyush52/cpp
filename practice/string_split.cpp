#include "string.h"

int main(int argc, char* argv[])
{
    if (argc == 2){
        string arg{argv[0]};
        arg.pop_backn(8);
        std::cout << arg;
    }
    return 0;
}