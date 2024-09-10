#ifndef __ARR_STRING_H
#define __ARR_STRING_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <climits>
#include <cmath>
#include "exceptions.h"
#include "..\deque\deque.h"
#include "reverse_iterator.h"

namespace __helpers{
    struct tautology{
        template<typename T>
        bool operator()(const T&){
            return true;
        }
    };
}

class CompactString;
class __string_input_buffer{
    public:
        __string_input_buffer() : buffer_size(100), cur(0), buf(new char[100]){}
        void insert(const char& ch){
            if (cur >= buffer_size)
                this->__buffer_expand();
            buf[cur++] = ch;
        }
        char* get_str(){
            if (cur >= buffer_size)
                this->__buffer_expand();
            buf[cur] = '\0';
            return buf;
        }
        unsigned int size(){
            return cur;
        }
        void clear_buffer(){
            this->cur = 0;
            this->buf[0] = 0;
        }
        ~__string_input_buffer(){
            delete[] buf;
            buf = nullptr;
            cur = buffer_size = 0;
        }
    
    private:
        unsigned int buffer_size;
        unsigned int cur;
        char* buf;
        
        void __buffer_expand(){
            char* newbuf = new char[buffer_size * 2];
            memcpy(newbuf, buf, buffer_size);
            buffer_size *= 2;
            delete[] buf;
            buf = newbuf;
        }
        friend bool getline(std::istream& input, CompactString& str);
};

class CompactString {
    public:
        typedef                                                      char              value_type;
        typedef                                                      char*             iterator;
        typedef                                                const char*             const_iterator;
        typedef                   __reverse_iterator<iterator, value_type>             reverse_iterator;
        typedef       __const_reverse_iterator<const_iterator, value_type>             const_reverse_iterator;
        typedef                                              deque<size_t>             IndexList;
        typedef                                       deque<CompactString>             StringList;
    
    public:
        CompactString();
        CompactString(size_t size);
        CompactString(char ch, size_t num);
        CompactString(const char* str);
        CompactString(const std::string& str);
        CompactString(const CompactString& src);
        CompactString(CompactString&& src);
        ~CompactString();

        size_t size() const;

        /**
         * @brief Returns a C-String (a const char*) of the underlying string.
         * @returns A const char* to a null terminated array of characters
         * (C-style string).
        */
        const char* c_str() const;

        /**
         * @brief Checks whether the string is empty or not.
         * @returns A boolean value indicating whether the string is empty.
        */
        bool is_empty() const;

        /**
         * @brief Checks whether each character of the string is an alphabetic
         * character or not.
         * @returns A boolean value indicating whether the string is composed
         * of only alphabetic characters.
        */
        bool is_alpha() const;

        /**
         * @brief Checks whether each character of the string is numeric or
         * not.
         * @returns A boolean value indicating whether the string is composed
         * of only numeric characters.
        */
        bool is_numeric() const;

        /**
         * @brief Checks whether each character of the string is alphanumeric
         * or not.
         * @returns A boolean value indicating whether the string is composed
         * of only alphanumeric characters.
        */
        bool is_alnum() const;

        /**
         * @brief Returns a new string object containing only the first word
         * of the complete string.
         * @returns A new string object.
        */
        CompactString first_word() const;

        /**
         * @brief Returns a new string object containing only the last word of
         * the complete string.
         * @returns A new string object.
        */
        CompactString last_word() const;

        /**
         * @brief Create and return a new string with all characters in
         * lowercase.
         * @returns A new string with all characters in lowercase.
        */
        CompactString get_lower() const;

        /**
         * @brief Create and return a new string with all characters in
         * uppercase.
         * @returns A new string with all characters in uppercase.
        */
        CompactString get_upper() const;

        /**
         * @brief Make the string lowercase in place and return a reference
         * to the current string object.
         * @returns Reference to the string object.
        */
        CompactString& to_lower();

        /**
         * @brief Make the string uppercase in place and return a reference
         * to the string.
         * @returns Reference to the string object.
        */
        CompactString& to_upper();

        /**
         * @brief Capitalizes the first character of the string. Leading
         * whitespace is ignored.
         * @returns Reference to the capitalized string.
        */
        CompactString& capitalize();

        CompactString& title();

        CompactString titled() const;

        CompactString& collapse();

        CompactString collapsed() const;

        /**
         * @brief Creates and returns a new string containing the binary
         * representation of the number in the string.
         * @note Requires that the string be a numeric string (containing
         * only characters 0 - 9).
         * @returns A string containing the binary representation.
         * @throws ValueError if the string is not numeric
        */
        CompactString bstring() const;

        /**
         * @brief Creates and returns a new string containing the binary
         * representation of the number in the string with the specified width
         * i.e., the number of characters which appear in the binary
         * representation.
         * @param width Specifies the number of characters to be used in the
         * binary representation.
         * @note Requires that the string be a numeric string (containing
         * only characters 0 - 9).
         * @returns A string containing the binary representation.
         * @throws ValueError if the width of the string specified is less
         * than 1 or if the string is not numeric.
        */
        CompactString bstring(int width) const;

        /**
         * @brief Creates and returns a string containing the binary
         * representation of num.
         * @param num The number whose binary representation is required.
         * @returns A string containing the binary representation.
        */
        friend CompactString bstring(int num);
        friend CompactString bstring(unsigned int num);
        friend CompactString bstring(long long num);
        friend CompactString bstring(unsigned long long num);

        /**
         * @brief Creates and returns a string containing the binary
         * representation of num with the specified width i.e., the number of
         * characters which appear in the binary representation.
         * @param num The number whose binary representation is required.
         * @param width Specifies the number of characters to be used in the
         * binary representation.
         * @returns A string containing the binary representation.
         * @throws ValueError if the width specified is less than 1.
        */
        friend CompactString bstring(int num, int width);
        friend CompactString bstring(unsigned int num, int width);
        friend CompactString bstring(long long num, int width);
        friend CompactString bstring(unsigned long long num, int width);

        /**
         * @brief Reverses and returns a reference to the string.
         * @returns Reference to the string object.
        */
        CompactString& reverse();

        /**
         * @brief Creates and returns a new string with the characters in
         * reverse order with respect to the current string.
         * @returns A new string object with the reversed string.
        */
        CompactString reversed() const;

        /**
         * @brief Perform case insensitive comparison of the current string
         * with string rhs.
        */
        bool similar(const CompactString& rhs) const;

        /**
         * @brief Perform case insensitive comparison of the current string
         * with C-Style string(const char*) rhs.
        */
        bool similar(const char* rhs) const;

        /**
         * @brief Returns the number of appearances of character ch in the
         * string.
         * @param ch The character whose number of occurrences are to be
         * counted.
         * @returns Number of times ch occurs in the string.
        */
        size_t count(char ch) const;

        /**
         * @brief Counts and returns the number of occurrences of the pattern
         * in the string.
         * @param pattern The pattern string whose number of occurrences need
         * to be found.
         * @returns Number of times the pattern occurs in the string.
        */
        size_t count(const char* pattern) const;

        /**
         * @brief Counts and returns the number of occurrences(case-insensitive)
         * of the pattern in the string.
         * @param pattern The pattern string whose number of occurrences need
         * to be found case-insensitively.
         * @returns Number of times the pattern occurs in the string.
        */
        size_t counti(const char* pattern) const;

        /**
         * @brief Counts and returns the number of occurrences of the pattern
         * in the string.
         * @param pattern The pattern string whose number of occurrences need
         * to be found.
         * @returns Number of times the pattern occurs in the string.
        */
        size_t count(const CompactString& pattern) const;

        /**
         * @brief Counts and returns the number of occurrences(case-insensitive)
         * of the pattern in the string.
         * @param pattern The pattern string whose number of occurrences need
         * to be found case-insensitively.
         * @returns Number of times the pattern occurs in the string.
        */
        size_t counti(const CompactString& pattern) const;

        /**
         * @brief Check if the pattern occurs in the string.
         * @param pattern The pattern string whose occurrence is checked.
         * @returns A boolean value indicating whether the string contains the
         * pattern or not.
        */
        bool contains(const char* pattern) const;

        /**
         * @brief Check if the pattern occurs in the string(case-insensitive).
         * @param pattern The pattern string whose occurrence is checked.
         * @returns A boolean value indicating whether the string contains the
         * pattern or not.
        */
        bool containsi(const char* str) const;

        /**
         * @brief Check if the pattern occurs in the string.
         * @param pattern The pattern string whose occurrence is checked.
         * @returns A boolean value indicating whether the string contains the
         * pattern or not.
        */
        bool contains(const CompactString& pattern) const;

        /**
         * @brief Check if the pattern occurs in the string(case-insensitive).
         * @param pattern The pattern string whose occurrence is checked.
         * @returns A boolean value indicating whether the string contains the
         * pattern or not.
        */
        bool containsi(const CompactString& pattern) const;

        /**
         * @brief Searches for the query string within the string and returns
         * the starting index of the query string within the string.
         * @param query The string to search for.
         * @returns The index value where the query is found within the
         * string. Returns -1 if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        long long search(const char* query) const;

        /**
         * @brief Searches for the query string within the string and returns
         * the starting index of the query string within the string.
         * @param query The string to search for.
         * @returns The index value where the query is found within the
         * string. Returns -1 if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        long long search(const CompactString& query) const;

        long long search(char ch) const;

        /**
         * @brief Searches for the query string case-insensitively within the
         * string and returns the starting index of the query string within
         * the string.
         * @param query The string to search for.
         * @returns The index value where the query is found within the
         * string. Returns -1 if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        long long searchi(const char* query) const;

        /**
         * @brief Searches for the query string case-insensitively within the
         * string and returns the starting index of the query string within
         * the string.
         * @param query The string to search for.
         * @returns The index value where the query is found within the
         * string. Returns -1 if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        long long searchi(const CompactString& query) const;

        /**
         * @brief Searches for all the occurrences of the query string in the
         * string and returns a list of positions of all the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        IndexList search_all(const char* query) const;

        /**
         * @brief Searches for all the occurrences of the query string in the
         * string and returns a list of positions of all the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        IndexList search_all(const CompactString& query) const;

        /**
         * @brief Searches for all the occurrences of the query string case
         * insensitively in the string and returns a list of positions of all
         * the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        IndexList search_alli(const char* query) const;

        /**
         * @brief Searches for all the occurrences of the query string case
         * insensitively in the string and returns a list of positions of all
         * the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        IndexList search_alli(const CompactString& query) const;
        
        /**
         * @brief Replace each occurrence of to_replace with replacement_char
         * in the string and return a reference to the modified string.
         * @param to_replace The character(case-sensitive) to replace in the
         * string.
         * @param replacement_char The character to be inserted in place of
         * each occurrence of to_replace.
         * 
         * @returns A reference to the modified string.
        */
        CompactString& replace(char to_replace, char replacement_char);
        /**
         * @brief Fills the entire string with the fill_char character and
         * returns a reference to the string
         * @param fill_char The character to be used to fill the string
         * @returns A reference to the modified string.
        */
        CompactString& fill(char fill_char);

        /**
         * @brief Return a new string containing n number of characters from
         * the start of the current string.
         * @returns A new string object.
        */
        CompactString operator()(size_t n) const;

        /**
         * @brief Return a new string containing characters from the current
         * string starting from index start, going up to end.
         * @returns A new string object.
        */
        CompactString operator()(size_t start, size_t end) const;

        /**
         * @brief Return a new string containing n characters from the start
         * of the current string.
         * @returns A new string object.
        */
        CompactString slice(size_t end) const;

        /**
         * @brief Return a new string containing characters from the current
         * string starting from index start, going up to end.
         * @returns A new string object.
        */
        CompactString slice(size_t start, size_t end) const;

        /**
         * @brief Return a new string with all characters from the current
         * string starting from the index pos.
         * @param pos The position from which the characters are to be copied
         * in the new string
         * @returns A new string containing all characters from the current
         * string after the index pos.
        */
        CompactString from_pos(size_t pos) const;

        CompactString from_pos(size_t pos, size_t count) const;

        /**
         * @brief Return a string containing count number of characters from
         * the end of the current string.
         * @param count Number of characters from the end to include.
         * @return A new string containing count number of characters from the
         * end.
        */
        CompactString nlast(size_t count) const;

        /**
         * @brief Strip all whitespace characters from the left (the
         * beginning) of the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        CompactString& lstrip();

        /**
         * @brief Strip all the whitespace characters from the right (the
         * end) of the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        CompactString& rstrip();

        /**
         * @brief Strip all the whitespace characters from both the ends of
         * the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        CompactString& strip();

        /**
         * @brief Splits the string at character ch and returns a list of the
         * individual components obtained after splitting.
         * @param ch The character in the string to split on.
         * @returns A list of strings.
        */
        StringList split(char ch = ' ') const;

        /**
         * @brief Generates an integer from a string containing numeric
         * characters.
         * Whitespace does not matter at the beginning or at the end of the
         * string.
         * @returns An integer generated using the string.
        */
        int stoi() const;
        
        /**
         * @brief Generates a long long integer from a string containing
         * numeric characters.
         * Whitespace does not matter at the beginning or at the end of the
         * string.
         * @returns A long long integer generated using the string.
        */
        long long stoll() const;

        /**
         * @brief Generates a double from a string containing
         * numeric characters.
         * Whitespace does not matter at the beginning or at the end of the
         * string.
         * @returns A double generated using the string.
        */
        double stod() const;

        /**
         * @brief Generates a long double from a string containing
         * numeric characters.
         * Whitespace does not matter at the beginning or at the end of the
         * string.
         * @returns A long double generated using the string.
        */
        long double stold() const;

        /**
         * @brief Generates an integer from a string containing a binary
         * representation i.e., a string with only zeros and ones.
         * @returns An integer generated from the binary representation
         * in the string.
        */
        int btoi() const;

        /**
         * @brief Generates a long long integer from a string containing a
         * binary representation i.e., a string with only zeros and ones.
         * @returns A long long integer generated from the binary
         * representation in the string.
        */
        long long btoll() const;

        /**
         * @brief Modify each character of the string one by one by executing
         * mod_fun on the character which satisfies the predicate pred
         * and storing the result back into the character.
         * @param mod_fun A function like object(Pointer to a function, a
         * functor, a lambda expression or an std::function) to for the
         * modification.
         * @param pred A function like object which determines which characters
         * will be modified.
         * @returns A reference to the modified string.
        */
        template<typename Modifier, typename Predicate = __helpers::tautology>
        CompactString& modify(Modifier mod_fun = {}, Predicate pred = {});

        template<typename Modifier>
        CompactString& transform(Modifier mod_fun = {});

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

        // Defining the three way comparison operator provides the
        // ability to use '<', '<=', '>', '=>' operators on our strings
        friend std::strong_ordering operator<=>(const CompactString& lhs, const CompactString& rhs);
        friend std::strong_ordering operator<=>(const CompactString& lhs, const char* rhs);

        // Operator == tests for strict equality (case sensitive).
        friend bool operator==(const CompactString& lhs, const CompactString& rhs);
        friend bool operator==(const CompactString& lhs, const char* rhs);

        // Operator + concatenates two strings
        friend CompactString operator+(const CompactString& lhs, const CompactString& rhs);
        friend CompactString operator+(const CompactString& lhs, const char* rhs);
        friend CompactString operator+(const char* lhs, const CompactString& rhs);

        CompactString& operator+=(const char* rhs);
        CompactString& operator+=(const CompactString& rhs);
        
        // Access elements of the string using array index notation.
        char& operator[](unsigned long long i);
        const char& operator[](unsigned long long i) const;

        CompactString& operator=(const char* str);
        CompactString& operator=(const CompactString& str);
        CompactString& operator=(CompactString&& str);
        CompactString& operator=(__string_input_buffer& buf);

        operator std::string_view() const;
        operator bool() const;

        template<typename U>
        requires std::is_integral_v<U>
        friend CompactString to_string(U num);

        template<typename U>
        requires std::is_integral_v<U>
        friend CompactString to_string(U num, int width);

        template<typename U>
        requires std::is_integral_v<U>
        friend CompactString to_string(U num, int width, char padding_char);

        friend std::ostream& operator<<(std::ostream& output, const CompactString& str);
        friend std::ofstream& operator<<(std::ofstream& output, const CompactString& str);
        friend std::istream& operator>>(std::istream& input, CompactString& str);
        friend std::ifstream& operator>>(std::ifstream& input, CompactString& str);
        friend bool getline(std::istream& input, CompactString& str);
        // string(__string_input_buffer& buf);
    
    private:
        char* __str{nullptr};
        size_t __size{0};
        static inline const char* __dummy{""};

        typedef bool (*__char_compare_fun)(char, char);
        
        CompactString(int num, int, int);
        CompactString(unsigned int num, int, int);

        CompactString(long long num, int, int);
        CompactString(unsigned long long num, int, int);
        
        CompactString(int num, int width, int, int);
        CompactString(unsigned int num, int width, int, int);
        
        CompactString(long long num, int width, int, int);
        CompactString(unsigned long long num, int width, int, int);
        
        CompactString(__string_input_buffer& buf);

        void invalidate();
        CompactString& clear_string();
        CompactString& make(size_t size);
        
        static bool __char_comp(char __x, char __y);
        static bool __char_comp_i(char __x, char __y);

        bool __contains_v(const char* pattern, size_t& m) const;
        static bool __contains(const char* str, size_t n, const char* pattern, size_t m, __char_compare_fun comp);
        
        bool __search_v(const char* query, size_t& m) const;
        static long long __search(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp);
        
        bool __search_all_v(const char* query, size_t& m) const;
        static IndexList __search_all(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp);
        
        size_t __count(const char* pattern, __char_compare_fun comp) const;

        template<typename U>
        requires std::is_integral_v<U>
        static CompactString __to_string(U num, int width = 0, char padding_char = '0');
};

bool __is_whitespace(const char& ch){
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

CompactString::CompactString(size_t size) : __str(new char[size + 1]), __size(size){
    this->__str[size] = 0;
#ifdef ARR_STRING_DEBUG
    std::cout << "string created with size "<< size << " at " << this << '\n';
#endif
}

CompactString::CompactString(int num, int, int){
    int i{31}, j{};
    for (; (i >= 0) && (((1 << i) & num) == 0); --i);
    if (i == -1){
        this->make(0);
        this->__str[0] = '0';
    }
    else{
        this->make(i + 1);
        for (; i >= 0; --i, ++j)
            this->__str[j] = (((1LL << i) & num) != 0) + '0';
    }
}

CompactString::CompactString(unsigned int num, int, int){
    int i{31}, j{};
    for (; (i >= 0) && (((1LL << i) & num) == 0); --i);
    if (i == -1){
        this->make(0);
        this->__str[0] = '0';
    }
    else{
        this->make(i + 1);
        for (; i >= 0; --i, ++j)
            this->__str[j] = (((1LL << i) & num) != 0) + '0';
    }
}

CompactString::CompactString(long long num, int, int){
    int i{63}, j{};
    for (; (i >= 0) && (((1LL << i) & num) == 0); --i);
    if (i == -1){
        this->make(0);
        this->__str[0] = '0';
    }
    else{
        this->make(i + 1);
        for (; i >= 0; --i, ++j)
            this->__str[j] = (((1LL << i) & num) != 0) + '0';
    }
}

CompactString::CompactString(unsigned long long num, int, int){
    int i{63}, j{};
    for (; (i >= 0) && (((1LL << i) & num) == 0); --i);
    if (i == -1){
        this->make(0);
        this->__str[0] = '0';
    }
    else{
        this->make(i + 1);
        for (; i >= 0; --i, ++j)
            this->__str[j] = (((1LL << i) & num) != 0) + '0';
    }
}

CompactString::CompactString(int num, int width, int, int) : CompactString(width){
    for (int i{width - 1}, j{}; i >= 0; --i, ++j)
        this->__str[j] = ((((1LL << i) & num) != 0) + '0');
}

CompactString::CompactString(unsigned int num, int width, int, int) : CompactString(width){
    for (int i{width - 1}, j{}; i >= 0; --i, ++j)
        this->__str[j] = ((((1LL << i) & num) != 0) + '0');
}

CompactString::CompactString(long long num, int width, int, int) : CompactString(width){
    for (int i{width - 1}, j{}; i >= 0; --i, ++j)
        this->__str[j] = ((((1LL << i) & num) != 0) + '0');
}

CompactString::CompactString(unsigned long long num, int width, int, int) : CompactString(width){
    for (int i{width - 1}, j{}; i >= 0; --i, ++j)
        this->__str[j] = ((((1LL << i) & num) != 0) + '0');
}

CompactString::CompactString(__string_input_buffer& buf) : CompactString(buf.size()){
    memcpy(this->__str, buf.get_str(), this->__size);
}

CompactString::CompactString(){
#ifdef ARR_STRING_DEBUG
    std::cout << "Empty string created at " << this << '\n';
#endif
}

CompactString::CompactString(const char* str) : CompactString(std::strlen(str)){
#ifdef ARR_STRING_DEBUG
    std::cout << "string created using const char* at " << this << '\n';
#endif
    memcpy(this->__str, str, __size);
}

CompactString::CompactString(char ch, size_t size) : CompactString(size){
    for (char& c : *this)
        c = ch;
#ifdef ARR_STRING_DEBUG
    std::cout << "string of size " << size << " created and filled with '"
        << ch << "' characters at " << this << '\n';
#endif
}

CompactString::CompactString(const std::string& str) : CompactString(str.size()){
#ifdef ARR_STRING_DEBUG
    std::cout << "string created using const std::string& at " << this << '\n';
#endif
    memcpy(this->__str, str.c_str(), str.size());
}

CompactString::CompactString(const CompactString& src) : CompactString(src.size()){
#ifdef ARR_STRING_DEBUG
    std::cout << "string copied from " << &src << " to " << this << '\n';
#endif
    memcpy(this->__str, src.__str, this->__size);
}

CompactString::CompactString(CompactString&& src){
#ifdef ARR_STRING_DEBUG
    std::cout << "string moved from " << &src << " to " << this << '\n';
#endif
    this->__str = src.__str;
    this->__size = src.__size;
    src.invalidate();
}

CompactString::~CompactString(){
#ifdef ARR_STRING_DEBUG
    std::cout << "Destroyed string at " << this << '\n';
#endif
    if (this->__str){
        delete[] this->__str;
        this->invalidate();
    }
}

void CompactString::invalidate(){
    this->__str = nullptr;
    this->__size = 0;
}

CompactString& CompactString::clear_string(){
    delete[] this->__str;
    this->invalidate();
    return *this;
}

CompactString& CompactString::make(size_t size){
    this->__str = new char[size + 1];
    this->__size = size;
    this->__str[size] = 0;
    return *this;
}

size_t CompactString::size() const{
    return this->__size;
}

const char* CompactString::c_str() const{
    if (this->is_empty())
        return this->__dummy;
    return this->__str;
}

bool CompactString::is_empty() const{
    return (!this->__size);
}

bool CompactString::is_alpha() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (!std::isalpha(*iter))
            return false;
    return true;
}

bool CompactString::is_alnum() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (!std::isalnum(*iter))
            return false;
    return true;
}

bool CompactString::is_numeric() const{
    if (this->is_empty())
        return false;
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (*iter < '0' || *iter > '9')
            return false;
    return true;
}

CompactString CompactString::first_word() const{
    if (is_empty())
        return {};
    
    const_iterator begin = this->begin(), end = this->end();
    for (; __is_whitespace(*begin); ++begin);
    if (begin == end)
        return {};
    __string_input_buffer buf;
    for (; (begin < end) && (!__is_whitespace(*end)); ++begin)
        buf.insert(*begin);
    return CompactString{buf};
}

CompactString CompactString::last_word() const{
    if (is_empty())
        return {};
    
    const_iterator begin = this->begin(), rear = this->end() - 1;
    for (; (begin < rear) && __is_whitespace(*rear); --rear);
    if (__is_whitespace(*rear))
        return {};
    const_iterator lw_end = rear + 1, lw_begin;
    for (; (begin < rear) && (!__is_whitespace(*rear)); --rear);
    if (rear == begin)
        lw_begin = rear;
    else
        lw_begin = rear + 1;
    CompactString tmp(lw_end - lw_begin);
    iterator iter = tmp.begin();
    for (; lw_begin != lw_end; ++lw_begin, ++iter)
        *iter = *lw_begin;
    return tmp;
}

CompactString CompactString::get_lower() const{
    if (this->is_empty())
        return {};
    
    CompactString tmp{this->__size};
    const_iterator s_iter = this->begin();
    iterator iter = tmp.begin(), end = tmp.end();
    for (; iter != end; ++iter, ++s_iter)
        *iter = std::tolower(*s_iter);
    return tmp;
}

CompactString CompactString::get_upper() const {
    if (this->is_empty())
        return {};
    
    CompactString tmp{this->__size};
    const_iterator s_iter = this->begin();
    iterator iter = tmp.begin(), end = tmp.end();
    for (; iter != end; ++iter, ++s_iter)
        *iter = std::toupper(*s_iter);
    return tmp;
}

CompactString& CompactString::to_lower(){
    iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        *iter = std::tolower(*iter);
    return *this;
}

CompactString& CompactString::to_upper(){
    iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter)
        *iter = std::toupper(*iter);
    return *this;
}

CompactString& CompactString::capitalize(){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin();
    iterator end = this->end();
    for (; (iter != end) && (__is_whitespace(*iter)); ++iter);
    if (iter != end)
        *iter = std::toupper(*iter);
    return *this;
}

CompactString& CompactString::title(){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin();
    iterator end = this->end();
    *iter = std::toupper(*iter);
    for (; iter < end; ++iter){
        if (__is_whitespace(*iter)){
            for (; (iter != end) && (__is_whitespace(*iter)); ++iter);
            *iter = std::toupper(*iter);
        }
    }
    return *this;
}

CompactString CompactString::titled() const{
    if (this->is_empty())
        return *this;
    return CompactString{*this}.title();
}

CompactString& CompactString::collapse(){
    if (this->is_empty())
        return *this;
    *this = std::move(this->collapsed());
    return *this;
}

CompactString CompactString::collapsed() const{
    if (this->is_empty())
        return {};
    const_iterator iter = this->begin(), end = this->end() - 1;
    for (; __is_whitespace(*iter); ++iter);
    if (iter == this->end())
        return {" "};
    for (; (iter < end) && (__is_whitespace(*end)); --end);
    if (iter == end)
        return {" "};
    __string_input_buffer buf;
    for (; iter <= end; ++iter){
        if (__is_whitespace(*iter)){
            buf.insert(' ');
            for (; (iter != end) && (__is_whitespace(*iter)); ++iter);
            buf.insert(*iter);
        }
        else
            buf.insert(*iter);
    }
    return CompactString(buf);
}

CompactString CompactString::bstring(int width) const{
    if (width < 1)
        throw ValueError("CompactString::bstring()\nWidth must be greater than 1");
    if (width > 64)
        width = 64;
    CompactString cleaned{*this};
    cleaned.strip();
    if (cleaned.is_numeric())
        return CompactString{cleaned.stoll(), width, 0, 0};
    else
        throw ValueError("CompactString::bstring()\nString must be numeric");
}

CompactString CompactString::bstring() const{
    CompactString cleaned{*this};
    cleaned.strip();
    if (cleaned.is_numeric())
        return CompactString(cleaned.stoll(), 0, 0);
    else
        throw ValueError("CompactString::bstring()\nString must be numeric");
}

CompactString bstring(int num){
    return CompactString(num, 0,0);
}

CompactString bstring(unsigned int num){
    return CompactString(num, 0, 0);
}

CompactString bstring(long long num){
    return CompactString(num, 0, 0);
}

CompactString bstring(unsigned long long num){
    return CompactString(num, 0, 0);
}

CompactString bstring(int num, int width){
    if (width < 1)
        throw ValueError("bstring()\nWidth must be greater than 1");
    if (width > 64)
        width = 64;
    return CompactString(num, width, 0, 0);
}

CompactString bstring(unsigned int num, int width){
    if (width < 1)
        throw ValueError("bstring()\nWidth must be greater than 1");
    if (width > 64)
        width = 64;
    return CompactString(num, width, 0, 0);
}

CompactString bstring(long long num, int width){
    if (width < 1)
        throw ValueError("bstring()\nWidth must be greater than 1");
    if (width > 64)
        width = 64;
    return CompactString(num, width, 0, 0);
}

CompactString bstring(unsigned long long num, int width){
    if (width < 1)
        throw ValueError("bstring()\nWidth must be greater than 1");
    if (width > 64)
        width = 64;
    return CompactString(num, width, 0, 0);
}

CompactString& CompactString::reverse(){
    if (this->__size < 2)
        return *this;
    iterator front = this->begin();
    iterator rear = this->end() - 1;
    char tmp;
    for (; front < rear; front++, rear--){
        tmp = *front;
        *front = *rear;
        *rear = tmp;
    }
    return *this;
}

CompactString CompactString::reversed() const{
    if (this->__size < 2)
        return *this;
    CompactString new_str{this->__size};
    iterator ptr = new_str.end() - 1;
    const_iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter, --ptr)
        *ptr = *iter;
    return new_str;
}

bool CompactString::similar(const CompactString& rhs) const {
    if (*this == rhs)
        return true;
    if (this->is_empty() || rhs.is_empty() || (this->__size != rhs.__size))
        return false;
    
    const_iterator rhs_str = rhs.__str, lhs_str = this->__str;
    for (size_t i{}; i < __size; i++)
        if (std::tolower(*(lhs_str++)) != std::tolower(*(rhs_str++)))
            return false;
    return true;
}

bool CompactString::similar(const char* rhs) const {
    if ((this->__size != std::strlen(rhs)))
        return false;
    
    char* lhs_str = this->__str;
    for (size_t i{}; i < __size; i++)
        if (std::tolower(*(lhs_str++)) != std::tolower(*(rhs++)))
            return false;
    return true;
}

size_t CompactString::count(char ch) const {
    if (this->is_empty())
        return 0;
    size_t count{};
    for (const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (*iter == ch)
            ++count;
    return count;
}

bool CompactString::contains(const char* pattern) const{
    size_t m{};
    if (this->__contains_v(pattern, m))
        return this->__contains(this->begin(), this->__size, pattern, m, this->__char_comp);
    return false;
}

bool CompactString::containsi(const char* pattern) const{
    size_t m{};
    if (this->__contains_v(pattern, m))
        return this->__contains(this->begin(), this->__size, pattern, m, this->__char_comp_i);
    return false;
}

bool CompactString::contains(const CompactString& pattern) const{
    return this->contains(pattern.begin());
}

bool CompactString::containsi(const CompactString& pattern) const{
    return this->containsi(pattern.begin());
}

long long CompactString::search(const char* query) const{
    size_t m{};
    if (this->__search_v(query, m))
        return this->__search(this->begin(), this->__size, query, m, this->__char_comp);
    return -1;
}

long long CompactString::search(const CompactString& query) const{
    return this->search(query.begin());
}

long long CompactString::search(char ch) const {
    const char* str = this->__str;
    long long i{};
    for (; *str; ++i, ++str)
        if (*str == ch)
            return i;
    return -1;
}

long long CompactString::searchi(const char* query) const{
    size_t m{};
    if (this->__search_v(query, m))
        return this->__search(this->begin(), this->__size, query, m, this->__char_comp_i);
    return -1;
}

long long CompactString::searchi(const CompactString& query) const{
    return this->searchi(query.begin());
}

CompactString::IndexList CompactString::search_all(const char* query) const{
    size_t m{};
    if (this->__search_all_v(query, m))
        return this->__search_all(this->begin(), this->__size, query, m, this->__char_comp);
    return IndexList((size_t)0);
}

CompactString::IndexList CompactString::search_all(const CompactString& query) const{
    return this->search_all(query.begin());
}

CompactString::IndexList CompactString::search_alli(const char* query) const{
    size_t m{};
    if (this->__search_all_v(query, m))
        return this->__search_all(this->begin(), this->__size, query, m, this->__char_comp_i);
    return IndexList((size_t)0);
}

CompactString::IndexList CompactString::search_alli(const CompactString& query) const{
    return this->search_alli(query.begin());
}

size_t CompactString::count(const char* pattern) const{
    return this->__count(pattern, this->__char_comp);
}

size_t CompactString::counti(const char* pattern) const{
    return this->__count(pattern, this->__char_comp_i);
}

size_t CompactString::count(const CompactString& pattern) const{
    return this->count(pattern.begin());
}

size_t CompactString::counti(const CompactString& pattern) const{
    return this->counti(pattern.begin());
}

CompactString& CompactString::replace(char to_replace, char replacement_char){
    for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        if (*iter == to_replace)
            *iter = replacement_char;
    return *this;
}

CompactString& CompactString::fill(char fill_char){
    for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        *iter = fill_char;
    return *this;
}

CompactString CompactString::operator()(size_t end) const{
    return this->slice(end);
}

CompactString CompactString::operator()(size_t start, size_t end) const{
    return this->slice(start, end);
}

CompactString CompactString::slice(size_t end) const{
    if (end >= this->__size)
        return *this;
    CompactString tmp(end);
    memcpy(tmp.begin(), this->begin(), end);
    return tmp;
}

CompactString CompactString::slice(size_t start, size_t end) const{
    if ((start >= end) || (start >= __size))
        throw IndexError();
    size_t size{end - start};
    if (end >= this->__size)
        size = this->__size - start;
    CompactString tmp(size);
    memcpy(tmp.begin(), this->begin() + start, size);
    return tmp;
}

CompactString CompactString::from_pos(size_t pos) const{
    if (pos == 0)
        return *this;
    if (pos >= (__size))
        throw IndexError("CompactString::from_pos(): invalid value of pos");
    size_t size{__size - pos};
    CompactString tmp(size);
    memcpy(tmp.begin(), this->begin() + pos, size);
    return tmp;
}

CompactString CompactString::from_pos(size_t pos, size_t count) const{
    if (!count)
        throw ValueError("CompactString::from_pos(): count cannot be zero");
    if (!pos)
        return this->slice(count);
    if (pos >= (this->__size))
        throw IndexError("CompactString::from_pos(): invalid value of pos");
    if ((pos + count) >= this->__size)
        return this->from_pos(pos);
    
    CompactString tmp{count};
    memcpy(tmp.begin(), this->begin() + pos, count);
    return tmp;
}

CompactString CompactString::nlast(size_t count) const{
    if (count > __size)
        return *this;
    if (!count)
        return {};
    CompactString tmp(count);
    memcpy(tmp.begin(), this->begin() + (__size - count), count);
    return tmp;
}

CompactString& CompactString::lstrip(){
    if (this->is_empty())
        return *this;
    
    char* ptr = this->begin(), *new_str{};
    size_t wcount{}, new_size{};
    if (!__is_whitespace(*ptr))
        return *this;
    for (; (*ptr != 0) && (__is_whitespace(*ptr)); ++ptr, ++wcount);
    if (*ptr == 0)
        return this->clear_string();
    
    new_size = this->__size - wcount;
    new_str = new char[new_size];
    memcpy(new_str, this->begin() + wcount, new_size + 1);
    delete[] this->__str;
    this->__str = new_str;
    this->__size = new_size;
    return *this;
}

CompactString& CompactString::rstrip(){
    if (this->is_empty())
        return *this;
    
    char* ptr = this->begin() + this->__size - 1, *new_str{};
    size_t wcount{}, new_size{};
    if (!__is_whitespace(*ptr))
        return *this;
    for (; (wcount < this->__size) && (__is_whitespace(*ptr)); --ptr, ++wcount);
    if (wcount == this->__size)
        return this->clear_string();
    
    new_size = this->__size - wcount;
    new_str = new char[new_size + 1];
    memcpy(new_str, this->begin(), new_size);
    new_str[new_size] = 0;
    delete[] this->__str;
    this->__str = new_str;
    this->__size = new_size;
    return *this;
}

CompactString& CompactString::strip(){
    if (this->is_empty())
        return *this;
    char* fptr = this->begin(), *rptr = this->begin() + this->__size - 1, *new_str{};
    size_t new_size{};
    if ((!__is_whitespace(*fptr)) && (!__is_whitespace(*rptr)))
        return *this;
    for (; (fptr < rptr) && (__is_whitespace(*fptr)); ++fptr);
    for (; (fptr < rptr) && (__is_whitespace(*rptr)); --rptr);
    if (__is_whitespace(*fptr))
        return this->clear_string();
    new_size = (rptr - fptr) + 1;
    new_str = new char[new_size + 1];
    new_str[new_size] = 0;
    for (char* nptr = new_str; fptr <= rptr; ++fptr, ++nptr)
        *nptr = *fptr;
    delete[] this->__str;
    this->__str = new_str;
    this->__size = new_size;
    return *this;
}

CompactString::StringList CompactString::split(char ch) const{
    StringList str_list;
    __string_input_buffer buf;
    const_iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter){
        if (*iter == ch){
            str_list.append(CompactString(buf));
            buf.clear_buffer();
        }
        else
            buf.insert(*iter);
    }
    if (buf.size()){
        str_list.append(CompactString(buf));
    }
    return str_list;
}

template<typename Modifier, typename Predicate>
CompactString& CompactString::modify(Modifier mod_fun, Predicate pred){
    if (this->is_empty())
        return *this;
    iterator iter = this->begin();
    iterator end = this->end();
    for (; iter != end; ++iter)
        if (pred(*iter))
            *iter = mod_fun(*iter);
    return *this;
}

template<typename Modifier>
CompactString& CompactString::transform(Modifier mod_fun){
    mod_fun(this->begin(), this->__size);
    return *this;
}

int CompactString::stoi() const{
    if (this->is_empty())
        throw ValueError("String empty");
    
    double num{};
    bool is_negative{false};
    
    const_iterator arr = this->begin();
    const_iterator end = this->end() - 1;
    
    for (; __is_whitespace(*arr); ++arr);
    if (arr == this->end())
        throw ValueError("Invalid input to stoi");
    for (; (arr < end) && __is_whitespace(*end); --end);
    if (__is_whitespace(*arr))
        throw ValueError("Invalid input to stoi");
    
    if (*arr == '-'){
        is_negative = true;
        ++arr;
    }
    else if (*arr == '+')
        ++arr;
    
    for (; (arr <= end) && (*arr >= '0' && *arr <= '9'); ++arr){
        num = ((num * 10) + (*arr - '0'));
    }
    
    if (arr != (end + 1))
        throw ValueError("Invalid input to stoi");
    
    if (is_negative)
        num = -num;
    if (num < INT_MIN)
        return INT_MIN;
    if (num > INT_MAX)
        return INT_MAX;
    
    return static_cast<int>(num);
}

long long CompactString::stoll() const{
    if (this->is_empty())
        throw ValueError("String empty");
    
    long double num{};
    bool is_negative{false};

    const_iterator arr = this->begin();
    const_iterator end = this->end() - 1;

    for (; __is_whitespace(*arr); ++arr);
    if (arr == this->end())
        throw ValueError("Invalid input to stoll");
    for (; (arr < end) && __is_whitespace(*end); --end);
    if (__is_whitespace(*arr))
        throw ValueError("Invalid input to stoll");
    
    if (*arr == '-'){
        is_negative = true;
        ++arr;
    }
    else if (*arr == '+')
        ++arr;
    
    for (; (arr <= end) && (*arr >= '0' && *arr <= '9'); ++arr){
        num = ((num * 10) + (*arr - '0'));
    }
    
    if (arr != (end + 1))
        throw ValueError("Invalid input to stoll");
    
    if (is_negative)
        num = -num;
    if (num < LLONG_MIN)
        return LLONG_MIN;
    if (num > LLONG_MAX)
        return LLONG_MAX;
    return static_cast<long long>(num);
}

double CompactString::stod() const{
    if (this->is_empty())
        throw ValueError("String empty");
    
    double num{}, div{10};
    bool is_negative{false};
    
    const_iterator iter = this->cbegin();
    const_iterator end = this->cend() - 1;
    
    for (; __is_whitespace(*iter); ++iter);
    if (iter == this->end())
        throw ValueError("Invalid input to stod");
    for (; (iter < end) && __is_whitespace(*end); --end);
    if (__is_whitespace(*iter))
        throw ValueError("Invalid input to stod");
    
    if (*iter == '-'){
        is_negative = true;
        ++iter;
    }
    else if (*iter == '+')
        ++iter;
    
    for (; (iter <= end) && (*iter >= '0' && *iter <= '9'); ++iter){
        num = ((num * 10) + (*iter - '0'));
    }
    if (*iter == '.'){
        for (++iter; (iter <= end) && (*iter >= '0' && *iter <= '9'); ++iter){
            num += ((*iter - '0') / div);
            div *= 10;
        }
    }

    if (iter != (end + 1))
        throw ValueError("Invalid input to stod");
    if (is_negative)
        num = -num;
    return num;
}

long double CompactString::stold() const{
    if (this->is_empty())
        throw ValueError("String empty");
    
    long double num{}, div{10};
    bool is_negative{false};
    
    const_iterator iter = this->cbegin();
    const_iterator end = this->cend();
    
    for (; __is_whitespace(*iter); ++iter);
    if (iter == this->end())
        throw ValueError("Invalid input to stold");
    for (; (iter < end) && __is_whitespace(*end); --end);
    if (__is_whitespace(*iter))
        throw ValueError("Invalid input to stold");
    
    if (*iter == '-'){
        is_negative = true;
        ++iter;
    }
    else if (*iter == '+')
        ++iter;
    
    for (; (iter <= end) && (*iter >= '0' && *iter <= '9'); ++iter){
        num = ((num * 10) + (*iter - '0'));
    }
    if (*iter == '.'){
        for (++iter; (iter <= end) && (*iter >= '0' && *iter <= '9'); ++iter){
            num += ((*iter - '0') / div);
            div *= 10;
        }
    }

    if (iter != (end + 1))
        throw ValueError("Invalid input to stold");
    if (is_negative)
        num = -num;
    return num;
}

int CompactString::btoi() const{
    if (this->is_empty())
        return 0;
    const_iterator iter = this->begin(), end = this->end() - 1;
    for (; (iter != end) && __is_whitespace(*iter); ++iter);
    for (; (iter != end) && __is_whitespace(*end); --end);
    if (iter == end)
        return 0;
    int size = (end - iter + 1), num{}, i{size - 1};
    if (size == 64 && *iter == '1')
        return INT_MIN;
    if (size > 32)
        return INT_MAX;
    for (; i >= 0; --i, ++iter)
        if (*iter == '1')
            num = (num | (1 << i));
        else if (*iter == '0')
            continue;
        else
            return 0;
    return num;
}

long long CompactString::btoll() const{
    if (this->is_empty())
        return 0;
    const_iterator iter = this->begin(), end = this->end() - 1;
    for (; (iter != end) && __is_whitespace(*iter); ++iter);
    for (; (iter != end) && __is_whitespace(*end); --end);
    if (iter == end)
        return 0;
    long long size = (end - iter + 1), num{}, i{size - 1};
    if (size > 64)
        return LLONG_MAX;
    for (; i >= 0; --i, ++iter)
        if (*iter == '1')
            num = (num | (1LL << i));
        else if (*iter == '0')
            continue;
        else
            return 0;
    return num;
}

CompactString::iterator CompactString::begin(){
    return this->__str;
}

CompactString::iterator CompactString::end(){
    return (this->__str + this->__size);
}

CompactString::const_iterator CompactString::begin() const{
    return this->__str;
}

CompactString::const_iterator CompactString::end() const{
    return (this->__str + this->__size);
}

CompactString::const_iterator CompactString::cbegin() const{
    return this->__str;
}

CompactString::const_iterator CompactString::cend()  const{
    return (this->__str + this->__size);
}

CompactString::reverse_iterator CompactString::rbegin(){
    return reverse_iterator{this->end() - 1};
}

CompactString::reverse_iterator CompactString::rend(){
    return reverse_iterator{this->begin() - 1};
}

CompactString::const_reverse_iterator CompactString::rbegin() const{
    return const_reverse_iterator{this->end() - 1};
}

CompactString::const_reverse_iterator CompactString::rend() const{
    return const_reverse_iterator{this->begin() - 1};
}

CompactString::const_reverse_iterator CompactString::crbegin() const{
    return CompactString::const_reverse_iterator{this->end() - 1};
}

CompactString::const_reverse_iterator CompactString::crend() const{
    return CompactString::const_reverse_iterator{this->begin() - 1};
}

std::strong_ordering operator<=>(const CompactString& lhs, const CompactString& rhs){
    using so = std::strong_ordering;

    char result;
    CompactString::const_iterator lhs_str = lhs.begin(), rhs_str = rhs.begin();
    size_t i{}, upto{(lhs.__size < rhs.__size) ? lhs.__size : rhs.__size};
    
    for (; i < upto; i++)
        if ((result = (lhs_str[i] - rhs_str[i])))
            break;
    
    if (!result)
        result = lhs.__size - rhs.__size;

    if (!result)
        return so::equal;
    else if (result < 0)
        return so::less;
    else
        return so::greater;
}

std::strong_ordering operator<=>(const CompactString& lhs, const char* rhs){
    using so = std::strong_ordering;
    
    size_t rhs_size{std::strlen(rhs)}, i{}, upto{(lhs.__size < rhs_size) ? lhs.__size : rhs_size};
    char result;
    CompactString::const_iterator lhs_str = lhs.begin();
    
    for (; i < upto; i++)
        if ((result = (lhs_str[i] - rhs[i])))
            break;
    
    if (!result)
        result = lhs.__size - rhs_size;

    if (!result)
        return so::equal;
    else if (result < 0)
        return so::less;
    else
        return so::greater;
}

bool operator==(const CompactString& lhs, const CompactString& rhs){
    if (lhs.__size != rhs.__size)
        return false;
    
    CompactString::const_iterator l_iter = lhs.begin(), l_end = lhs.end(), r_iter = rhs.begin();
    for (; l_iter != l_end; ++l_iter, ++r_iter)
        if (*l_iter != *r_iter)
            return false;
    return true;
}

bool operator==(const CompactString& lhs, const char* rhs){
    if (lhs.__size != std::strlen(rhs))
        return false;
    CompactString::const_iterator iter = lhs.begin(), end = lhs.end();
    for (; iter != end; ++iter, ++rhs)
        if (*iter != *rhs)
            return false;
    return true;
}

CompactString operator+(const CompactString& lhs, const CompactString& rhs){
    size_t tmp_size{lhs.__size + rhs.__size};
    CompactString tmp{tmp_size};
    memcpy(tmp.__str, lhs.__str, lhs.__size);
    memcpy(tmp.__str + lhs.__size, rhs.__str, rhs.__size);
    tmp.__str[tmp_size] = 0;
    tmp.__size = tmp_size;
    return tmp;
}

CompactString operator+(const CompactString& lhs, const char* rhs){
    size_t rhs_size{std::strlen(rhs)}, tmp_size{lhs.__size + rhs_size};
    CompactString tmp{tmp_size};
    memcpy(tmp.__str, lhs.__str, lhs.__size);
    memcpy(tmp.__str + lhs.__size, rhs, rhs_size);
    tmp.__str[tmp_size] = 0;
    tmp.__size = tmp_size;
    return tmp;
}

CompactString operator+(const char* lhs, const CompactString& rhs){
    size_t lhs_size{std::strlen(lhs)}, tmp_size{lhs_size + rhs.__size};
    CompactString tmp{tmp_size};
    memcpy(tmp.__str, lhs, lhs_size);
    memcpy(tmp.__str + lhs_size, rhs.__str, rhs.__size);
    tmp.__str[tmp_size] = 0;
    tmp.__size = tmp_size;
    return tmp;
}

CompactString& CompactString::operator+=(const char* rhs){
    size_t rhs_size{std::strlen(rhs)};
    if (!rhs_size)
        return *this;
    
    size_t new_size{__size + rhs_size};
    char* new_str = new char[new_size + 1];
    memcpy(new_str, this->__str, sizeof(char) * this->__size);
    memcpy(new_str + this->__size, rhs, rhs_size);
    new_str[new_size] = 0;
    delete[] this->__str;
    this->__str = new_str;
    this->__size = new_size;
    return *this;
}

CompactString& CompactString::operator+=(const CompactString& rhs){
    if (rhs.__size == 0)
        return *this;
    
    size_t new_size{this->__size + rhs.__size};
    char* new_str = new char[new_size + 1];
    memcpy(new_str, this->__str, sizeof(char) * this->__size);
    memcpy(new_str + this->__size, rhs.__str, rhs.__size);
    new_str[new_size] = 0;
    delete[] this->__str;
    this->__str = new_str;
    this->__size = new_size;
    return *this;
}

char& CompactString::operator[](unsigned long long i){
    if (this->__size == 0)
        throw IndexError();
    return this->__str[i];
}

const char& CompactString::operator[](unsigned long long i) const {
    if (this->__size == 0)
        throw IndexError();
    return this->__str[i];
}

CompactString& CompactString::operator=(const char* str){
    size_t len{std::strlen(str)};
    if (!len)
        return this->clear_string();

    if (len != __size)
    {
        delete[] this->__str;
        this->__str = new char[len + 1];
        __size = len;
        this->__str[len] = 0;
    }
    
    memcpy(this->__str, str, len);

    return *this;
}

CompactString& CompactString::operator=(const CompactString& str){
    if (this == &str)
        return *this;

#ifdef ARR_STRING_DEBUG
    std::cout << "Copying(=) string from " << &str << " to " << this << '\n';
#endif
    
    if (str.__size == 0)
        return this->clear_string();

    if (this->__size != str.__size)
    {
        delete[] this->__str;
        this->__str = new char[str.__size + 1];
        __size = str.__size;
        this->__str[__size] = 0;
    }

    memcpy(this->__str, str.__str, sizeof(char) * str.__size);
    
    return *this;
}

CompactString& CompactString::operator=(CompactString&& str){
    if (this == &str)
        return *this;
    
#ifdef ARR_STRING_DEBUG
    std::cout << "Moving(=) string from " << &str << " to " << this << '\n';
#endif

    delete[] this->__str;
    this->__str = str.__str;
    __size = str.__size;
    str.invalidate();
    return *this;
}

CompactString& CompactString::operator=(__string_input_buffer& buf){
    delete[] this->__str;
    this->__size = buf.size();
    this->__str = new char[this->__size + 1];
    memcpy(this->__str, buf.get_str(), this->__size);
    this->__str[this->__size] = 0;
    return *this;
}

CompactString::operator std::string_view() const{
    return std::string_view{this->__str};
}

CompactString::operator bool() const{
    return (this->__size != 0);
}

std::ostream& operator<<(std::ostream& output, const CompactString& str){
    if (!str.__size)
        return output;
    
    output << str.__str;
    return output;
}

std::ofstream& operator<<(std::ofstream& output, const CompactString& str){
    if (str.is_empty())
        return output;
    if (!output)
        throw FileOutputError();
    CompactString::const_iterator iter = str.begin(), end = str.end();
    for (; iter != end; ++iter)
        output.put(*iter);
    return output;
}

std::istream& operator>>(std::istream& input, CompactString& str){
    delete[] str.__str;
    __string_input_buffer buf;
    char ch;
    input.get(ch);
    while(ch != '\n'){
        buf.insert(ch);
        input.get(ch);
    }
    
    unsigned int size{buf.size()};
    if (!size){
        str.invalidate();
        return input;
    }
    str.__str = new char[size + 1];
    str.__size = size;
    memcpy(str.__str, buf.get_str(), size);
    str.__str[size] = 0;
    
    return input;
}

std::ifstream& operator>>(std::ifstream& input, CompactString& str){
    if (!input)
        throw FileInputError();
    delete[] str.__str;
    __string_input_buffer buf;
    char ch;
    input.get(ch);
    while(!input.eof()){
        buf.insert(ch);
        input.get(ch);
    }
    input.clear();
    unsigned int size{buf.size()};
    if (!size){
        str.invalidate();
        return input;
    }
    str.__str = new char[size + 1];
    str.__size = size;
    memcpy(str.__str, buf.get_str(), size);
    str.__str[size] = 0;
    
    return input;
}

bool getline(std::istream& input, CompactString& str){
    if (!input)
        throw FileInputError();
    if (input.eof())
        return false;
    delete[] str.__str;
    __string_input_buffer buf;
    char ch;
    input.get(ch);
    while ((ch != '\n') && (!input.eof())){
        buf.insert(ch);
        input.get(ch);
    }
    if (!buf.size()){
        str.invalidate();
        return (!input.eof());
    }
    
    str.__str = buf.get_str();
    str.__size = buf.size();
    buf.buf = nullptr;
    return (!input.eof());
}

/**
 * @brief Converts an integral value num to a string object.
 * @returns A string representation of the number num.
*/
template<typename U>
requires std::is_integral_v<U>
CompactString to_string(U num){
    if (!(num))
        return CompactString{"0"};
    return CompactString::__to_string(num);
}

template<typename U>
requires std::is_integral_v<U>
CompactString to_string(U num, int width){
    if (!(num || width))
        return CompactString{"0"};
    return CompactString::__to_string(num, width);
}

template<typename U>
requires std::is_integral_v<U>
CompactString to_string(U num, int width, char padding_char){
    if (!(num || width))
        return CompactString{"0"};
    return CompactString::__to_string(num, width, padding_char);
}

/**
 * @brief Split the C-Style string at the character ch and return a list of
 * strings of the individual pieces.
 * @param str The string to split.
 * @param ch The character to split at. By default the splitting is done at
 * the space(' ') character.
 * @returns A list of strings containing individual pieces after the split.
*/
CompactString::StringList split(const char* str, char ch = ' '){
	return CompactString(str).split(ch);
}

bool CompactString::__char_comp(char __x, char __y){
    return (__x == __y);
}

bool CompactString::__char_comp_i(char __x, char __y){
    return (std::tolower(__x) == std::tolower(__y));
}

bool CompactString::__contains_v(const char* pattern, size_t& m) const{
    if(this->is_empty() || (*pattern == 0))
        return false;
    m = std::strlen(pattern);
    if (m > this->__size)
        return false;
    return true;
}

bool CompactString::__contains(const char* str, size_t n, const char* pattern, size_t m, __char_compare_fun comp){
    size_t i{}, j{}, upto{n - m + 1};
    for (; i < upto; ++i){
        for (j = 0; (j < m) && comp(str[i + j], pattern[j]); ++j);
        if (j == m)
            return true;
    }
    return false;
}

bool CompactString::__search_v(const char* query, size_t& m) const{
    if (this->is_empty())
        throw ValueError("String empty");
    if (*query == 0)
        throw ValueError("Query string empty");
    m = std::strlen(query);
    if (m > this->__size)
        return false;
    return true;
}

long long CompactString::__search(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp){
    size_t i{}, j{}, upto{n - m + 1};
    for (; i < upto; ++i){
        for (j = 0; (j < m) && comp(str[i + j], query[j]); ++j);
        if (j == m)
            return i;
    }
    return -1;
}

bool CompactString::__search_all_v(const char* query, size_t& m) const{
    if (this->is_empty())
        throw ValueError("String empty");
    if (*query == 0)
        throw ValueError("Query string empty");
    m = std::strlen(query);
    if (m > this->__size)
        return false;
    return true;
}

CompactString::IndexList CompactString::__search_all(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp){
    IndexList indices;
    size_t i{}, j{}, upto{n - m + 1};
    for (; i < upto; ++i){
        for (j = 0; (j < m) && comp(str[i + j], query[j]); ++j);
        if (j == m)
            indices.append(i);
    }
    return indices;
}

size_t CompactString::__count(const char* pattern, __char_compare_fun comp) const{
    if (this->is_empty())
        throw ValueError("String empty");
    if (*pattern == 0)
        throw ValueError("Pattern empty");
    size_t m{std::strlen(pattern)};
    if (m > this->__size)
        return 0;
    size_t i{}, j{}, upto{this->__size - m + 1}, num_of_occurrences{};
    for (; i < upto; ++i){
        for (j = 0; (j < m) && comp(this->__str[i + j], pattern[j]); ++j);
        if (j == m)
            ++num_of_occurrences;
    }
    return num_of_occurrences;
}

template<typename U>
requires std::is_integral_v<U>
CompactString CompactString::__to_string(U num, int width, char padding_char){
    __string_input_buffer buf;
    U __num{num};
    if (num < 0)
        __num = -__num;
    for (; __num; __num /= 10)
        buf.insert((__num % 10) + '0');
    if (buf.size() < width)
        for (int i{}, upto = width - buf.size(); i < upto; ++i)
            buf.insert(padding_char);
    if (num < 0)
        buf.insert('-');
    return CompactString(buf).reverse();
}

#endif  // __ARR_STRING_H
