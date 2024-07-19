#ifndef __STRING_H
#define __STRING_H

#include "deque_t.h"
#include <vector>
#include <math.h>
#include <concepts>
#include "exceptions.h"
#include "str_helpers.h"

class string : public deque<char>{
    public:
        typedef                             char            value_type;
        typedef                      deque<char>            base;
        typedef                   base::iterator            iterator;
        typedef             base::const_iterator            const_iterator;
        typedef           base::reverse_iterator            reverse_iterator;
        typedef     base::const_reverse_iterator            const_reverse_iterator;
        typedef                    deque<string>            string_list;
        typedef                 deque<long long>            index_list;
        
    public:
        string();
        string(char ch, int size);
        string(const char* str);
        // string(const char* str, int count);
        // string(const string& str, int count);
        // string(const string& str, int from, int to);
        string(const std::string& str);
        string(const string& src);
        string(string&& src);

        const char* c_str() const;
        string& push_front(char ch);
        string& push_back(char ch);
        string& push_front(const char* str);
        string& push_back(const char* str);
        string& push_front(const string& str);
        string& push_back(const string& str);
        string& pop_front();
        string& pop_back();
        string& pop_frontn(int n);
        string& pop_backn(int n);
        string& shrink_to_fit();
        const string& shrink_to_fit() const;
        void __contents();
        
        bool is_alpha() const;
        bool is_alnum() const;
        bool is_numeric() const;
        bool contains(char ch) const;
        bool contains_i(char ch) const;
        bool contains(const string& q) const;
        bool contains_i(const string& q) const;
        bool contains(const char* q) const;
        bool contains_i(const char* q) const;
        long long search(const string& q) const;
        long long search_i(const string& q) const;
        long long search(const char* q) const;
        long long search_i(const char* q) const;
        index_list search_all(const string& q) const;
        index_list search_all_i(const string& q) const;
        index_list search_all(const char* q) const;
        index_list search_all_i(const char* q) const;
        
        string first_word() const;
        string last_word() const;
        string get_lower() const;
        string get_upper() const;
        string& to_lower();
        string& to_upper();
        string& capitalize();
        string& title();
        string titled() const;
        string& collapse();
        string collapsed();
        string& reverse();
        string reversed() const;
        
        bool similar(const char* str) const;
        bool similar(const string& str) const;
        
        size_t count(char ch) const;
        size_t count_i(char ch) const;
        size_t count(const string& q) const;
        size_t count_i(const string& q) const;
        size_t count(const char* q) const;
        size_t count_i(const char* q) const;
        string& replace(char to_replace, char replacement_char);
        string& fill(char fill_char);
        string slice(size_t end) const;
        string slice(size_t start, size_t end) const;
        string from_pos(size_t pos) const;
        string from_pos(size_t pos, size_t count) const;
        string nlast(size_t count) const;
        string& lstrip();
        string& rstrip();
        string& strip();
        string_list split(char ch = ' ') const;
        
        int stoi() const;
        unsigned int stoui() const;
        long stol() const;
        unsigned long stoul() const;
        long long stoll() const;
        unsigned long long stoull() const;
        double stod() const;
        long double stold() const;
        
        int btoi() const;
        unsigned int btoui() const;
        long btol() const;
        unsigned long btoul() const;
        long long btoll() const;
        unsigned long long btoull() const;
        
        template<typename Modifier, typename Predicate = hlp::tautology>
        string& modify(Modifier mod_fun = {}, Predicate pred = {}){
            if (this->is_empty())
                return *this;
            for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
                if (pred(*iter))
                    *iter = mod_fun(*iter);
            return *this;
        }
        
        static void set_precision(int prec);
        static int get_precision();
        
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        operator bool() const;
        string operator()(size_t end) const;
        string operator()(size_t start, size_t end) const;
        string& operator=(const string& src);
        string& operator=(string&& src);
        friend std::strong_ordering operator<=>(const string& lhs, const string& rhs);
        friend std::strong_ordering operator<=>(const string& lhs, const char* rhs);
        friend bool operator==(const string& lhs, const string& rhs);
        friend bool operator==(const string& lhs, const char* rhs);
        friend string operator+(const string& lhs, const string& rhs);
        friend string operator+(const string& lhs, const char* rhs);
        friend string operator+(const char* lhs, const string& rhs);
        string& operator+=(const string& rhs);
        string& operator+=(const char* rhs);
        string& operator+=(char ch);
        string operator*(int i) const;
        string& operator*=(int i);
        char& operator[](long long i);
        const char& operator[](long long i) const;
        friend std::ostream& operator<<(std::ostream& output, const string& str);
        friend std::istream& operator>>(std::istream& input, string& str);
        friend std::ifstream& operator>>(std::ifstream& input, string& str);
        void __reset();
        
    private:
        static inline int precision{6};
        static inline const char* dummy{""};
        static bool __is_whitespace(const char& ch);
        string(long long size);
        iterator __skipwf();
        const_iterator __skipwf() const;
        iterator __skipwr();
        const_iterator __skipwr() const;
        long double __get_num(const_iterator& iter, const_iterator& rear) const;
        long double __get_unum(const_iterator& iter, const_iterator& rear) const;
        static bool __char_compare(char __x, char __y);
        static bool __char_compare_i(char __x, char __y);
        typedef bool (*compare_fun)(char, char);
        bool __contains(char ch, compare_fun comp) const;
        static long long __search(const_iterator& iter, const_iterator& end, const char* q, compare_fun comp);
        static long long __search(const_iterator&& iter, const_iterator&& end, const char* q, compare_fun comp);
        static long long __search(const_iterator& iter, const_iterator& end, const string& q, compare_fun comp);
        static long long __search(const_iterator&& iter, const_iterator&& end, const string& q, compare_fun comp);
};

template<std::integral _num_tp>
string bstring(_num_tp num){
    string tmp;
    if (!num){
        tmp.push_back('0');
        return tmp;
    }
    long long i{63};
    for (; (i >= 0) && (((1LL << i) & num) == 0); --i);
    for (; (i >= 0); --i)
        if ((1LL << i) & num)
            tmp.push_back('1');
        else
            tmp.push_back('0');
    return tmp;
}

template<std::integral _num_tp>
string bstring(_num_tp num, int width){
    if (width < 1)
        throw ValueError("bstring() : Invalid value for width");
    if (width > 64)
        width = 64;
    string tmp;
    // if (!num){
        // tmp.push_back('0');
        // return tmp;
    // }
    long long i{width - 1};
    for (; (i >= 0); --i)
        if ((1LL << i) & num)
            tmp.push_back('1');
        else
            tmp.push_back('0');
    return tmp;
}

template<std::integral T>
string to_string(T num){
    if (!num)
        return {"0"};
    string buf;
    bool is_negative{};
    if (num < 0){
        num = -num;
        is_negative = true;
    }
    for (; num; num /= 10)
        buf.push_front((num % 10) + '0');
    if (is_negative)
        buf.push_front('-');
    return buf;
}

template<std::integral T>
string to_string(T num, int width){
    string buf;
    bool is_negative{};
    if (num < 0){
        num = -num;
        is_negative = true;
    }
    for (; num; num /= 10)
        buf.push_front((num % 10) + '0');
    if (buf.size() < width){
        for (auto i{width - buf.size()}; i; --i)
            buf.push_front('0');
    }
    if (is_negative)
        buf.push_front('-');
    return buf;
}

template<std::integral T>
string to_string(T num, int width, char padding_char){
    string buf;
    bool is_negative{};
    if (num < 0){
        num = -num;
        is_negative = true;
    }
    for (; num; num /= 10)
        buf.push_front((num % 10) + '0');
    if (buf.size() < width){
        for (auto i{width - buf.size()}; i; --i)
            buf.push_front(padding_char);
    }
    if (is_negative)
        buf.push_front('-');
    return buf;
}

template<std::floating_point T>
string to_string(T num){
    if (!num)
        return {"0"};
    string buf;
    bool is_negative{};
    if (num < 0){
        num = -num;
        is_negative = true;
    }
    long long whole{static_cast<long long>(num)};
    long long frac = static_cast<long long>((num - whole) * pow(10, string::get_precision()));
    if (frac){
        for (; frac; frac /= 10)
        buf.push_front((frac % 10) + '0');
            buf.push_front(".");
    }
    for (; whole; whole /= 10)
        buf.push_front((whole % 10) + '0');
    if (is_negative)
        buf.push_front('-');
    return buf;
}

template<std::floating_point T>
string to_string(T num, int prec){
    if (!prec)
        throw ArgError("to_string() : Precision cannot be lower than 1");
    prec = ((prec > 15) ? 15 : prec);
    string buf;
    bool is_negative{};
    if (num < 0){
        num = -num;
        is_negative = true;
    }
    long long whole{static_cast<long long>(num)};
    long long frac = static_cast<long long>((num - whole) * pow(10, prec));
    if (frac){
        for (; frac; frac /= 10)
            buf.push_front((frac % 10) + '0');
        buf.push_front('.');
    }
    else{
        for (; prec; --prec)
            buf.push_back('0');
        buf.push_front('.');
    }
    for (; whole; whole /= 10)
        buf.push_front((whole % 10) + '0');
    if (is_negative)
        buf.push_front('-');
    return buf;
}

inline string& get(string& str);
inline bool getline(std::istream& input, string& str);
inline int get_int(const char* prompt);
inline long long get_llint(const char* prompt);
inline double get_double(const char* prompt);
inline string operator "" _s(const char* str, unsigned long long){ return {str}; }
// inline string operator "" _s(const char* str){ return {str}; }
inline string operator "" _s(unsigned long long num){ return to_string(num); }
inline string operator "" _s(long double num){ return to_string(num); }
inline deque<int> to_int(const string::string_list& li){
    deque<int> nums;
    for (auto& s : li)
        nums.push_back(s.stoi());
    return nums;
}

#endif  // __STRING_H