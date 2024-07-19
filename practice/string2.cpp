#include <iostream>
#include <iomanip>
#include <string>

int main(void)
{
    std::string str;
    std::cout << "\nstr is empty : " << std::boolalpha << str.empty() << std::endl;

    // str.capacity() method returns the maximum number of characters that the current array
    // can hold before it needs to expand
    std::cout << str.capacity() << std::endl;
    str.append("x");
    std::cout << str.capacity() << std::endl;

    // reserves the array size to 100 so that frequent resizes are not required
    str.reserve(100);
    for (int i{}; i < 500; i++)
    {
        // appends a single character to the string
        str.push_back('x');
        if (!(i % 50))
            std::cout << "capacity after appending " << (i+1) << " times : " << str.capacity() << std::endl;
    }

    // shrinks the char array to the current size of the string
    std::cout << "\nstr.size() : " << str.size() << std::endl;
    str.shrink_to_fit();
    std::cout << "str.capacity() after shrinking to fit : " << str.capacity() << std::endl;
    str.append("x");
    std::cout << "str.capacity() after appending a single character string : " << str.capacity() << std::endl;
    str.shrink_to_fit();
    std::cout << "str.capacity() after shrinking to fit : " << str.capacity() << std::endl;
    str.clear();
    std::cout << "\nAfter str.clear() : " << std::endl;
    std::cout << "str.size() : " << str.size() << std::endl;
    std::cout << "str.capacity() : " << str.capacity() << std::endl;
    str.shrink_to_fit();
    std::cout << "str.capacity() after calling shrink_to_fit() : " << str.capacity() << std::endl;

    std::string msg {"random text string to test the capacity"};
    std::cout << "\nmsg : " << std::quoted(msg) << std::endl;
    msg.append("hello");
    std::cout << "msg.size() : " << msg.size() << std::endl;
    std::cout << "msg.length() : " << msg.length() << std::endl;
    std::cout << "msg.capacity() : " << msg.capacity() << std::endl;
    msg.shrink_to_fit();
    std::cout << "msg.capacity() after shrinking to fit : " << msg.capacity() << std::endl;

    std::string s;
    std::cout << "\nBuilding a string using the += compound operator to append to it : " << std::endl;
    s += "This ";
    std::cout << std::quoted(s) << std::endl;
    s += "is ";
    std::cout << std::quoted(s) << std::endl;
    s += 'a';
    std::cout << std::quoted(s) << std::endl;
    s += " string.";
    std::cout << std::quoted(s) << std::endl;

    // taking input with spaces (not possible with std::cin >>)
    std::string name;
    std::cout << "\nEnter your name : ";
    std::getline(std::cin, name);
    std::cout << "Goodbye, ";
    if (name.empty())
        std::cout << "no name.";
    else
        std::cout << name;
    std::cout << std::endl;

    return 0;
}