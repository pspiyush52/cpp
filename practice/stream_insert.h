/*
 * A collection of functions which overload the stream insertion(<<)
 * operator for standard library types.
 * 
 * Bring the namespace for the associated type into your program with the
 * 'using namespace <NAMESPACE NAME>;' syntax and then the objects of
 * that type will work directly with the stream insertion operator(<<).
 * 
 * Note that even if the headers for the stdlib types are included in
 * this header itself, you still have to include them in your code and
 * before the point where you include this header file otherwise the
 * preprocessor directives in this header will make it so that the code
 * you want to use will not be included in your program at all.
 */
#ifndef __STREAM_INSERT_H
#define __STREAM_INSERT_H

#include <iostream>

#ifndef __DELIM_ARR_H
#include <climits>
#include <float.h>
#endif  // __DELIM_ARR_H

#ifdef _GLIBCXX_VECTOR
#include <vector>
#include <string_view>
#endif

#ifdef _GLIBCXX_ARRAY
#include <array>
#include <string_view>
#endif

#ifdef _GLIBCXX_LIST
#include <list>
#include <string_view>
#endif

#ifdef _GLIBCXX_DEQUE
#include <deque>
#include <string_view>
#endif

#ifdef _GLIBCXX_SET
#include <set>
#include <string_view>
#endif

#ifdef _GLIBCXX_MAP
#include <map>
#include <string_view>
#endif

#ifdef _GLIBCXX_STACK
#include <stack>
#include <string_view>
#endif

#ifndef __DELIM_ARR_H
namespace delim_arr{
    inline std::ostream &operator<<(std::ostream &output, short arr[])
    {
        if (arr[0] == SHRT_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != SHRT_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }
    inline std::ostream &operator<<(std::ostream &output, unsigned short arr[])
    {
        if (arr[0] == USHRT_MAX)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != USHRT_MAX; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, int arr[])
    {
        if (arr[0] == INT_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != INT_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }
    inline std::ostream &operator<<(std::ostream &output, unsigned int arr[])
    {
        if (arr[0] == UINT_MAX)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != UINT_MAX; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, long arr[])
    {
        if (arr[0] == LONG_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != LONG_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }
    inline std::ostream &operator<<(std::ostream &output, unsigned long arr[])
    {
        if (arr[0] == ULONG_MAX)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != ULONG_MAX; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, long long arr[])
    {
        if (arr[0] == LLONG_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != LLONG_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }
    inline std::ostream &operator<<(std::ostream &output, unsigned long long arr[])
    {
        if (arr[0] == ULLONG_MAX)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != ULLONG_MAX; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, float arr[])
    {
        if (arr[0] == FLT_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != FLT_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, double arr[])
    {
        if (arr[0] == DBL_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != DBL_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }

    inline std::ostream &operator<<(std::ostream &output, long double arr[])
    {
        if (arr[0] == LDBL_MIN)
            output << "[]";
        else
        {
            output << "[";
            for (; *(arr + 1) != LDBL_MIN; ++arr)
                output << *arr << ", ";
            output << *arr << "]";
        }
        return output;
    }
}
#endif  // __DELIM_ARR_H

#ifdef _GLIBCXX_VECTOR
namespace __vec__{
    template<typename T>
    std::ostream& operator<<(std::ostream& output, const std::vector<T>& v){
        if (v.size() == 0)
            output << "[()";
        else
        {
            size_t i{}, upto{v.size() - 1};
            output << "[(";
            for (; i < upto; i++)
                output << v[i] << ", ";
            output << v[i] << ')';
        }
        output << ", <std::vector at " << &v << ">]";
        return output;
    }
    template<typename T>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::vector<T>& v){
        if (v.size() == 0)
            output << "[()";
        else
        {
            size_t i{}, upto{v.size() - 1};
            output << "[(";
            for (; i < upto; i++)
                output << '"' << v[i] << "\", ";
            output << "'" << v[i] << "\")";
        }
        output << ", <std::vector at " << &v << ">]";
        return output;
    }
}
#endif  // _GLIBCXX_VECTOR

#ifdef _GLIBCXX_ARRAY
namespace __array__{
    template<typename T, size_t size>
    std::ostream& operator<<(std::ostream& output, const std::array<T, size>& A){
        if (A.size() == 0)
            output << "[()";
        else
        {
            size_t i{}, upto{A.size() - 1};
            output << "[(";
            for (; i < upto; i++)
                output << A[i] << ", ";
            output << A[i] << ')';
        }
        output << ", <std::array at " << &A << ">]";
        return output;
    }
    template<typename T, size_t size>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::array<T, size>& A){
        if (A.size() == 0)
            output << "[()";
        else
        {
            size_t i{}, upto{A.size() - 1};
            output << "[(";
            for (; i < upto; i++)
                output << '"' << A[i] << "\", ";
            output << '"' << A[i] << "\")";
        }
        output << ", <std::array at " << &A << ">]";
        return output;
    }
}
#endif  // _GLIBCXX_ARRAY

#ifdef _GLIBCXX_LIST
namespace __list__{
    template<typename T>
    std::ostream& operator<<(std::ostream& output, const std::list<T>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << *begin << ", ";
            output << *begin << ')';
        }
        output << ", <std::list at " << &l << ">]";
        return output;
    }
    template<typename T>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::list<T>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << '"' << *begin << "\", ";
            output << '"' << *begin << "\")";
        }
        output << ", <std::list at " << &l << ">]";
        return output;
    }

}
#endif  // _GLIBCXX_LIST

#ifdef _GLIBCXX_DEQUE
namespace __deque__{
    template<typename T>
    std::ostream& operator<<(std::ostream& output, const std::deque<T>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << *begin << ", ";
            output << *begin << ')';
        }
        output << ", <std::deque at " << &l << ">]";
        return output;
    }
    template<typename T>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::deque<T>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << '"' << *begin << "\", ";
            output << '"' << *begin << "\")";
        }
        output << ", <std::deque at " << &l << ">]";
        return output;
    }

}
#endif  // _GLIBCXX_DEQUE

#ifdef _GLIBCXX_SET
namespace __set__{
    template<typename T, typename U>
    std::ostream& operator<<(std::ostream& output, const std::set<T, U>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << *begin << ", ";
            output << *begin << ')';
        }
        output << ", <std::set at " << &l << ">]";
        return output;
    }
    template<typename T, typename U>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::set<T, U>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << '"' << *begin << "\", ";
            output << '"' << *begin << "\")";
        }
        output << ", <std::set at " << &l << ">]";
        return output;
    }
}

namespace __multiset__{
    template<typename T, typename U>
    std::ostream& operator<<(std::ostream& output, const std::multiset<T, U>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << *begin << ", ";
            output << *begin << ')';
        }
        output << ", <std::multiset at " << &l << ">]";
        return output;
    }
    template<typename T, typename U>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::multiset<T, U>& l){
        if (l.size() == 0)
            output << "[()";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[(";
            for (; begin != end; ++begin)
                output << '"' << *begin << "\", ";
            output << '"' << *begin << "\")";
        }
        output << ", <std::multiset at " << &l << ">]";
        return output;
    }
}
#endif  // _GLIBCXX_SET

#ifdef _GLIBCXX_MAP
namespace __map__{
    template<typename T, typename U, typename V>
    std::ostream& operator<<(std::ostream& output, const std::map<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << begin->first << ": " << begin->second << ", ";
            output << begin->first << ": " << begin->second << '}';
        }
        output << ", <std::map at " << &l << ">]";
        return output;
    }
    template<typename T, typename U, typename V>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::map<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << '"' << begin->first << "\": " << begin->second << ", ";
            output << '"' << begin->first << "\": " << begin->second << '}';
        }
        output << ", <std::map at " << &l << ">]";
        return output;
    }
    template<typename T, typename U, typename V>
    requires std::is_convertible_v<U, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::map<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << begin->first << ": \"" << begin->second << "\", ";
            output << begin->first << ": \"" << begin->second << "\"}";
        }
        output << ", <std::map at " << &l << ">]";
        return output;
    }
}

namespace __multimap__{
    template<typename T, typename U, typename V>
    std::ostream& operator<<(std::ostream& output, const std::multimap<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << begin->first << ": " << begin->second << ", ";
            output << begin->first << ": " << begin->second << '}';
        }
        output << ", <std::multimap at " << &l << ">]";
        return output;
    }
    template<typename T, typename U, typename V>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::multimap<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << '"' << begin->first << "\": " << begin->second << ", ";
            output << '"' << begin->first << "\": " << begin->second << '}';
        }
        output << ", <std::multimap at " << &l << ">]";
        return output;
    }
    template<typename T, typename U, typename V>
    requires std::is_convertible_v<U, std::string_view>
    std::ostream& operator<<(std::ostream& output, const std::multimap<T, U, V>& l){
        if (l.size() == 0)
            output << "[{}";
        else
        {
            auto begin = l.begin();
            auto end = l.end();
            end--;
            output << "[{";
            for (; begin != end; ++begin)
                output << begin->first << ": \"" << begin->second << "\", ";
            output << begin->first << ": \"" << begin->second << "\"}";
        }
        output << ", <std::multimap at " << &l << ">]";
        return output;
    }
}
#endif  // _GLIBCXX_MAP

#ifdef _GLIBCXX_STACK
namespace __stack__{
    template<typename T, typename Container = std::deque<T>>
    std::ostream& operator<<(std::ostream& output, std::stack<T, Container> s){
        if (s.empty())
            output << "[()";
        else
        {
            T num;
            output << "[(";
            while (s.size() > 1){
                num = s.top();
                s.pop();
                output << num << ", ";
            }
            output << s.top() << ')';
            s.pop();
        }
        output << ", <std::stack at " << &s << ">]";
        return output;
    }

    template<typename T, typename Container = std::deque<T>>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, std::stack<T, Container> s){
        if (s.empty())
            output << "[()";
        else
        {
            T num;
            output << "[(";
            while (s.size() > 1){
                num = s.top();
                s.pop();
                output << '"' << num << "\", ";
            }
            output << '"' << s.top() << "\")";
            s.pop();
        }
        output << ", <std::stack at " << &s << ">]";
        return output;
    }
}
#endif  // _GLIBCXX_STACK

#endif  // __STREAM_INSERT_H