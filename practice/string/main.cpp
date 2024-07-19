#include "string.h"

int main(void)
{
    auto det = [](string& s){
        std::cout << s << '\n';
        std::cout << s.size() << ' ' << s.capacity() << '\n';
    };
    string s{"         this    is a    string   "};
    det(s);
    det(s.collapse());
    return 0;
}