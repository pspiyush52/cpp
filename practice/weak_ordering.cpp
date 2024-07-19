#include "utils.h"
class string {
    public:
        string(const char* str) : data(str){}
        std::weak_ordering operator<=>(const string& rhs) const;
        std::weak_ordering operator<=>(const char* rhs) const;
        bool operator==(const string& rhs) const;
        bool operator==(const char* rhs) const;
        
    private:
        const char* data;
};

int main(void)
{
    const string str1{"some"};
    const string str2{"soMe"};
    std::cout << "str1 == \"SOME\" : " << std::boolalpha << (str1 == "SOME") << '\n';
    std::cout << "\"SOME\" == str2 : " << ("SOME" == str2) << '\n';
    std::cout << "\"SOME\" < str2 : " << ("SOME" < str2) << '\n';

    std::cout << "str1 < \"somp\" : "  << (str1 < "somp") << '\n';
    auto result = (str1 <=> "somp");
    std::cout << "str1 < \"somp\" : "  << (result < 0) << '\n';

    return 0;
}

std::weak_ordering string::operator<=>(const string& rhs) const {
    int result = sut::strcmpi(data, rhs.data);
    if (result > 0)
        return std::weak_ordering::greater;
    else if (result < 0)
        return std::weak_ordering::less;
    else
        return std::weak_ordering::equivalent;
}

std::weak_ordering string::operator<=>(const char* rhs) const {
    int result = sut::strcmpi(data, rhs);
    if (result > 0)
        return std::weak_ordering::greater;
    else if (result < 0)
        return std::weak_ordering::less;
    else
        return std::weak_ordering::equivalent;
}

bool string::operator==(const string& rhs) const {
    return (!sut::strcmpi(data, rhs.data));
}

bool string::operator==(const char* rhs) const {
    return (!sut::strcmpi(data, rhs));
}