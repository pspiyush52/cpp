#include <iostream>
#include <initializer_list>
#include "stream_insertable.h"

template<typename T = int, size_t default_size = 16>
class Array : public st::StreamInsertable<T>{
    public:
        Array(size_t size = default_size);
        Array(std::initializer_list<T> args);
        void stream_insert(std::ostream& output) const override;
        void stream_insert_s(std::ostream& output) const override;
        ~Array();
    
    private:
        T* arr;
        size_t arr_size;
};

template<typename T, size_t default_size>
Array<T, default_size>::Array(size_t size) : arr(new T[size]), arr_size(size){}

template<typename T, size_t default_size>
Array<T, default_size>::Array(std::initializer_list<T> args):
    Array(args.size()){
        const T* front = args.begin();
        memcpy(arr, front, arr_size * sizeof(T));
    }

template<typename T, size_t ds>
void Array<T, ds>::stream_insert(std::ostream& output) const{
    if (!arr_size)
        output << "[]";
    else
    {
        output << '[';
        size_t i{}, upto{arr_size - 1};
        for (; i < upto; i++)
            output << arr[i] << ", ";
        output << arr[i] << ']';
    }
}

template<typename T, size_t ds>
void Array<T, ds>::stream_insert_s(std::ostream& output) const{
    if (!arr_size)
        output << "[]";
    else
    {
        output << '[';
        size_t i{}, upto{arr_size - 1};
        for (; i < upto; i++)
            output << '\"' << arr[i] << "\", ";
        output << '\"' << arr[i] << "\"]";
    }
}

template<typename T, size_t ds>
Array<T, ds>::~Array() { delete[] arr; arr_size = 0; }

int main(void)
{
    const Array days{0, 1, 2, 3, 4, 5, 6};
    std::cout << "days: " << days << '\n';

    Array dnames{
        "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
    };
    std::cout << "Names: " << dnames << '\n';
    return 0;
}