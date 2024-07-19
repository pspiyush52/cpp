#include <iostream>
#include <iomanip>
#include <optional>
#include <string_view>

std::optional<size_t> find_char(std::string_view sv, char c = 'a');

int main(void)
{
    std::string str {"this is a sample string to test the function."};
    // std::string_view str {"this is a sample string to test the function."};
    // const char* str {"this is a sample string to test the function."};
    char ch {'l'};

    std::cout << "The string : " << std::quoted(str) << std::endl;
    
    std::optional<size_t> index = find_char(str, ch);
    // std::optional<size_t> index = find_char("this is a sample string", ch);
    
    if (index.has_value())
        std::cout << "Character \'" << ch << "\' found at index : " << index.value() << std::endl;
    else
        std::cout << "Character \'" << ch << "\' not found in the string." << std::endl;
    
    return 0;
}

std::optional<size_t> find_char(std::string_view sv, char c)
{
    char cur;
    for (size_t i{}; (cur = sv[i]) != '\0'; i++)
        if (cur == c)
            return i;
    return {};
}