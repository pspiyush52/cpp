/**
 * ========================== DELIMITED ARRAYS ==========================
 * 
 * Delimited arrays are arrays which have one extra array item which
 * holds a special value i.e., the delimiter. The only purpose of the
 * delimiter is to demarcate the end of the array so that we can use the
 * array with std::cout directly without having to pass the size of the
 * array which is a necessity otherwise there are no means of knowing
 * where the array ends.
 * 
 * In delimited arrays the delimiter marks the end of the array and
 * printing stops before the delimiter.
 * It can be thought of as the end iterator to the array.
 * 
 * The delimited arrays are created dynamically and a unique pointer to
 * the array is returned so that we do not have to worry about calling
 * delete for every allocated array in our program.
 * 
 * NOTE: Define the NO_UNQUE_PTR macro in your source file if you want
 * to use raw pointers to manage the dynamically allocated delimited
 * arrays.
 * ***You'll have to deallocate the memory yourself using the delete[]
 * operator.
 */
#ifndef __DELIM_ARR_H
#define __DELIM_ARR_H

#include <memory>
#include <climits>
#include <float.h>

#ifndef NO_UNIQUE_PTR
namespace del{
    /**
     * @brief: A template type alias for the unique pointer which will be
     * used to handle the dynamic array.
     */
    template<typename T, typename Deleter = std::default_delete<T[]>>
    using array = std::unique_ptr<T[], Deleter>;
}
#endif  // NO_UNIQUE_PTR

namespace s{
    
    typedef short type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = SHRT_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
		arr[size] = SHRT_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return arr;
	}
#else
    
    typedef del::array<type_name> uptr;

    inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = SHRT_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = SHRT_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace us{
    
    typedef unsigned short type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = USHRT_MAX;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
		arr[size] = USHRT_MAX;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return arr;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = USHRT_MAX;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = USHRT_MAX;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}

namespace i{

    typedef int type_name;
    typedef type_name* pointer;
    typedef const int* const_pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = INT_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
        arr[size] = INT_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = INT_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
        arr[size] = INT_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
    template<typename iterator>
    inline uptr make_array(const iterator begin, const iterator end){
        size_t size{};
        const_pointer _begin = begin;
        for (; _begin != end; ++_begin, ++size);
        uptr arr{new type_name[size + 1]};
        arr[size] = INT_MIN;
        const_pointer __begin = begin;
        for (size_t i{}; __begin != end; ++__begin, ++i)
            arr[i] = *__begin;
        return arr;
    }
#endif  // NO_UNIQUE_PTR
}
namespace ui{

    typedef unsigned int type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = UINT_MAX;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
		arr[size] = UINT_MAX;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = UINT_MAX;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = UINT_MAX;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}

namespace l{
    
    typedef long type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = LONG_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
		arr[size] = LONG_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = LONG_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = LONG_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace ul{
    
    typedef unsigned long type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = ULONG_MAX;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
		arr[size] = ULONG_MAX;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = ULONG_MAX;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = ULONG_MAX;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}

namespace ll{
    
    typedef long long type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = LLONG_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
		arr[size] = LLONG_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else

    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = LLONG_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = LLONG_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace ull{
    
    typedef unsigned long long type_name;
    typedef type_name* pointer;
    
#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = ULLONG_MAX;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
        pointer retval = arr;
		arr[size] = ULLONG_MAX;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return retval;
	}
#else

    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = ULLONG_MAX;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = ULLONG_MAX;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace f{
    
    typedef float type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = FLT_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
		arr[size] = FLT_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return arr;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = FLT_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = FLT_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace d{
    
    typedef double type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = DBL_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
		arr[size] = DBL_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return arr;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = DBL_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = DBL_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}
namespace ld{
    
    typedef long double type_name;
    typedef type_name* pointer;

#ifdef NO_UNIQUE_PTR
    inline pointer make_array(size_t size){
		pointer arr{new type_name[size + 1]};
		arr[size] = LDBL_MIN;
		return arr;
	}
    inline pointer make_array(size_t size, type_name default_value){
		pointer arr{new type_name[size + 1]};
		arr[size] = LDBL_MIN;
        for (size_t i{}; i < size; ++arr, ++i)
            *arr = default_value;
		return arr;
	}
#else
    
    typedef del::array<type_name> uptr;

	inline uptr make_array(size_t size){
		uptr arr{new type_name[size + 1]};
		arr[size] = LDBL_MIN;
		return arr;
	}
	inline uptr make_array(size_t size, type_name default_value){
		uptr arr{new type_name[size + 1]};
		arr[size] = LDBL_MIN;
        size_t i{};
        for (pointer _arr = arr.get(); i < size; ++_arr, ++i)
            *_arr = default_value;
		return arr;
	}
#endif  // NO_UNIQUE_PTR
}

#ifndef NO_UNIQUE_PTR
/*
 * Overloads of the output stream operator to enable printing of the
 * array pointed to by the unique pointer.
 */

inline std::ostream& operator<<(std::ostream& output, const del::array<short>& arr){
    output << '[';
    const short* _arr = arr.get();
    if (*_arr == SHRT_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != SHRT_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<unsigned short>& arr){
    output << '[';
    const unsigned short* _arr = arr.get();
    if (*_arr == USHRT_MAX){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != USHRT_MAX; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<int>& arr){
    output << '[';
    const int* _arr = arr.get();
    if (*_arr == INT_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != INT_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<unsigned int>& arr){
    output << '[';
    const unsigned int* _arr = arr.get();
    if (*_arr == UINT_MAX){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != UINT_MAX; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<long>& arr){
    output << '[';
    const long* _arr = arr.get();
    if (*_arr == LONG_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != LONG_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<unsigned long>& arr){
    output << '[';
    const unsigned long* _arr = arr.get();
    if (*_arr == ULONG_MAX){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != ULONG_MAX; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<long long>& arr){
    output << '[';
    const long long* _arr = arr.get();
    if (*_arr == LLONG_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != LLONG_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<unsigned long long>& arr){
    output << '[';
    const unsigned long long* _arr = arr.get();
    if (*_arr == ULLONG_MAX){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != ULLONG_MAX; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<float>& arr){
    output << '[';
    const float* _arr = arr.get();
    if (*_arr == FLT_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != FLT_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<double>& arr){
    output << '[';
    const double* _arr = arr.get();
    if (*_arr == DBL_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != DBL_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
inline std::ostream& operator<<(std::ostream& output, const del::array<long double>& arr){
    output << '[';
    const long double* _arr = arr.get();
    if (*_arr == LDBL_MIN){
        output << ']';
        return output;
    }
    for (; *(_arr + 1) != LDBL_MIN; ++_arr)
        output << *_arr << ", ";
    output << *_arr << ']';
    return output;
}
#endif  // NO_UNIQUE_PTR

/**
 * @brief Contains the overloads for the output stream operator(<<) for
 * raw delimited arrays.
 * Bring this namespace into your code to print delimited raw arrays
 * directly using std::cout.
 * 
 * @warning Regular pointers of fundamental types will be treated as
 * delimited arrays too after this namespace is included in your code so
 * using regular pointers with std::cout may result in a program crash.
 * Use in limited scopes only.
 */
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