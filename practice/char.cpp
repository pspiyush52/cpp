#include "my.h"
#include <cctype>

using namespace std;

int main(void)
{
    char s[50];
    cout << "Enter some text : ";
    fgets(s, 50, stdin);
    unsigned char size = std::size(s);
    for (char ch : s)
    {
        if (!ch)
            break;
        if (std::isalpha(ch))
            cout << "Alphabet : " << ch;
        else if (std::isspace(ch))
            cout << "Whitespace character" << endl;
        else if (std::isdigit(ch))
            cout << "Numeric character : " << ch << endl;
        
        if (std::islower(ch))
            cout << " lowercase" << endl;
        else if (std::isupper(ch))
            cout << " uppercase" << endl;
    }
    cout << endl << "The string with flipped case : ";
    for (char ch : s)
    {
        if (!ch)
            break;
        if (std::islower(ch))
            cout << (char) std::toupper(ch);
        else if (std::isupper(ch))
            cout << (char) std::tolower(ch);
        else
            cout << (char) ch;
    }
    
    char* left = s;
    char* right = s;
    char tmp;
    while (*right++ != 0);
    right -= 2;
    if (*right == '\n')
        *right-- = 0;
    while (left < right)
    {
        tmp = *right;
        *right-- = *left;
        *left++ = tmp;
    }
    cout << "\nReversed string : " << s << endl;
    return 0;
}