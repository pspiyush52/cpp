#include "my.h"
#include <cstring>

int main(void)
{
    const char* string1 = "String 1";
    char* ptr = std::strchr(string1, 'r') + 1;
    nl
    cout << string1 << endl;
    cout << ptr << endl;

    std::string s1(30, '-'); // create a string with '-' character repeated 30 times
    cout << s1 << endl;

    std::string s2 {"sample string", 3, 5};  // start at index 3, take 5 characters
    cout << s2 << endl;

    std::string s3 {"another sample string", 5}; // take 5 characters from the beginning of the string
    cout << s3 << endl;
    
    return 0;
}