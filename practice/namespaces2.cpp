#include <iostream>
#include <cstring>

using namespace std;

class string{
    public:
        string(const char* s){
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }
        char* c_str(){
            return str;
        }
        ~string(){
            delete[] str;
        }
    private:
        char* str;
};

int main(void)
{
    // will create a string object of the string class defined above
    ::string str{"sample string"};
    cout << "string : " << str.c_str() << endl;

    // will create a string object of the string class defined in std
    std::string str2{"sample string 2"};
    cout << "string 2 : " << str2 << '\n';

    return 0;
}