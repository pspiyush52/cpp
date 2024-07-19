#include "char_counter.h"

int main(int argc, char* argv[])
{
    if (argc == 2){
        Counter c{argv[1]};
        std::cout << c << '\n' << c.size() << '\n';
    }
    else{
        Counter c("this is an example string to demonstrate the counter");
        std::cout << c << '\n' << c.size() << '\n';
    }
    return 0;
}