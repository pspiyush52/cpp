#include <iostream>
#include "defs.h"
#include <cstring>

//using namespace std;

int main(void)
{
    newline;
    const char* str = "This is a sample text to test the strchr function of cstring library.";
    const char* result = str;
    char target = 't';
    unsigned short count = 0;
    while ((result = strchr(result, target)))
    {
        cout << "Found " << target << " starting at - " << result << endl;
        result++;
        count++;
    }
    cout << "\nTotal " << target << "\'s in the string : " << count << endl;
    return 0;
}