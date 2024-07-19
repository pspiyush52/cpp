#include "string.h"
#include <iomanip>
#include <fstream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <climits>

string::string() : deque() {}
string::string(char ch, int size) : deque(2 * size){
    for (; size > 0; --size)
        this->push_back(ch);
}
string::string(const char *str) : deque(2 * strlen(str)){
    if (str)
        this->push_back(str);
}
/*string::string(const char* str, int count) : deque(2 * count){
    if (str && (count > 0))
        for (; count && *str; --count)
            this->push_back(*str++);
}
string::string(const string& str, int count) : deque(2 * count){
    if (str && (count > 0))
        for (const_iterator iter = str.cbegin(), end = str.cend(); count && (iter != end); ++iter, --count)
            this->push_back(*iter);
}
string::string(const string& str, int from, int to) : deque(2 * (to - from)){
    int size{to - from};
    if (str && (size > 0))
        size_t i{(str.__front + from) % str.__size};
}*/
string::string(const string& src) : deque(2 * src.size()){
    const_iterator iter = src.cbegin(), end = src.cend();
    pointer arr = this->__arr;
    for (; iter != end; ++iter, ++arr)
        *arr = *iter;
    this->__n = src.__n;
}
string::string(string&& src) : deque(1, 1, 1){
    if (src.is_empty())
        this->__make__(base::DEFAULT_SIZE);
    else{
        delete[] this->__arr;
        this->__arr = src.__arr;
        this->__front = src.__front;
        this->__n = src.__n;
        this->__size = src.__size;
        src.__invalidate__();
    }
}
string::string(const std::string &str) : string(str.c_str()) {}

const char* string::c_str() const{
    if (this->is_empty())
        return this->dummy;
    size_t rear = (this->__front + this->__n) % this->__size;
    if (this->__front < rear){
        this->__arr[rear] = '\0';
        return this->__arr + this->__front;
    }
    else{
        pointer new_arr = new value_type[this->__size], ptr = new_arr;
        for (char ch : *this)
            *ptr++ = ch;
        *ptr = '\0';
        delete[] this->__arr;
        this->__front = 0;
        this->__arr = new_arr;
        return this->__arr;
    }
}

string& string::push_front(char ch){
    base::push_front(ch);
    return *this;
}
string& string::push_back(char ch){
    base::push_back(ch);
    return *this;
}
string& string::push_front(const char* str){
    if (str){
        const char* rear = str;
        while(*rear++);
        for (--str, rear -= 2; str != rear; --rear)
            base::push_front(*rear);
    }
    return *this;
}
string& string::push_back(const char* str){
    if (str){
        while (*str)
            base::push_back(*str++);
    }
    return *this;
}
string& string::push_front(const string& str){
    if (str.is_empty())
        return *this;
    for (const_reverse_iterator iter = str.crbegin(), end = str.crend(); iter != end; ++iter)
        this->push_front(*iter);
    return *this;
}
string& string::push_back(const string& str){
    if (str.is_empty())
        return *this;
    for (const_iterator iter = str.cbegin(), end = str.cend(); iter != end; ++iter)
        this->push_back(*iter);
    return *this;
}
string& string::pop_front(){
    base::pop_front();
    return *this;
}
string& string::pop_back(){
    base::pop_back();
    return *this;
}
string& string::pop_frontn(int n){
    base::pop_frontn(n);
    return *this;
}
string& string::pop_backn(int n){
    base::pop_backn(n);
    return *this;
}
string& string::shrink_to_fit(){
    base::shrink_to_fit();
    return *this;
}
const string& string::shrink_to_fit() const{
    base::shrink_to_fit();
    return *this;
}

bool string::is_alpha() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (!isalpha(*iter))
            return false;
    return true;
}
bool string::is_alnum() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (!isalnum(*iter))
            return false;
    return true;
}
bool string::is_numeric() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (*iter < '0' || *iter > '9')
            return false;
    return true;
}
bool string::contains(char ch) const{
    return this->__contains(ch, this->__char_compare);
}
bool string::contains_i(char ch) const{
    return this->__contains(ch, this->__char_compare_i);
}
bool string::contains(const string& q) const{
    if (this->size() < q.size())
        return false;
    if (this->is_empty() && q.is_empty())
        return true;
    return (this->__search(this->cbegin(), this->cend(), q, this->__char_compare) != -1);
}
bool string::contains_i(const string& q) const{
    if (this->size() < q.size())
        return false;
    if (this->is_empty() && q.is_empty())
        return true;
    return (this->__search(this->cbegin(), this->cend(), q, this->__char_compare_i) != -1);
}
bool string::contains(const char* q) const{
    if (this->is_empty() && (*q == 0))
        return true;
    return (this->__search(this->cbegin(), this->cend(), q, this->__char_compare) != -1);
}
bool string::contains_i(const char* q) const{
    if (this->is_empty() && (*q == 0))
        return true;
    return (this->__search(this->cbegin(), this->cend(), q, this->__char_compare_i) != -1);
}
long long string::search(const string& q) const{
    if (this->size() < q.size())
        return -1;
    if (this->is_empty() && q.is_empty())
        return 0;
    return this->__search(this->begin(), this->end(), q, this->__char_compare);
}
long long string::search_i(const string& q) const{
    if (this->size() < q.size())
        return -1;
    if (this->is_empty() && q.is_empty())
        return 0;
    return this->__search(this->begin(), this->end(), q, this->__char_compare_i);
}
long long string::search(const char* q) const{
    if (this->is_empty() && (*q == 0))
        return 0;
    return this->__search(this->cbegin(), this->cend(), q, this->__char_compare);
}
long long string::search_i(const char* q) const{
    if (this->is_empty() && (*q == 0))
        return 0;
    return this->__search(this->cbegin(), this->cend(), q, this->__char_compare_i);
}
string::index_list string::search_all(const string& q) const{
    if (this->size() < q.size() || this->is_empty())
        return {};
    const_iterator iter = this->cbegin(), end = this->cend();
    long long pos{this->__search(iter, end, q, this->__char_compare)};
    string::index_list positions;
    for (++iter; pos != -1; ++iter){
        positions.push_back(pos);
        pos = this->__search(iter, end, q, this->__char_compare);
    }
    return positions;
}
string::index_list string::search_all_i(const string& q) const{
    if (this->size() < q.size() || this->is_empty())
        return {};
    const_iterator iter = this->cbegin(), end = this->cend();
    long long pos{this->__search(iter, end, q, this->__char_compare_i)};
    string::index_list positions;
    for (++iter; pos != -1; ++iter){
        positions.push_back(pos);
        pos = this->__search(iter, end, q, this->__char_compare_i);
    }
    return positions;
}
string::index_list string::search_all(const char* q) const{
    if (this->is_empty())
        return {};
    const_iterator iter = this->cbegin(), end = this->cend();
    long long pos{this->__search(iter, end, q, this->__char_compare)};
    string::index_list positions;
    for (++iter; pos != -1; ++iter){
        positions.push_back(pos);
        pos = this->__search(iter, end, q, this->__char_compare);
    }
    return positions;
}
string::index_list string::search_all_i(const char* q) const{
    if (this->is_empty())
        return {};
    const_iterator iter = this->cbegin(), end = this->cend();
    long long pos{this->__search(iter, end, q, this->__char_compare_i)};
    string::index_list positions;
    for (++iter; pos != -1; ++iter){
        positions.push_back(pos);
        pos = this->__search(iter, end, q, this->__char_compare_i);
    }
    return positions;
}
string string::first_word() const{
    if (this->is_empty())
        return {};
    const_iterator begin = this->__skipwf(), end = this->end();
    if (begin == end)
        return {};
    string buf{};
    for (; (begin != end) && (!__is_whitespace(*begin)); ++begin)
        buf.push_back(*begin);
    return buf;
}
string string::last_word() const{
    if (this->is_empty())
        return {};
    const_iterator begin = this->begin(), rear = this->__skipwr();
    if (begin == rear)
        return {};
    string buf;
    for (; (begin != rear) && (!__is_whitespace(*rear)); --rear)
        buf.push_front(*rear);
    if (rear == begin)
        buf.push_front(*rear);
    return buf;
}
string string::get_lower() const{
    if (this->is_empty())
        return {};
    string tmp(this->__size);
    const_iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        tmp.push_back(tolower(*iter));
    return tmp;
}
string string::get_upper() const{
    if (this->is_empty())
        return {};
    string tmp(this->__size);
    const_iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        tmp.push_back(toupper(*iter));
    return tmp;
}
string& string::to_lower(){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        *iter = tolower(*iter);
    return *this;
}
string& string::to_upper(){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        *iter = toupper(*iter);
    return *this;
}
string& string::capitalize(){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin(), end = this->end();
    for (; (iter != end) && __is_whitespace(*iter); ++iter);
    if (iter == end)
        return *this;
    *iter = toupper(*iter);
    return *this;
}
string& string::title(){
    if (this->is_empty())
        return *this;
    iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        return *this;
    *iter = toupper(*iter);
    for (++iter; iter != end; ++iter){
        if (__is_whitespace(*iter)){
            for (; ((iter != end) && __is_whitespace(*iter)); ++iter);
            if (iter == end)
                return *this;
            *iter = toupper(*iter);
        }
        else
            *iter = tolower(*iter);
    }
    return *this;
}
string string::titled() const{
    if (this->is_empty())
        return {};
    string tmp{*this};
    return tmp.title();
}
string& string::collapse(){
    if (this->is_empty())
        return *this;
    iterator iter = this->__skipwf(), end = this->__skipwr(), ff = this->end();
    if (iter == ff){
        this->__reset();
        return *this;
    }
    ++end;
    size_t i{end.__get_pos()}, front{i}, counter{};
    for (; iter != end; ++iter){
        if (__is_whitespace(*iter)){
            this->__arr[i] = *iter;
            i = (i + 1) % this->__size;
            for (; (iter != end) && __is_whitespace(*iter); ++iter);
        }
        this->__arr[i] = *iter;
        i = (i + 1) % this->__size;
        ++counter;
    }
    this->__front = front;
    this->__n = counter ;
    return *this;
}
string string::collapsed(){
    if (this->is_empty())
        return {};
    string tmp;
    iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->end();
    if (iter == end)
        return {};
    for (++rear; iter != rear; ++iter){
        if (__is_whitespace(*iter)){
            tmp.push_back(*iter);
            for (; (iter != rear) && __is_whitespace(*iter); ++iter);
        }
        tmp.push_back(*iter);
    }
    return tmp;
}
string& string::reverse(){
    if (this->size() < 2)
        return *this;
    char tmp{};
    reverse_iterator riter = this->rbegin();
    iterator iter = this->begin();
    for (size_t i{this->size() / 2}; i; ++riter, ++iter, --i){
        tmp = *riter;
        *riter = *iter;
        *iter = tmp;
    }
    return *this;
}
string string::reversed() const{
    if (this->size() < 2)
        return {};
    string tmp;
    for (auto iter = this->cbegin(), end = this->cend(); iter != end; ++iter)
        tmp.push_front(*iter);
    return tmp;
}
bool string::similar(const char* str) const{
    const_iterator iter = this->cbegin(), end = this->cend();
    for (; (iter != end) && (*str); ++iter, ++str)
        if (tolower(*iter) != tolower(*str))
            return false;
    if ((iter != end) || (*str))
        return false;
    return true;
}
bool string::similar(const string& str) const{
    if (this == &str)
        return true;
    if (!(this->size() || str.size()))
        return true;
    if (this->size() != str.size())
        return false;
    const_iterator titer = this->cbegin(), tend = this->end();
    const_iterator siter = str.begin();
    for (; titer != tend; ++titer, ++siter)
        if (tolower(*titer) != tolower(*siter))
            return false;
    return true;
}
size_t string::count(char ch) const{
    if (this->is_empty())
        return {};
    size_t count{};
    const_iterator iter = this->cbegin(), end = this->cend();
    for (; iter != end; ++iter)
        if (*iter == ch)
            ++count;
    return count;
}
size_t string::count_i(char ch) const{
    if (this->is_empty())
        return {};
    size_t count{};
    ch = tolower(ch);
    const_iterator iter = this->cbegin(), end = this->cend();
    for (; iter != end; ++iter)
        if (tolower(*iter) == ch)
            ++count;
    return count;
}
size_t string::count(const string& q) const{
    if (this->is_empty() || q.is_empty() || (this->size() < q.size()))
        return {};
    string::const_iterator iter = this->cbegin(), end = this->cend();
    size_t count{};
    for (; this->__search(iter, end, q, this->__char_compare) != -1; ++iter, ++count);
    return count;
}
size_t string::count_i(const string& q) const{
    if (this->is_empty() || q.is_empty() || (this->size() < q.size()))
        return {};
    string::const_iterator iter = this->cbegin(), end = this->cend();
    size_t count{};
    for (; this->__search(iter, end, q, this->__char_compare_i) != -1; ++iter, ++count);
    return count;
}
size_t string::count(const char* q) const{
    if (this->is_empty())
        return {};
    string::const_iterator iter = this->cbegin(), end = this->cend();
    size_t count{};
    for (; this->__search(iter, end, q, this->__char_compare) != -1; ++count, ++iter);
    return count;
}
size_t string::count_i(const char* q) const{
    if (this->is_empty())
        return {};
    string::const_iterator iter = this->cbegin(), end = this->cend();
    size_t count{};
    for (; this->__search(iter, end, q, this->__char_compare_i) != -1; ++count, ++iter);
    return count;
}
string& string::replace(char to_replace, char replacement_char){
    if (this->is_empty())
        return *this;
    for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (*iter == to_replace)
            *iter = replacement_char;
    return *this;
}
string& string::fill(char fill_char){
    if (this->is_empty())
        return *this;
    for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        *iter = fill_char;
    return *this;
}
string string::slice(size_t end) const{
    if (end >= this->size())
        return *this;
    string tmp;
    for (size_t i{this->__front}, j{}; j < end; ++j){
        tmp.push_back(this->__arr[i]);
        i = (i + 1) % this->__size;
    }
    return tmp;
}
string string::slice(size_t start, size_t end) const{
    if ((start >= end) || (start >= this->size()))
        throw IndexError("string::slice() : Invalid position for slicing");
    string tmp;
    size_t i = (this->__front + start) % this->__size;
    size_t rear = (end >= this->size()) ? ((this->__front + this->__n) % this->__size) : ((this->__front + end) % this->__size);
    while (i != rear){
        tmp.push_back(this->__arr[i]);
        i = (i + 1) % this->__size;
    }
    return tmp;
}
string string::from_pos(size_t pos) const{
    if (!pos)
        return *this;
    if (pos >= this->size())
        throw IndexError("string::from_pos() : Invalid position for slicing");
    string tmp;
    size_t size = this->size(), i = (this->__front + pos) % size, j{};
    for (; j < size - pos; ++j){
        tmp.push_back(this->__arr[i]);
        i = (i + 1) % size;
    }
    return tmp;
}
string string::from_pos(size_t pos, size_t count) const{
    if (!count)
        throw ArgError("string::from_pos() : count cannot be zero");
    if (pos >= this->size())
        throw IndexError("string::from_pos() : Invalid position for slicing");
    if ((pos + count) >= (this->size()))
        return this->from_pos(pos);
    string tmp;
    size_t size = this->size(), i = (this->__front + pos) % size, j{};
    for (; j < count; ++j){
        tmp.push_back(this->__arr[i]);
        i = (i + 1) % size;
    }
    return tmp;
}
string string::nlast(size_t count) const{
    if (!count)
        throw ArgError("string::nlast() : count cannot be zero");
    if (count >= this->size())
        return *this;
    string tmp;
    const_reverse_iterator iter = this->crbegin();
    for (size_t i{}; i < count; ++i, ++iter)
        tmp.push_front(*iter);
    return tmp;
}
string& string::lstrip(){
    if (this->is_empty())
        return *this;
    iterator iter = this->__skipwf();
    this->__front = iter.__get_pos();
    return *this;
}
string& string::rstrip(){
    if (this->is_empty())
        return *this;
    // iterator rear = this->__skipwr();
    // this->__rear = (++rear).__get_pos();
    return *this;
}
string& string::strip(){
    if (this->is_empty())
        return *this;
    iterator front = this->__skipwf();
    // iterator rear = this->__skipwr();
    this->__front = front.__get_pos();
    // this->__rear = (++rear).__get_pos();
    return *this;
}
string::string_list string::split(char ch) const{
    if (this->is_empty())
        return {};
    string_list list;
    string tmp;
    for (const_iterator iter = this->cbegin(), end = this->cend(); iter != end; ++iter){
        if (*iter == ch){
            list.push_back(std::move(tmp));
            tmp.__make__();
        }
        else
            tmp.push_back(*iter);
    }
    if (tmp)
        list.push_back(std::move(tmp));
    return list;
}

int string::stoi() const{
    if (this->is_empty())
        throw ValueError("string::stoi() : String empty");
    
    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stoi() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = __get_num(iter, rear);
    }
    catch(ValueError& err){
        throw ValueError("string::stoi() : Invalid string");
    }
    if (num < INT_MIN)
        return INT_MIN;
    else if (num > INT_MAX)
        return INT_MAX;
    return static_cast<int>(num);
}
unsigned int string::stoui() const{
    if (this->is_empty())
        throw ValueError("string::stoui() : String empty");
    
    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stoui() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = this->__get_unum(iter, rear);
    }
    catch(ValueError&){
        throw ValueError("string::stoui() : Invalid string");
    }
    if (num > UINT_MAX)
        return UINT_MAX;
    return static_cast<unsigned int>(num);
}
long string::stol() const{
    if (this->is_empty())
        throw ValueError("string::stol() : String empty");
    
    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stol() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = this->__get_num(iter, rear);
    }
    catch(ValueError&){
        throw ValueError("string::stol() : Invalid string");
    }
    if (num < LONG_MIN)
        return INT_MIN;
    else if (num > LONG_MAX)
        return LONG_MAX;
    return static_cast<long>(num);
}
unsigned long string::stoul() const{
    if (this->is_empty())
        throw ValueError("string::stoul() : String empty");

    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stoul() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = this->__get_unum(iter, rear);
    }
    catch(ValueError&){
        throw ValueError("string::stoul() : Invalid string");
    }
    if (num > ULONG_MAX)
        return ULONG_MAX;
    return static_cast<unsigned long>(num);
}
long long string::stoll() const{
    if (this->is_empty())
        throw ValueError("string::stoll() : String empty");
    
    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stoll() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = this->__get_num(iter, rear);
    }
    catch(ValueError&){
        throw ValueError("string::stoll() : Invalid string");
    }
    if (num < LLONG_MIN)
        return LLONG_MIN;
    else if (num > LLONG_MAX)
        return LLONG_MAX;
    return static_cast<long long>(num);
    
}
unsigned long long string::stoull() const{
    if (this->is_empty())
        throw ValueError("string::stoull() : String empty");
    
    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stoull() : String empty");
    const_iterator rear = this->__skipwr();
    long double num{};
    try{
        num = this->__get_unum(iter, rear);
    }
    catch(ValueError&){
        throw ValueError("string::stoull() : Invalid string");
    }
    if (num > ULONG_MAX)
        return ULONG_MAX;
    return static_cast<unsigned long long>(num);
}
double string::stod() const{
    if (this->is_empty())
        throw ValueError("string::stod() : String empty");
    
    double num{}, div{10};
    bool is_negative{false};

    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stod() : String empty");
    const_iterator rear = this->__skipwr();
    if (*iter == '-'){
        is_negative = true;
        ++iter;
    }
    else if (*iter == '+')
        ++iter;
    for (++rear; (iter != rear) && (*iter >= '0' && *iter <= '9'); ++iter)
        num = (num * 10) + (*iter - '0');
    if (*iter == '.'){
        for (++iter; (iter != rear); ++iter){
            if (*iter >= '0' && *iter <= '9'){
                num += ((*iter - '0') / div);
                div *= 10;
            }
            else
                throw ValueError("string::stod() : Invalid string");
        }
    }
    if (is_negative)
        num = -num;
    return num;
}
long double string::stold() const{
    if (this->is_empty())
        throw ValueError("string::stold() : String empty");
    
    long double num{}, div{10};
    bool is_negative{false};

    const_iterator iter = this->__skipwf(), end = this->end();
    if (iter == end)
        throw ValueError("string::stold() : String empty");
    const_iterator rear = this->__skipwr();
    if (*iter == '-'){
        is_negative = true;
        ++iter;
    }
    else if (*iter == '+')
        ++iter;
    for (++rear; (iter != rear) && (*iter >= '0' && *iter <= '9'); ++iter)
        num = (num * 10) + (*iter - '0');
    if (*iter == '.'){
        for (++iter; (iter != rear); ++iter){
            if (*iter >= '0' && *iter <= '9'){
                num += ((*iter - '0') / div);
                div *= 10;
            }
            else
                throw ValueError("string::stold() : Invalid string");
        }
    }
    if (is_negative)
        num = -num;
    return num;
}
int string::btoi() const{
    if (this->is_empty())
        throw ValueError("string::btoi() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btoi() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    int num{}, i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1 << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btoi() : Invalid string");
    if (i > __INT_WIDTH__)
        return INT_MAX;
    return num;
}
unsigned int string::btoui() const{
    if (this->is_empty())
        throw ValueError("string::btoui() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btoui() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    unsigned int num{}, i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1U << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btoui() : Invalid string");
    if (i > __INT_WIDTH__)
        return UINT_MAX;
    return num;
}
long string::btol() const{
    if (this->is_empty())
        throw ValueError("string::btol() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btol() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    long num{};
    int i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1L << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btol() : Invalid string");
    if (i > __LONG_WIDTH__)
        return LONG_MAX;
    return num;
}
unsigned long string::btoul() const{
    if (this->is_empty())
        throw ValueError("string::btoul() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btoul() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    unsigned long num{};
    int i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1UL << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btoul() : Invalid string");
    if (i > __LONG_WIDTH__)
        return ULONG_MAX;
    return num;
}
long long string::btoll() const{
    if (this->is_empty())
        throw ValueError("string::btoll() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btoll() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    long long num{};
    int i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1LL << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btoll() : Invalid string");
    if (i > __LONG_LONG_WIDTH__)
        return LLONG_MAX;
    return num;
}
unsigned long long string::btoull() const{
    if (this->is_empty())
        throw ValueError("string::btoull() : b-string empty");
    const_iterator iter = this->__skipwf(), rear = this->__skipwr(), end = this->cend();
    if (iter == rear)
        throw ValueError("string::btoull() : b-string empty");
    for (; (iter != end) && (*iter == '0'); ++iter);
    if (iter == end)
        return {};
    unsigned long long num{};
    int i{};
    for (--iter; iter != rear; --rear, ++i)
        if (*rear == '1')
            num = (num | (1ULL << i));
        else if (*rear == '0')
            continue;
        else
            throw ValueError("string::btoull() : Invalid string");
    if (i > __LONG_LONG_WIDTH__)
        return ULLONG_MAX;
    return num;
}
void string::set_precision(int prec){
    if (prec < 1)
        throw ArgError("string::set_precision() : Precision cannot be lower than 1");
    std::cout << std::setprecision(prec);
    precision = prec;
}
int string::get_precision(){
    return precision;
}
string::iterator string::begin(){
    return base::begin();
}
string::iterator string::end(){
    return base::end();
}
string::const_iterator string::begin() const{
    return base::begin();
}
string::const_iterator string::end() const{
    return base::end();
}
string::const_iterator string::cbegin() const{
    return base::cbegin();
}
string::const_iterator string::cend() const{
    return base::cend();
}
string::reverse_iterator string::rbegin(){
    return base::rbegin();
}
string::reverse_iterator string::rend(){
    return base::rend();
}
string::const_reverse_iterator string::rbegin() const{
    return base::rbegin();
}
string::const_reverse_iterator string::rend() const{
    return base::rend();
}
string::const_reverse_iterator string::crbegin() const{
    return base::crbegin();
}
string::const_reverse_iterator string::crend() const{
    return base::crend();
}
void string::__contents(){
    putchar('[');
    size_t i{}, upto{this->__size - 1};
    for (size_t i{}; i < upto; ++i)
        printf("(%d:'%c'), ", this->__arr[i], this->__arr[i]);
    printf("(%d: '%c')]", this->__arr[i], this->__arr[i]);
    printf("\nArray size: %llu, Front: %llu, Rear: %llu", this->__size, this->__front, (this->__front + this->__n) % this->__size);
}

string::operator bool() const{
    return (!this->is_empty());
}
string string::operator()(size_t end) const{
    return this->slice(end);
}
string string::operator()(size_t start, size_t end) const{
    return this->slice(start, end);
}
string& string::operator=(const string& src){
    if (this == &src)
        return *this;
    delete[] this->__arr;
    this->__make__(src.__size);
    const_iterator iter = src.cbegin(), end = src.cend();
    pointer arr = this->__arr;
    for (; iter != end; ++iter, ++arr)
        *arr = *iter;
    this->__n = src.__n;
    return *this;
}
string& string::operator=(string&& src){
    if (this == &src)
        return *this;
    delete[] this->__arr;
    if (!src.__arr)
        this->__make__();
    else{
        this->__arr = src.__arr;
        this->__front = src.__front;
        this->__n = src.__n;
        this->__size = src.__size;
        src.__invalidate__();
    }
    return *this;
}

std::strong_ordering operator<=>(const string& lhs, const string& rhs){
    if (&lhs == &rhs)
        return std::strong_ordering::equal;
    using so = std::strong_ordering;
    int res{};
    string::const_iterator lhs_iter = lhs.begin(), lhs_end = lhs.end();
    string::const_iterator rhs_iter = rhs.begin(), rhs_end = rhs.end();
    for (; (lhs_iter != lhs_end) && (rhs_iter != rhs_end); ++lhs_iter, ++rhs_iter)
        if ((res = (*lhs_iter - *rhs_iter)))
            break;
    if (!res)
        res = lhs.size() - rhs.size();
    
    if (!res)
        return so::equal;
    else if (res < 0)
        return so::less;
    else
        return so::greater;
}
std::strong_ordering operator<=>(const string& lhs, const char* rhs){
    using so = std::strong_ordering;
    int res{};
    string::const_iterator lhs_iter = lhs.begin(), lhs_end = lhs.end();
    for (; (lhs_iter != lhs_end) && (*rhs); ++lhs_iter, ++rhs)
        if ((res = (*lhs_iter - *rhs)))
            break;
    if (!res)
        res = lhs.size() - strlen(rhs);
    
    if (!res)
        return so::equal;
    else if (res < 0)
        return so::less;
    else
        return so::greater;
}
bool operator==(const string& lhs, const string& rhs){
    if (&lhs == &rhs)
        return true;
    if (lhs.size() != rhs.size())
        return false;
    string::const_iterator lhs_iter = lhs.begin(), lhs_end = lhs.end(), rhs_iter = rhs.begin();
    for (; lhs_iter != lhs_end; ++lhs_iter, ++rhs_iter)
        if (*lhs_iter != *rhs_iter)
            return false;
    return true;
}
bool operator==(const string& lhs, const char* rhs){
    string::const_iterator lhs_iter = lhs.begin(), lhs_end = lhs.end();
    const char* rhs_iter = rhs;
    for (; (lhs_iter != lhs_end) && (*rhs_iter); ++lhs_iter, ++rhs_iter)
        if (*lhs_iter != *rhs_iter)
            return false;
    if (*rhs_iter || (lhs_iter != lhs_end))
        return false;
    return true;
}
string operator+(const string& lhs, const string& rhs){
    size_t n1{lhs.size()}, n2{rhs.size()};
    if (n1 < n2)
        hlp::swap(n1, n2);
    string res = 2 * n1 + n2;
    string::const_iterator iter = lhs.cbegin(), end = lhs.cend();
    string::const_iterator siter = rhs.cbegin(), send = rhs.cend();
    for (; iter != end; ++iter)
        res.push_back(*iter);
    for (; siter != send; ++siter)
        res.push_back(*siter);
    return res;
}
string operator+(const string& lhs, const char* rhs){
    size_t n1{lhs.size()}, n2{strlen(rhs)};
    if (n1 < n2)
        hlp::swap(n1, n2);
    string res = 2 * n1 + n2;
    string::const_iterator iter = lhs.cbegin(), end = lhs.cend();
    for (; iter != end; ++iter)
        res.push_back(*iter);
    for (; *rhs; ++rhs)
        res.push_back(*rhs);
    return res;
}
string operator+(const char* lhs, const string& rhs){
    size_t n1{strlen(lhs)}, n2{rhs.size()};
    if (n1 < n2)
        hlp::swap(n1, n2);
    string res = 2 * n1 + n2;
    string::const_iterator riter = rhs.cbegin(), rend = rhs.cend();
    for (; *lhs; ++lhs)
        res.push_back(*lhs);
    for (; riter != rend; ++riter)
        res.push_back(*riter);
    return res;
}

string& string::operator+=(const string& rhs){
    return this->push_back(rhs);
}
string& string::operator+=(const char* rhs){
    return this->push_back(rhs);
}
string& string::operator+=(char ch){
    return this->push_back(ch);
}
string string::operator*(int i) const{
    if (i < 1)
        return {};
    string buf = 2 *this->size() * i;
    for (; i; --i)
        buf.push_back(*this);
    return buf;
}
string& string::operator*=(int i){
    if (i < 0)
        throw ArgError("string::operator*=() : Multiplication by a negative integer");
    if (!i){
        this->__front = this->__n = 0;
        return *this;
    }
    string tmp{*this};
    for (--i; i; --i)
        tmp.push_back(*this);
    *this = std::move(tmp);
    return *this;
}
char& string::operator[](long long i){
    long long size = this->size();
    if (size == 0)
        throw IndexError("string::operator[] : string empty");
    if (i < 0)
        i = size + i;
    if ((i >= size) || (i < 0))
        throw IndexError("string::operator[] : Index value out of bounds");
    return (this->__arr[(this->__front + i) % this->__size]);
}
const char& string::operator[](long long i) const{
    long long size = this->size();
    if (size == 0)
        throw IndexError("string::operator[] : string empty");
    if (i < 0)
        i = size + i;
    if ((i >= size) || (i < 0))
        throw IndexError("string::operator[] : Index value out of bounds");
    return (this->__arr[(this->__front + i) % this->__size]);
}

std::ostream& operator<<(std::ostream& output, const string& str){
    if (str.is_empty())
        return output;
    
    auto iter = str.begin(), end = str.end();
    for (; iter != end; ++iter)
        output.put(*iter);
    return output;
}
std::istream& operator>>(std::istream& input, string& str){
    str.__reset();
    char ch;
    input.get(ch);
    while (ch != '\n'){
        str.push_back(ch);
        input.get(ch);
    }
    return input;
}
std::ifstream& operator>>(std::ifstream& input, string& str){
    if (!input)
        throw FileInputError();
    char ch;
    input.get(ch);
    for (; !input.eof(); input.get(ch))
        str.push_back(ch);
    return input;
}

bool string::__is_whitespace(const char& ch){
    switch (ch){
        case ' ':
        case '\t':
        case '\f':
        case '\n':
        case '\r':
        case '\v':
            return true;
        default:
            return false;
    }
}
string::string(long long size) : deque(size){}
string::iterator string::__skipwf(){
    iterator iter = this->begin(), end = this->end();
    for (; (iter != end)  && __is_whitespace(*iter); ++iter);
    return iter;
}
string::const_iterator string::__skipwf() const{
    const_iterator iter = this->cbegin(), end = this->cend();
    for (; (iter != end)  && __is_whitespace(*iter); ++iter);
    return iter;
}
string::iterator string::__skipwr(){
    iterator iter = this->begin(), end = this->end();
    for (--end; (iter != end)  && __is_whitespace(*end); --end);
    return end;
}
string::const_iterator string::__skipwr() const{
    const_iterator iter = this->begin(), end = this->end();
    for (--end; (iter != end)  && __is_whitespace(*end); --end);
    return end;
}
void string::__reset(){
    this->__front = this->__n = 0;
}
long double string::__get_num(const_iterator& iter, const_iterator& rear) const{
    long double num{};
    bool is_negative{false};
    if (*iter == '-'){
        is_negative = true;
        ++iter;
    }
    else if (*iter == '+')
        ++iter;
    for (++rear; iter != rear; ++iter)
        if (*iter >= '0' && *iter <= '9')
            num = (num * 10) + (*iter - '0');
        else
            throw ValueError();
    if (is_negative)
        num = -num;
    return num;
    
}
long double string::__get_unum(const_iterator& iter, const_iterator& rear) const{
    long double num{};
    if (*iter == '+'){
        ++iter;
    }
    else if (*iter == '-')
        throw ValueError();
    for (++rear; iter != rear; ++iter)
        if (*iter >= '0' && *iter <= '9')
            num = (num * 10) + (*iter - '0');
        else
            throw ValueError();
    return num;
}
bool string::__char_compare(char __x, char __y){
    return (__x == __y);
}
bool string::__char_compare_i(char __x, char __y){
    return (tolower(__x) == tolower(__y));
}
bool string::__contains(char ch, compare_fun comp) const{
    const_iterator iter = this->cbegin(), end = this->cend();
    for (; iter != end; ++iter)
        if (comp(*iter, ch))
            return true;
    return false;
}
long long string::__search(const_iterator& iter, const_iterator& end, const string& q, compare_fun comp){
    const_iterator cur = iter;
    const_iterator qbegin = q.cbegin(), qiter = qbegin, qend = q.cend();
    long long pos{};
    for (; iter != end; ++pos){
        for (; (cur != end) && (qiter != qend) && comp(*cur, *qiter); ++cur, ++qiter);
        if (qiter == qend)
            return iter.__rel_pos();
        cur = ++iter;
        qiter = qbegin;
    }
    return -1;
}
long long string::__search(const_iterator&& iter, const_iterator&& end, const string& q, compare_fun comp){
    return __search(std::forward<const_iterator&>(iter), std::forward<const_iterator&>(end), q, comp);
}
long long string::__search(const_iterator& iter, const_iterator& end, const char* q, compare_fun comp){
    const_iterator cur = iter;
    const char* ptr = q;
    for (; iter != end; ){
        for (; *ptr && (cur != end) && comp(*cur, *ptr); ++cur, ++ptr);
        if (!*ptr)
            return iter.__rel_pos();
        cur = ++iter;
        ptr = q;
    }
    return -1;
}
long long string::__search(const_iterator&& iter, const_iterator&& end, const char* q, compare_fun comp){
    return __search(std::forward<const_iterator&>(iter), std::forward<const_iterator&>(end), q, comp);
}

bool getline(std::istream& input, string& str){
    if (!input)
        throw FileInputError();
    str.__reset();
    char ch;
    input.get(ch);
    for (; ch != '\n' && input; input.get(ch))
        str.push_back(ch);
    return static_cast<bool>(input);
}

string& get(string& str){
    str.__reset();
    char ch;
    std::istream& input = std::cin;
    input.get(ch);
    while(ch != 4){
        str.push_back(ch);
        input.get(ch);
    }
    input.seekg(0);
    return str;
}

string get_string(const char* prompt){
    string response;
    std::cout << prompt;
    std::cin >> response;
    return response;
}
int get_int(const char* prompt){
    string response;
    std::cout << prompt;
    std::cin >> response;
    return response.strip().stoi();
}
long long get_llint(const char* prompt){
    string response;
    std::cout << prompt;
    std::cin >> response;
    return response.strip().stoll();
}
double get_double(const char* prompt){
    string response;
    std::cout << prompt;
    std::cin >> response;
    return response.strip().stod();
}