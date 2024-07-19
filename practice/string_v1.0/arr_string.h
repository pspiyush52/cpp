#ifndef __ARR_STRING_H
#define __ARR_STRING_H

#include <iostream>
#include <concepts>
#include <cmath>
#include "exceptions.h"
#include "utils.h"
#include "lists.h"
#include "reverse_iterator.h"

class string;
class __string_input_buffer{
    public:
        __string_input_buffer();
        void insert(const char& ch);
        char* get_str();
        unsigned int size();
        void clear_buffer();
        ~__string_input_buffer();
    
    private:
        char* buf;
        unsigned int cur;
        unsigned int buffer_size;
        void __buffer_expand();
        friend bool getline(std::istream& input, string& str);
};

class string{
    public:
        typedef                                                        char         value_type;
        typedef                                                        char*        iterator;
        typedef                                                  const char*        const_iterator;
        typedef                     __reverse_iterator<iterator, value_type>        reverse_iterator;
        typedef         __const_reverse_iterator<const_iterator, value_type>        const_reverse_iterator;
        typedef                                                 List<size_t>        index_list;
        typedef                                                 List<string>        string_list;
    
    public:
        string();
        string(char ch, size_t num);
        string(const char* str);
        string(const std::string& str);
        string(const string& src);
        string(string&& src);
        ~string();

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
        string first_word() const;

        /**
         * @brief Returns a new string object containing only the last word of
         * the complete string.
         * @returns A new string object.
        */
        string last_word() const;

        /**
         * @brief Create and return a new string with all characters in
         * lowercase.
         * @returns A new string with all characters in lowercase.
        */
        string get_lower() const;

        /**
         * @brief Create and return a new string with all characters in
         * uppercase.
         * @returns A new string with all characters in uppercase.
        */
        string get_upper() const;

        /**
         * @brief Make the string lowercase in place and return a reference
         * to the current string object.
         * @returns Reference to the string object.
        */
        string& to_lower();

        /**
         * @brief Make the string uppercase in place and return a reference
         * to the string.
         * @returns Reference to the string object.
        */
        string& to_upper();

        /**
         * @brief Capitalizes the first character of the string. Leading
         * whitespace is ignored.
         * @returns Reference to the capitalized string.
        */
        string& capitalize();

        string& title();

        string titled() const;

        string& collapse();

        string collapsed() const;

        /**
         * @brief Creates and returns a new string containing the binary
         * representation of the number in the string.
         * @note Requires that the string be a numeric string (containing
         * only characters 0 - 9).
         * @returns A string containing the binary representation.
         * @throws ValueError if the string is not numeric
        */
        string bstring() const;

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
        string bstring(int width) const;

        /**
         * @brief Creates and returns a string containing the binary
         * representation of num.
         * @param num The number whose binary representation is required.
         * @returns A string containing the binary representation.
        */
        friend string bstring(int num);
        friend string bstring(unsigned int num);
        friend string bstring(long long num);
        friend string bstring(unsigned long long num);

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
        friend string bstring(int num, int width);
        friend string bstring(unsigned int num, int width);
        friend string bstring(long long num, int width);
        friend string bstring(unsigned long long num, int width);

        /**
         * @brief Reverses and returns a reference to the string.
         * @returns Reference to the string object.
        */
        string& reverse();

        /**
         * @brief Creates and returns a new string with the characters in
         * reverse order with respect to the current string.
         * @returns A new string object with the reversed string.
        */
        string reversed() const;

        /**
         * @brief Perform case insensitive comparison of the current string
         * with string rhs.
        */
        bool similar(const string& rhs) const;

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
        size_t count(const string& pattern) const;

        /**
         * @brief Counts and returns the number of occurrences(case-insensitive)
         * of the pattern in the string.
         * @param pattern The pattern string whose number of occurrences need
         * to be found case-insensitively.
         * @returns Number of times the pattern occurs in the string.
        */
        size_t counti(const string& pattern) const;

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
        bool contains(const string& pattern) const;

        /**
         * @brief Check if the pattern occurs in the string(case-insensitive).
         * @param pattern The pattern string whose occurrence is checked.
         * @returns A boolean value indicating whether the string contains the
         * pattern or not.
        */
        bool containsi(const string& pattern) const;

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
        long long search(const string& query) const;

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
        long long searchi(const string& query) const;

        /**
         * @brief Searches for all the occurrences of the query string in the
         * string and returns a list of positions of all the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        index_list search_all(const char* query) const;

        /**
         * @brief Searches for all the occurrences of the query string in the
         * string and returns a list of positions of all the occurrences.
         * @param query The string to search for.
         * @returns A list of indices where the query string occurs in the
         * string. An empty list if the query is not found.
         * @throws ValueError: If either the string is empty or the query
         * string is empty or both.
        */
        index_list search_all(const string& query) const;

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
        index_list search_alli(const char* query) const;

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
        index_list search_alli(const string& query) const;
        
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
        string& replace(char to_replace, char replacement_char);
        /**
         * @brief Fills the entire string with the fill_char character and
         * returns a reference to the string
         * @param fill_char The character to be used to fill the string
         * @returns A reference to the modified string.
        */
        string& fill(char fill_char);

        /**
         * @brief Return a new string containing n number of characters from
         * the start of the current string.
         * @returns A new string object.
        */
        string operator()(size_t n) const;

        /**
         * @brief Return a new string containing characters from the current
         * string starting from index start, going up to end.
         * @returns A new string object.
        */
        string operator()(size_t start, size_t end) const;

        /**
         * @brief Return a new string containing n characters from the start
         * of the current string.
         * @returns A new string object.
        */
        string slice(size_t end) const;

        /**
         * @brief Return a new string containing characters from the current
         * string starting from index start, going up to end.
         * @returns A new string object.
        */
        string slice(size_t start, size_t end) const;

        /**
         * @brief Return a new string with all characters from the current
         * string starting from the index pos.
         * @param pos The position from which the characters are to be copied
         * in the new string
         * @returns A new string containing all characters from the current
         * string after the index pos.
        */
        string from_pos(size_t pos) const;

        string from_pos(size_t pos, size_t count) const;

        /**
         * @brief Return a string containing count number of characters from
         * the end of the current string.
         * @param count Number of characters from the end to include.
         * @return A new string containing count number of characters from the
         * end.
        */
        string nlast(size_t count) const;

        /**
         * @brief Strip all whitespace characters from the left (the
         * beginning) of the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        string& lstrip();

        /**
         * @brief Strip all the whitespace characters from the right (the
         * end) of the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        string& rstrip();

        /**
         * @brief Strip all the whitespace characters from both the ends of
         * the string.
         * Modifies the string in place.
         * @return A reference to the modified string.
        */
        string& strip();

        /**
         * @brief Splits the string at character ch and returns a list of the
         * individual components obtained after splitting.
         * @param ch The character in the string to split on.
         * @returns A list of strings.
        */
        string_list split(char ch = ' ') const;

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
        string& modify(Modifier mod_fun = {}, Predicate pred = {});

        template<typename Modifier>
        string& transform(Modifier mod_fun = {});

        /**
         * @brief Set the value of the precision flag which specifies the
         * number of digits which appear after the decimal upon using the
         * to_string function to convert a floating point number to a string.
         * @throws ValueError if an attempt is made to set the precision to 0.
        */
        static void set_precision(int prec);

        /**
         * @brief Get the current value of the precision flag which specifies
         * the number of digits which appear after the decimal upon using the
         * to_string function to convert a floating point number to a string.
         * @returns Value of the precision flag.
        */
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
        char& operator[](long long i);
        const char& operator[](long long i) const;

        string& operator=(const char* str);
        string& operator=(const string& str);
        string& operator=(string&& str);
        string& operator=(__string_input_buffer& buf);

        operator std::string_view() const;
        operator bool() const;

        /**
         * @brief Return a string representation of the floating point number with the
         * set precision number of digits after the decimal. The value of precision is
         * taken from the precision flag set in the string class itself and can be
         * modified using the set_precision() function.
         * @param num The floating point number whose string representation is sought.
         * @returns A string object containing a string representation of the number.
        */
        template<typename U>
        friend string to_string(U num);

        /**
         * @brief Return a string representation of the floating point number with the
         * set precision number of digits after the decimal. The value of precision is
         * taken from the precision flag set in the string class itself and can be
         * modified using the set_precision() function.
         * @param num The floating point number whose string representation is sought.
         * @param precision If specified, will override the default precision value
         * specified by the string::precision flag.
         * Specify a value for this parameter to force zeroes after the decimal even
         * if the fractional part is zero.
         * Use precision to force appearance of digits after the decimal. If the
         * precision is not specified then no matter what the value of the
         * string::precision flag is, if there are no digits after the decimal then
         * the decimal will not be shown and the number will appear as an integer.
         * @returns A string object containing a string representation of the number.
        */
        template<typename U>
        friend string to_string(U num, int precision);

        template<typename U>
        requires std::is_integral_v<U>
        friend string to_string(U num);

        template<typename U>
        requires std::is_integral_v<U>
        friend string to_string(U num, int width);

        template<typename U>
        requires std::is_integral_v<U>
        friend string to_string(U num, int width, char padding_char);

        friend std::ostream& operator<<(std::ostream& output, const string& str);
        friend std::ofstream& operator<<(std::ofstream& output, const string& str);
        friend std::istream& operator>>(std::istream& input, string& str);
        friend std::ifstream& operator>>(std::ifstream& input, string& str);
        friend bool getline(std::istream& input, string& str);
    
    private:
        char* __str{nullptr};
        size_t __size{0};
        static inline unsigned int precision{6};
        static inline const char* __dummy{""};

        typedef bool (*__char_compare_fun)(char, char);
        
        string(size_t size);
        string(int num, int, int);
        string(unsigned int num, int, int);

        string(long long num, int, int);
        string(unsigned long long num, int, int);
        
        string(int num, int width, int, int);
        string(unsigned int num, int width, int, int);
        
        string(long long num, int width, int, int);
        string(unsigned long long num, int width, int, int);
        
        string(__string_input_buffer& buf);

        void invalidate();
        string& clear_string();
        string& make(size_t size);
        
        static bool __char_comp(char __x, char __y);
        static bool __char_comp_i(char __x, char __y);

        bool __contains_v(const char* pattern, size_t& m) const;
        static bool __contains(const char* str, size_t n, const char* pattern, size_t m, __char_compare_fun comp);
        
        bool __search_v(const char* query, size_t& m) const;
        static long long __search(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp);
        
        bool __search_all_v(const char* query, size_t& m) const;
        static index_list __search_all(const char* str, size_t n, const char* query, size_t m, __char_compare_fun comp);
        
        size_t __count(const char* pattern, __char_compare_fun comp) const;

        template<typename U>
        requires std::is_integral_v<U>
        static string __to_string(U num, int width = 0, char padding_char = '0');
};

bool __is_whitespace(const char& ch);

template<typename Modifier, typename Predicate>
string& string::modify(Modifier mod_fun, Predicate pred){
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
string& string::transform(Modifier mod_fun){
    mod_fun(this->begin(), this->__size);
    return *this;
}
string bstring(int num);
string bstring(unsigned int num);
string bstring(long long num);
string bstring(unsigned long long num);
string bstring(int num, int width);
string bstring(unsigned int num, int width);
string bstring(long long num, int width);
string bstring(unsigned long long num, int width);

/**
 * @brief Converts an integral value num to a string object.
 * @returns A string representation of the number num.
*/
template<typename U>
requires std::is_integral_v<U>
string to_string(U num){
    if (!(num))
        return string{"0"};
    return string::__to_string(num);
}

template<typename U>
requires std::is_integral_v<U>
string to_string(U num, int width){
    if (!(num || width))
        return string{"0"};
    return string::__to_string(num, width);
}

template<typename U>
requires std::is_integral_v<U>
string to_string(U num, int width, char padding_char){
    if (!(num || width))
        return string{"0"};
    return string::__to_string(num, width, padding_char);
}

template<typename U>
requires std::is_floating_point_v<U>
string to_string(U num){
    if (!num){
        return string{"0.0"};
    }
    long long whole{static_cast<long long>(num)};
    long long frac{static_cast<long long>((num - whole) * std::pow(10, string::get_precision()))};
    if (frac < 0)
        frac = -frac;
    if (frac)
        return (to_string(whole) + "." + to_string(frac));
    return to_string(whole);
}

template<typename U>
requires std::is_floating_point_v<U>
string to_string(U num, int precision){
    if (precision < 1)
        throw ValueError("to_string()\nPrecision cannot be lower than 1");
    if (!num){
        return string{"0.0"};
    }
    long long whole{static_cast<long long>(num)}, frac{};
    
    if (precision > 15)
        precision = 15;
    frac = static_cast<long long>((num - whole) * std::pow(10, precision));
    if (frac < 0)
        frac = -frac;
    if (frac)
        return (to_string(whole) + "." + to_string(frac));
    else
        return (to_string(whole) + "." + string('0', precision));
}

/**
 * @brief Split the C-Style string at the character ch and return a list of
 * strings of the individual pieces.
 * @param str The string to split.
 * @param ch The character to split at. By default the splitting is done at
 * the space(' ') character.
 * @returns A list of strings containing individual pieces after the split.
*/
string::string_list split(const char* str, char ch = ' ');

template<typename U>
requires std::is_integral_v<U>
string string::__to_string(U num, int width, char padding_char){
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
    return std::move(string(buf).reverse());
}

#endif  // __ARR_STRING_H