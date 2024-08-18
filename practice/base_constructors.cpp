#include "utils.h"
#include "plist.h"
#include "../deque/deque.h"

class string : public deque<char> {
    typedef                deque<char>                base;
    public:
        string(): base() {}
        string(const char* str) {
            while (*str)
                this->push_back(*str++);
        }
        string(const string& src): base(static_cast<const base&>(src)) {}
        string(string&& src): base(static_cast<base&&>(src)) {}
        string& operator=(const string& src) {
            if (this != &src)
                *(static_cast<base*>(this)) = static_cast<const base&>(src);
            return *this;
        }
        string& operator=(string&& src) {
            if (this != &src)
                *(static_cast<base*>(this)) = static_cast<base&&>(src);
            return *this;
        }
        string operator+(const string& str) const {
            string res{*this};
            for (char ch : str)
                res.push_back(ch);
            return res;
        }
        string operator+(const char* str) const {
            string res{*this};
            while (*str)
                res.push_back(*str++);
            return res;
        }
        string& operator+=(const string& str) {
            for (char ch : str)
                this->push_back(ch);
            return *this;
        }
        string& operator+=(const char* str) {
            while(*str)
                this->push_back(*str++);
            return *this;
        }
        string& collapse() {
            int arr_size = this->capacity() + 1;
            int i = this->Front(), count{};
            i = (i == 0) ? (arr_size - 1) : (i - 1);
            for (int j{}; j < this->size(); ++j) {
                for (; j < this->size() && (*this)[j] == ' '; ++j);
                (*this)[i] = ' ';
                i = (i + 1) % arr_size;
                ++count;
                for (; j < this->size() && (*this)[j] != ' '; ++j) {
                    (*this)[i] = (*this)[j];
                    i = (i + 1) % arr_size;
                    ++count;
                }
            }
            this->setFront(0);
            this->setCur(count);
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const string& s) {
            for (auto c : s)
                out << c;
            return out;
        }
};

PList<string> split(const string& str, char sep=' ') {
    PList<string> strings;
    string first;
    int i{};
    for (; i < str.size() && str[i] != sep; ++i)
        first.push_back(str[i]);
    strings.emplace(static_cast<string&&>(first));
    while (i < str.size()) {
        if (str[i] == sep) {
            string s;
            for (++i; i < str.size() && str[i] != sep; ++i)
                s.push_back(str[i]);
            strings.emplace(static_cast<string&&>(s));
        }
        else
            ++i;
    }
    
    return strings;
}

int main(void)
{
    const char* arr[] = {"Shyam", "Sundar", "Bipasha", "Murali", "Leela"};
    PList<string> names(3);
    for (int i{}; i < 11; ++i)
        names.emplace(arr[i % 5]);
    print(names);
    PList<string> books = split(
        "CLRS_Object Oriented Programming and It's Applications_Servlets & JSP_Introduction to Calculus_Linear Algebra"
    , '_');
    print("Books to study:");
    for (string& book : books)
        print('\t', book);
    return 0;
}
