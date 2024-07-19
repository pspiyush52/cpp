#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view sv {"Hello there."};
    std::cout << " sv : " << sv << std::endl;
    std::cout << " sv.data() : " << sv.data() << std::endl;
    std::cout << " std::size(sv) : " << std::size(sv) << std::endl;
    std::cout << " std::string_view::length() : " << sv.length() << std::endl;
    std::cout << " std::string_view::size() : " << sv.size() << std::endl;
    std::cout << " sv[2] : " << sv[2] << std::endl;
    std::cout << "\nRemoving 4 prefix characters and 1 suffix character : \n";
    sv.remove_prefix(4);
    sv.remove_suffix(1);
    std::cout << " sv : " << sv << std::endl;
    std::cout << " sv.data() : " << sv.data() << std::endl;
    std::cout << " std::size(sv) : " << std::size(sv) << std::endl;
    std::cout << " std::string_view::length() : " << sv.length() << std::endl;
    std::cout << " std::string_view::size() : " << sv.size() << std::endl;
    std::cout << " sv[2] : " << sv[2] << std::endl;
    char arr[] = "this is a character array";
    std::string_view sv2 {arr};
    std::cout << "sv2 : " << sv2 << std::endl;
    arr[3] = 'x';
    std::cout << "sv2 : " << sv2 << std::endl;
    return 0;
}