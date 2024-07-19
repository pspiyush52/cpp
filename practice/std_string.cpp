#include <iostream>
#include <string>

int main(void)
{
    std::string str {"object oriented programming"};
    std::cout << str << std::endl;

    // when used with a string variable, it takes all characters except the first four
    std::string str2 {str, 4};
    std::cout << str2 << std::endl;

    // when used with a string literal, it takes the first four characters
    std::string str3 {"Hello there", 4};
    std::cout << str3 << std::endl;

    // same with functional initialization
    std::string str4 (str, 4);
    std::cout << str4 << std::endl;

    std::string str5 ("Hello there", 4);
    std::cout << str5 << std::endl;

    // start from 5th position and take 10 characters
    std::string str6 {str, 5, 10};
    std::cout << str6 << std::endl;

    // this behaves the same with string literals as well
    std::string str7 {"object oriented programming", 5, 10};
    std::cout << str7 << std::endl;

    std::string str8 (3, 'r');
    std::cout << str8 << std::endl;

    // concatenation
    std::string str9 = str5 + str8;
    std::cout << str9 << std::endl;

    // using the append method
    std::cout << str5.append(str8) << std::endl;

    // appending 5 '?' characters using append() method
    std::cout << str.append(5, '?') << std::endl;

    // appending a section of string with append()
    std::cout << str5.append(str, 7, 5) << std::endl;

    // appends all characters from str except the first 10
    std::cout << str8.append(str, 10) << std::endl;

    // appends the first four characters from the string literal
    std::cout << str9.append("something", 4) << std::endl;

    // characters can be concatenated to std::strings as well
    std::cout << str9 + '*' << std::endl;

    // std::string can also be initialized with a const char* or a char array
    const char* cstr = "cstring";
    std::string str10 {cstr};
    std::cout << str10 << std::endl;

    char cstr2[] = "sometext";
    std::string str11 {cstr2};
    std::cout << str11 << std::endl;

    // size() method returns the size of the string excluding the null terminating character
    std::cout << "str.size() : " << str.size() << std::endl;

    // Accessing and Modifying characters at specific positions in std::string

    str[0] = '0';           // using square brackets
    str.at(1) = 'B';        // using at() method
    std::cout << str << std::endl;

    // front and back characters using the respective methods
    std::cout << "str.front() : " << str.front() << std::endl;
    std::cout << "str.back() : " << str.back() << std::endl;

    // front can be modfied as well
    str.front() = 'L';
    std::cout << str << std::endl;

    // the c_str() method returns a const char* to the c string wrapped by the std::string
    // it returns a pointer to the underlying character array
    const char* wrapped_string = str.c_str();
    std::cout << "wrapped_string using str.c_str() : " << wrapped_string << std::endl;
    // the returned pointer cannot be used to modify the string as it returns a const*

    // the data() method on the other hand returns a non-const pointer which can be used to
    // modify the string
    char* data = str.data();
    data[7] = 'e';
    data[16] = 'x';
    std::cout << "str.data() after modification : " << data << std::endl;

    std::cout << "str.capacity() : " << str.capacity() << std::endl;
    std::cout << "str.max_size() : " << str.max_size() << std::endl;

    return 0;
}