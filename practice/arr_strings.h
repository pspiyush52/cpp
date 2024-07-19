#ifndef __ARR_STRINGS_H
#define __ARR_STRINGS_H

#include "arrs.h"
#include <cstring>
#include "utils.h"

class string : public arr::Array<char> {
    public:
        string();
        string(const char* str);
        string(const std::string& str);
        string(const string& src);
        string(string&& src);

        bool is_empty() const;

        // Create and return a new string with all characters in lowercase.
        string get_lower() const;
        // Create and return a new string with all characters in uppercase.
        string get_upper() const;

        // Make the string lowercase in place and return a reference to the
        // current string object.
        string& to_lower();
        // Make the string uppercase in place and return a reference to the
        // current string object.
        string& to_upper();

        string& reverse();

        // Perform case insensitive comparison of two strings.
        bool similar(const string& rhs) const;
        bool similar(const char* rhs) const;

        // Return the number of appearances of character ch in the string.
        size_t count(char ch) const;

        // Return a new string containing n characters from the start of the
        // current string.
        string operator()(size_t n) const;
        // Return a new string containing characters from the current string
        // starting from index start, going up to end.
        string operator()(size_t start, size_t end) const;

        // Return a new string containing n characters from the start of the
        // current string.
        string slice(size_t end) const;
        // Return a new string containing characters from the current string
        // starting from index start, going up to end.
        string slice(size_t start, size_t end) const;

        // Defining the three way comparison operator provides the
        // ability to use '<', '<=', '>', '=>' operators on our strings
        friend std::strong_ordering operator<=>(const string& lhs, const string& rhs);
        friend std::strong_ordering operator<=>(const string&lhs, const char* rhs);

        // Operator == tests for strict equality (case sensitive).
        friend bool operator==(const string& lhs, const string& rhs);
        friend bool operator==(const string& lhs, const char* rhs);

        // Operator + concatenates two strings
        friend string operator+(const string& lhs, const string& rhs);
        friend string operator+(const string& lhs, const char* rhs);
        friend string operator+(const char* lhs, const string& rhs);

        string& operator+=(const char* rhs);
        string& operator+=(const string& rhs);

        // Access elements of the string using array index notation.
        char& operator[](size_t i);
        const char& operator[](size_t i) const;

        string& operator=(const char* str);
        string& operator=(const string& str);
        string& operator=(string&& str);

        operator std::string_view();

        template<typename U>
        requires std::is_integral_v<U>
        friend string to_string(U num);

        template<typename U>
        requires std::is_floating_point_v<U>
        friend string to_string(U num);

        friend std::ostream& operator<<(std::ostream& output, const string& str);
        friend std::istream& operator>>(std::istream& input, string& str);
    
    private:
        string(size_t size) : arr::Array<char>(size){}
};

class __string_input_buffer{
    public:
        __string_input_buffer() : buffer_size(100), cur(0), buf(new char[100]){}
        void insert(const char& ch){
            if (cur >= buffer_size)
                this->__buffer_expand();
            buf[cur++] = ch;
        }
        void terminate(){
            if (cur >= buffer_size)
                this->__buffer_expand();
            buf[cur] = '\0';
        }
        const char* get_str(){
            if (cur >= buffer_size)
                this->__buffer_expand();
            buf[cur] = '\0';
            return buf;
        }
        unsigned int size(){
            return cur;
        }
    
    private:
        char* buf;
        unsigned int cur;
        unsigned int buffer_size;
        
        void __buffer_expand(){
            char* newbuf = new char[buffer_size * 2];
            memcpy(newbuf, buf, buffer_size);
            buffer_size *= 2;
            delete[] buf;
            buf = newbuf;
        }
};

string::string() : arr::Array<char>(0){
    arr = nullptr;
    arr_size = 0;
}

string::string(const char* str) : arr::Array<char>(std::strlen(str)){
    memcpy(arr, str, arr_size);
}

string::string(const std::string& str) : arr::Array<char>(str.size()){
    memcpy(arr, str.c_str(), str.size());
}

string::string(const string& src) : arr::Array<char>(src){}

string::string(string&& src) : arr::Array<char>(std::move(src)){}

bool string::is_empty() const{
    return (arr == nullptr);
}

string string::get_lower() const {
    string tmp{arr_size};
    for (size_t i{}; i < arr_size; i++)
        tmp.arr[i] = sut::tolower(arr[i]);
    return tmp;
}

string string::get_upper() const {
    string tmp{arr_size};
    for (size_t i{}; i < arr_size; i++)
        tmp.arr[i] = sut::toupper(arr[i]);
    return tmp;
}

string& string::to_lower(){
    for (size_t i{}; i < arr_size; i++)
        arr[i] = sut::tolower(arr[i]);
    return *this;
}

string& string::to_upper(){
    for (size_t i{}; i < arr_size; i++)
        arr[i] = sut::toupper(arr[i]);
    return *this;
}

string& string::reverse(){
    if (arr_size < 2)
        return *this;
    char* front = arr;
    char* rear = arr + (arr_size - 1);
    char tmp;
    for (; front < rear; front++, rear--){
        tmp = *front;
        *front = *rear;
        *rear = tmp;
    }
    return *this;
}

bool string::similar(const string& rhs) const {
    if (arr_size != rhs.arr_size)
        return false;
    
    char* rhs_arr = rhs.arr;
    char* lhs_arr = arr;
    for (size_t i{}; i < arr_size; i++)
        if (sut::tolower(*(lhs_arr++)) != sut::tolower(*(rhs_arr++)))
            return false;
    return true;
}

bool string::similar(const char* rhs) const {
    if (arr_size != std::strlen(rhs))
        return false;
    
    char* lhs_arr = arr;
    for (size_t i{}; i < arr_size; i++)
        if (sut::tolower(*(lhs_arr++)) != sut::tolower(*(rhs++)))
            return false;
    return true;
}

size_t string::count(char ch) const {
    size_t count{};
    char* _arr = arr;
    while (*_arr)
        if (*(_arr++) == ch)
            count++;
    return count;
}

string string::operator()(size_t end) const{
    if (end >= this->arr_size)
        return *this;
    string tmp(end);
    memcpy(tmp.arr, this->arr, end);
    return tmp;
}

string string::operator()(size_t start, size_t end) const{
    if ((start >= end) || (start >= arr_size - 1))
        return string("");
    size_t size{end - start};
    if (end >= this->arr_size)
        size = this->arr_size - start;
    string tmp(size);
    memcpy(tmp.arr, this->arr + start, size);
    return tmp;
}

string string::slice(size_t end) const{
    if (end >= this->arr_size)
        return *this;
    string tmp(end);
    memcpy(tmp.arr, this->arr, end);
    return tmp;
}

string string::slice(size_t start, size_t end) const{
    if ((start >= end) || (start >= arr_size - 1))
        return string("");
    size_t size{end - start};
    if (end >= this->arr_size)
        size = this->arr_size - start;
    string tmp(size);
    memcpy(tmp.arr, this->arr + start, size);
    return tmp;
}

std::strong_ordering operator<=>(const string& lhs, const string& rhs){
    using so = std::strong_ordering;

    char result;
    char* lhs_arr = lhs.arr;
    char* rhs_arr = rhs.arr;
    size_t i{}, upto{(lhs.arr_size < rhs.arr_size) ? lhs.arr_size : rhs.arr_size};
    
    for (; i < upto; i++)
        if ((result = (lhs_arr[i] - rhs_arr[i])))
            break;
    
    if (!result)
        result = lhs.arr_size - rhs.arr_size;

    if (!result)
        return so::equal;
    else if (result < 0)
        return so::less;
    else
        return so::greater;
}

std::strong_ordering operator<=>(const string& lhs, const char* rhs){
    using so = std::strong_ordering;
    
    size_t rhs_size{std::strlen(rhs)}, i{}, upto{(lhs.arr_size < rhs_size) ? lhs.arr_size : rhs_size};
    char result;
    char* lhs_arr = lhs.arr;
    
    for (; i < upto; i++)
        if ((result = (lhs_arr[i] - rhs[i])))
            break;
    
    if (!result)
        result = lhs.arr_size - rhs_size;
    
    if (!result)
        return so::equal;
    else if (result < 0)
        return so::less;
    else
        return so::greater;
}

bool operator==(const string& lhs, const string& rhs){
    if (lhs.arr_size != rhs.arr_size)
        return false;
    
    char* lhs_arr = lhs.arr;
    char* rhs_arr = rhs.arr;
    for (size_t i{}; i < lhs.arr_size; i++)
        if (*(lhs_arr++) != *(rhs_arr++))
            return false;
    return true;
}

bool operator==(const string& lhs, const char* rhs){
    if (lhs.arr_size != std::strlen(rhs))
        return false;
    
    char* lhs_arr = lhs.arr;
    for (size_t i{}; i < lhs.arr_size; i++)
        if (*(lhs_arr++) != *(rhs++))
            return false;
    return true;
}

string operator+(const string& lhs, const string& rhs){
    size_t tmp_size{lhs.arr_size + rhs.arr_size};
    string tmp{tmp_size};
    memcpy(tmp.arr, lhs.arr, lhs.arr_size);
    memcpy(tmp.arr + lhs.arr_size, rhs.arr, rhs.arr_size);
    tmp.arr_size = tmp_size;
    return tmp;
}

string operator+(const string& lhs, const char* rhs){
    size_t rhs_size{std::strlen(rhs)}, tmp_size{lhs.arr_size + rhs_size};
    string tmp{tmp_size};
    memcpy(tmp.arr, lhs.arr, lhs.arr_size);
    memcpy(tmp.arr + lhs.arr_size, rhs, rhs_size);
    tmp.arr_size = tmp_size;
    return tmp;
}

string operator+(const char* lhs, const string& rhs){
    size_t lhs_size{std::strlen(lhs)}, tmp_size{lhs_size + rhs.arr_size};
    string tmp{tmp_size};
    memcpy(tmp.arr, lhs, lhs_size);
    memcpy(tmp.arr + lhs_size, rhs.arr, rhs.arr_size);
    tmp.arr_size = tmp_size;
    return tmp;
}

string& string::operator+=(const char* rhs){
    size_t rhs_size{std::strlen(rhs)};
    if (!rhs_size)
        return *this;
    
    char* new_arr = new char[arr_size + rhs_size];
    memcpy(new_arr, arr, sizeof(char) * arr_size);
    memcpy(new_arr + arr_size, rhs, rhs_size);
    delete[] arr;
    arr = new_arr;
    arr_size += rhs_size;
    return *this;
}

string& string::operator+=(const string& rhs){
    if (rhs.arr_size == 0)
        return *this;
    
    size_t new_size{this->arr_size + rhs.arr_size};
    char* new_arr = new char[new_size];
    memcpy(new_arr, arr, sizeof(char) * arr_size);
    memcpy(new_arr + arr_size, rhs.arr, rhs.arr_size);
    delete[] arr;
    arr = new_arr;
    arr_size = new_size;
    return *this;
}

char& string::operator[](size_t i){
    if (i > (arr_size - 1))
        return error;
    return arr[i];
}

const char& string::operator[](size_t i) const {
    if (i > (arr_size - 1))
        return error;
    return arr[i];
}

string& string::operator=(const char* str){
    size_t len{std::strlen(str)};
    if (!len)
    {
        delete[] arr;
        arr = nullptr;
        arr_size = 0;
        return *this;
    }

    if (len != arr_size)
    {
        delete[] arr;
        arr = new char[len];
        arr_size = len;
        char* ptr = arr;
    }
    
    char* ptr = arr;
    while ((*(ptr++) = *(str++)));

    return *this;
}

string& string::operator=(const string& str){
    if (this == &str)
        return *this;
    
    if (str.arr_size == 0)
    {
        delete[] arr;
        arr = nullptr;
        arr_size = 0;
        return *this;
    }

    if (this->arr_size != str.arr_size)
    {
        delete[] arr;
        arr = new char[str.arr_size];
        arr_size = str.arr_size;
    }

    memcpy(arr, str.arr, sizeof(char) * str.arr_size);
    
    return *this;
}

string& string::operator=(string&& str){
    if (this == &str)
        return *this;
    
    delete[] arr;
    arr = str.arr;
    arr_size = str.arr_size;
    str.arr = nullptr;
    str.arr_size = 0;
    return *this;
}

string::operator std::string_view(){
    return std::string_view{arr};
}

std::ostream& operator<<(std::ostream& output, const string& str){
    if (str.arr == nullptr)
        return output;
    else
    {
        size_t i{}, size{str.arr_size};
        char* arr = str.arr;
        while (i < size)
            output << arr[i++];
    }
    return output;
}

std::istream& operator>>(std::istream& input, string& str){
    delete[] str.arr;
    __string_input_buffer buf;
    char ch;
    std::cin.get(ch);
    while(ch != '\n'){
        buf.insert(ch);
        std::cin.get(ch);
    }
    
    unsigned int size{buf.size()};
    str.arr = new char[size];
    str.arr_size = size;
    memcpy(str.arr, buf.get_str(), size);
    
    return input;
}

template<typename U>
requires std::is_integral_v<U>
string to_string(U num){
    if (!num){
        return string{"0"};
    }
    unsigned char num_digits = __helpers::__num_digits(num);
    string tmp{num_digits};
    char* _arr = tmp.arr;
    for (size_t i{tmp.arr_size - 1}; num; num /= 10, i--)
        _arr[i] = ((num % 10) + 48);
    return tmp;
}

#endif  // __ARR_STRINGS_H